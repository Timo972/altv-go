#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class WeaponDamageEvent : public Go::IEvent
            {
            public:
                explicit WeaponDamageEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}