#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class ConnectionQueueAddEvent : public Go::IEvent
    {
    public:
        explicit ConnectionQueueAddEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}
