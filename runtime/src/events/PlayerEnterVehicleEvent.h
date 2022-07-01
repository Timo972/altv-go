#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class PlayerEnterVehicleEvent : public Go::IEvent
            {
            public:
                explicit PlayerEnterVehicleEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}
