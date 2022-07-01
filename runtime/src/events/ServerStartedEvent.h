#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class ServerStartedEvent : public Go::IEvent
    {
    public:
        explicit ServerStartedEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}