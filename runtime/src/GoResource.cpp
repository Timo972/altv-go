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
                       int(*)(alt::IResource * resourcePtr, const char *resourceName, const char *ResourcePath, const char *version));
    if (go == nullptr) {
        alt::ICore::Instance()
                .LogError("Error while initializing Go Resource");

        return false;
    }

    bool ok = go(_resource, resourceName, resourcePath, GO_MODULE_VERSION);
    if (!ok) {
        return ok;
    }


    auto start = GET_FUNC(Module, "OnStart", void(*)());
    if (start == nullptr) {
        alt::ICore::Instance().LogError("Main entrypoint not found");
        return false;
    }

    RegisterEventHandler(alt::CEvent::Type::PLAYER_CONNECT, new PlayerConnectEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_DISCONNECT, new PlayerDisconnectEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_DAMAGE, new PlayerDamageEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_DEATH, new PlayerDeathEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_ENTER_VEHICLE, new PlayerEnterVehicleEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_LEAVE_VEHICLE, new PlayerLeaveVehicleEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_CHANGE_VEHICLE_SEAT, new PlayerChangeVehicleSeatEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::CONSOLE_COMMAND_EVENT, new ConsoleCommandEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::WEAPON_DAMAGE_EVENT, new WeaponDamageEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::EXPLOSION_EVENT, new ExplosionEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::RESOURCE_START, new ResourceStartEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::COLSHAPE_EVENT, new ColShapeEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::FIRE_EVENT, new FireEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::SYNCED_META_CHANGE, new SyncedMetaDataChangeEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::STREAM_SYNCED_META_CHANGE, new StreamSyncedMetaDataChangeEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::GLOBAL_META_CHANGE, new GlobalMetaDataChangeEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::GLOBAL_SYNCED_META_CHANGE, new GlobalSyncedMetaDataChangeEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::RESOURCE_STOP, new ResourceStopEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::RESOURCE_ERROR, new ResourceErrorEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::VEHICLE_DESTROY, new VehicleDestroyEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::START_PROJECTILE_EVENT, new StartProjectileEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_WEAPON_CHANGE, new PlayerWeaponChangeEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::VEHICLE_ATTACH, new VehicleAttachEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::VEHICLE_DETACH, new VehicleDetachEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::NETOWNER_CHANGE, new NetOwnerChangeEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_ENTERING_VEHICLE, new PlayerEnteringVehicleEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::SERVER_SCRIPT_EVENT, new ServerScriptEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::CLIENT_SCRIPT_EVENT, new ClientScriptEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::VEHICLE_DAMAGE, new VehicleDamageEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::CONNECTION_QUEUE_ADD, new ConnectionQueueAddEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::CONNECTION_QUEUE_REMOVE, new ConnectionQueueRemoveEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::SERVER_STARTED, new ServerStartedEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::LOCAL_SYNCED_META_CHANGE, new LocalSyncedMetaDataChangeEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::META_CHANGE, new MetaDataChangeEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_REQUEST_CONTROL, new PlayerRequestControlEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_CHANGE_ANIMATION_EVENT, new PlayerChangeAnimationEvent(Module));
    RegisterEventHandler(alt::CEvent::Type::PLAYER_CHANGE_INTERIOR_EVENT, new PlayerChangeInteriorEvent(Module));

    start();

    _resource->SetExports(_registeredExports);

    return true;
}

bool Go::Resource::Stop() {
    auto stop = GET_FUNC(Module, "OnStop", void(*)());
    if (stop == nullptr) {
        alt::ICore::Instance().LogError("Couldn't call OnStop.");
        return false;
    }

    stop();

    // TODO: UNLOAD_LIB(Module)
    // https://github.com/golang/go/issues/11100

    return true;
}

void Go::Resource::OnEvent(const alt::CEvent *ev) {
    auto type = ev->GetType();

    NotifyEvent(ev, _resource->GetName().c_str());
}

void Go::Resource::OnTick() {}

void Go::Resource::OnCreateBaseObject(alt::IBaseObject* handle) {
    this->AddEntity(handle);

    CBaseObject *object;
    Go::Runtime::GetCBaseObject(handle, object);

    static auto addEntity = GET_FUNC(Module, "altCreateBaseObject", void(*)(CBaseObject*));
    if (addEntity == nullptr) {
        alt::ICore::Instance().LogError("Could not call altCreateBaseObject.");
        return;
    }
    addEntity(object);
}

void Go::Resource::OnRemoveBaseObject(alt::IBaseObject* handle) {
    this->RemoveEntity(handle);
    CBaseObject *object;
    Go::Runtime::GetCBaseObject(handle, object);

    static auto removeEntity = GET_FUNC(Module, "altRemoveBaseObject", void(*)(CBaseObject*));
    if (removeEntity == nullptr) {
        alt::ICore::Instance().LogError("Could not call altRemoveBaseObject.");
        return;
    }
    removeEntity(object);
}
