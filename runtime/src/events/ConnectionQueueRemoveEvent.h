#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class ConnectionQueueRemoveEvent : public Go::IEvent
    {
    public:
        explicit ConnectionQueueRemoveEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}
