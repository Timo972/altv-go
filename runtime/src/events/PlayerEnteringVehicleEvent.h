#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class PlayerEnteringVehicleEvent : public Go::IEvent
            {
            public:
                explicit PlayerEnteringVehicleEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}