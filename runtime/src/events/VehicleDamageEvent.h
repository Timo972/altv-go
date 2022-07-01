#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class VehicleDamageEvent : public Go::IEvent
    {
    public:
        explicit VehicleDamageEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}
