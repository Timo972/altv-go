#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class PlayerBeforeConnectEvent : public Go::IEvent
    {
    public:
        explicit PlayerBeforeConnectEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}
