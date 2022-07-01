#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class VehicleDestroyEvent : public Go::IEvent
            {
            public:
                explicit VehicleDestroyEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}