#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class PlayerLeaveVehicleEvent : public Go::IEvent
            {
            public:
                explicit PlayerLeaveVehicleEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}
