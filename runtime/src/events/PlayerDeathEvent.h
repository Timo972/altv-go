#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class PlayerDeathEvent : public Go::IEvent
            {
            public:
                explicit PlayerDeathEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}
