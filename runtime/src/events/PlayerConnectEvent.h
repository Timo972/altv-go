#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class PlayerConnectEvent : public Go::IEvent
    {
    public:
        explicit PlayerConnectEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}
