#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class VehicleAttachEvent : public Go::IEvent
            {
            public:
                explicit VehicleAttachEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}