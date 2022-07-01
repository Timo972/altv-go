#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class PlayerDamageEvent : public Go::IEvent
            {
            public:
                explicit PlayerDamageEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}
