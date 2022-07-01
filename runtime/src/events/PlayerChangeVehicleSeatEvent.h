#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class PlayerChangeVehicleSeatEvent : public Go::IEvent
            {
            public:
                explicit PlayerChangeVehicleSeatEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}
