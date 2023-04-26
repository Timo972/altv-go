#pragma once

#include "Main.h"
#include "Library.h"
#include "GoRuntime.h"
#include "GoEventManager.h"
#include "GoExportManager.h"

#include <list>

#include "events/PlayerConnectEvent.h"
#include "events/PlayerDisconnectEvent.h"
#include "events/PlayerDamageEvent.h"
#include "events/PlayerDeathEvent.h"
#include "events/PlayerEnterVehicleEvent.h"
#include "events/PlayerLeaveVehicleEvent.h"
#include "events/PlayerChangeVehicleSeatEvent.h"
#include "events/ConsoleCommandEvent.h"
#include "events/WeaponDamageEvent.h"
#include "events/ExplosionEvent.h"
#include "events/ResourceStartEvent.h"
#include "events/ColShapeEvent.h"
#include "events/FireEvent.h"
#include "events/SyncedMetaDataChangeEvent.h"
#include "events/StreamSyncedMetaDataChangeEvent.h"
#include "events/GlobalMetaDataChangeEvent.h"
#include "events/GlobalSyncedMetaDataChangeEvent.h"
#include "events/ResourceStopEvent.h"
#include "events/ResourceErrorEvent.h"
#include "events/VehicleDestroyEvent.h"
#include "events/StartProjectileEvent.h"
#include "events/PlayerWeaponChangeEvent.h"
#include "events/VehicleAttachEvent.h"
#include "events/VehicleDetachEvent.h"
#include "events/NetOwnerChangeEvent.h"
#include "events/PlayerEnteringVehicleEvent.h"
#include "events/ServerScriptEvent.h"
#include "events/ClientScriptEvent.h"
#include "events/VehicleDamageEvent.h"
#include "events/ConnectionQueueAddEvent.h"
#include "events/ConnectionQueueRemoveEvent.h"
#include "events/ServerStartedEvent.h"
#include "events/LocalSyncedMetaDataChangeEvent.h"
#include "events/MetaDataChangeEvent.h"
#include "events/PlayerRequestControlEvent.h"
#include "events/PlayerChangeAnimationEvent.h"
#include "events/PlayerChangeInteriorEvent.h"

namespace Go
{
class Resource : public alt::IResource::Impl, public Go::EventsManager, public Go::ExportsManager
    {
    private:
        Go::Runtime *_runtime;
        alt::IResource *_resource;
        std::list<alt::IBaseObject*> _entities;

    public:
        ModuleLibrary *Module = nullptr;
        Resource(Go::Runtime *runtime, alt::IResource *resource);
        ~Resource() override = default;
        bool Start() override;
        bool Stop() override;
        void OnEvent(const alt::CEvent *ev) override;
        void OnTick() override;
        void OnCreateBaseObject(alt::IBaseObject* handle) override;
        void OnRemoveBaseObject(alt::IBaseObject* handle) override;

        inline bool AddEntity(alt::IBaseObject* baseObject)
        {
            auto entityFound = std::find(this->_entities.begin(), this->_entities.end(), baseObject) != this->_entities.end();
            if (entityFound)
                return false;

            this->_entities.push_back(baseObject);
            return true;
        }

        inline bool RemoveEntity(alt::IBaseObject* baseObject)
        {
            auto it = std::find(this->_entities.begin(), this->_entities.end(), baseObject);
            if (it == this->_entities.end())
                return false;

            this->_entities.erase(it);
            return true;
        }

        inline bool HasEntity(alt::IBaseObject* baseObject) {
            return std::find(this->_entities.begin(), this->_entities.end(), baseObject) != this->_entities.end();
        }
    };
}