#pragma once

#include "Main.h"
#include "GoRuntime.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class ConsoleCommandEvent : public Go::IEvent
            {
            public:
                explicit ConsoleCommandEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}
