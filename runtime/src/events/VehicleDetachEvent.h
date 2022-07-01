#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class VehicleDetachEvent : public Go::IEvent
            {
            public:
                explicit VehicleDetachEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}