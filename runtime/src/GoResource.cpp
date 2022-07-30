#include "GoResource.h"

Go::Resource::Resource(Go::Runtime *runtime, alt::IResource *resource) : _runtime(runtime), _resource(resource) {}

bool Go::Resource::Start() {
    Module = LOAD_LIB((_resource->GetPath() + SEPARATOR + _resource->GetMain()).c_str());
    if (Module == nullptr) {
        alt::ICore::Instance()
                .LogError("Failed to open main file");

        return false;
    }

    auto resourceName = _resource->GetName().c_str();
    auto resourcePath = _resource->GetPath().c_str();
    auto go = GET_FUNC(Module, "initGoResource",
                       void(*)(alt::IResource * resourcePtr, const char *resourceName, const char *resourcePath, const char *version));
    if (go == nullptr) {
        alt::ICore::Instance()
                .LogError("Error while initializing Go Resource");

        return false;
    }

    go(_resource, resourceName, resourcePath, GO_MODULE_VERSION);


    auto start = GET_FUNC(Module, "OnStart", void(*)());
    if (start == nullptr) {
        alt::ICore::Instance().LogError("Main entrypoint not found");
        return false;
    }

    RegisterEventHandler(Go::EventType::PLAYER_CONNECT, new PlayerConnectEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_DISCONNECT, new PlayerDisconnectEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_DAMAGE, new PlayerDamageEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_DEATH, new PlayerDeathEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_ENTER_VEHICLE, new PlayerEnterVehicleEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_LEAVE_VEHICLE, new PlayerLeaveVehicleEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_CHANGE_VEHICLE_SEAT, new PlayerChangeVehicleSeatEvent(Module));
    RegisterEventHandler(Go::EventType::REMOVE_ENTITY_EVENT, new RemoveEntityEvent(Module));
    RegisterEventHandler(Go::EventType::CONSOLE_COMMAND_EVENT, new ConsoleCommandEvent(Module));
    RegisterEventHandler(Go::EventType::WEAPON_DAMAGE_EVENT, new WeaponDamageEvent(Module));
    RegisterEventHandler(Go::EventType::EXPLOSION_EVENT, new ExplosionEvent(Module));
    RegisterEventHandler(Go::EventType::RESOURCE_START, new ResourceStartEvent(Module));
    RegisterEventHandler(Go::EventType::COLSHAPE_EVENT, new ColShapeEvent(Module));
    RegisterEventHandler(Go::EventType::FIRE_EVENT, new FireEvent(Module));
    RegisterEventHandler(Go::EventType::SYNCED_META_CHANGE, new SyncedMetaDataChangeEvent(Module));
    RegisterEventHandler(Go::EventType::STREAM_SYNCED_META_CHANGE, new StreamSyncedMetaDataChangeEvent(Module));
    RegisterEventHandler(Go::EventType::GLOBAL_META_CHANGE, new GlobalMetaDataChangeEvent(Module));
    RegisterEventHandler(Go::EventType::GLOBAL_SYNCED_META_CHANGE, new GlobalSyncedMetaDataChangeEvent(Module));
    RegisterEventHandler(Go::EventType::RESOURCE_STOP, new ResourceStopEvent(Module));
    RegisterEventHandler(Go::EventType::RESOURCE_ERROR, new ResourceErrorEvent(Module));
    RegisterEventHandler(Go::EventType::VEHICLE_DESTROY, new VehicleDestroyEvent(Module));
    RegisterEventHandler(Go::EventType::START_PROJECTILE_EVENT, new StartProjectileEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_WEAPON_CHANGE, new PlayerWeaponChangeEvent(Module));
    RegisterEventHandler(Go::EventType::VEHICLE_ATTACH, new VehicleAttachEvent(Module));
    RegisterEventHandler(Go::EventType::VEHICLE_DETACH, new VehicleDetachEvent(Module));
    RegisterEventHandler(Go::EventType::NETOWNER_CHANGE, new NetOwnerChangeEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_ENTERING_VEHICLE, new PlayerEnteringVehicleEvent(Module));
    RegisterEventHandler(Go::EventType::SERVER_SCRIPT_EVENT, new ServerScriptEvent(Module));
    RegisterEventHandler(Go::EventType::CLIENT_SCRIPT_EVENT, new ClientScriptEvent(Module));
    RegisterEventHandler(Go::EventType::VEHICLE_DAMAGE, new VehicleDamageEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_BEFORE_CONNECT, new PlayerBeforeConnectEvent(Module));
    RegisterEventHandler(Go::EventType::CONNECTION_QUEUE_ADD, new ConnectionQueueAddEvent(Module));
    RegisterEventHandler(Go::EventType::CONNECTION_QUEUE_REMOVE, new ConnectionQueueRemoveEvent(Module));
    RegisterEventHandler(Go::EventType::SERVER_STARTED, new ServerStartedEvent(Module));
    RegisterEventHandler(Go::EventType::LOCAL_SYNCED_META_CHANGE, new LocalSyncedMetaDataChangeEvent(Module));
    RegisterEventHandler(Go::EventType::META_CHANGE, new MetaDataChangeEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_REQUEST_CONTROL, new PlayerRequestControlEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_CHANGE_ANIMATION_EVENT, new PlayerChangeAnimationEvent(Module));
    RegisterEventHandler(Go::EventType::PLAYER_CHANGE_INTERIOR_EVENT, new PlayerChangeInteriorEvent(Module));

    start();

    _resource->SetExports(_registeredExports);

    return true;
}

bool Go::Resource::Stop() {
    auto shutdown = GET_FUNC(Module, "stopGoResource", void(*)());
    if (shutdown == nullptr) {
        alt::ICore::Instance().LogError("Couldn't call resource internal shutdown.");
        return false;
    }

    auto stop = GET_FUNC(Module, "OnStop", void(*)());
    if (stop == nullptr) {
        alt::ICore::Instance().LogError("Couldn't call OnStop.");
        return false;
    }

    shutdown();
    stop();
    return true;
}

bool Go::Resource::OnEvent(const alt::CEvent *ev) {
    auto type = ev->GetType();

    //if (!IsEventRegistered(type)) {
    //    return false;
    //}

    NotifyEvent(ev, _resource->GetName().c_str());
    return true;
}

void Go::Resource::OnTick() {}

void Go::Resource::OnCreateBaseObject(alt::Ref<alt::IBaseObject> handle) {
    this->AddEntity(handle.Get());
}

void Go::Resource::OnRemoveBaseObject(alt::Ref<alt::IBaseObject> handle) {
    this->RemoveEntity(handle.Get());
}
