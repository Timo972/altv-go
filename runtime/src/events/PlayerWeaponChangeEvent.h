#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class PlayerWeaponChangeEvent : public Go::IEvent
            {
            public:
                explicit PlayerWeaponChangeEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}