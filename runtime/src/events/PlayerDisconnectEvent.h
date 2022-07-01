#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class PlayerDisconnectEvent : public Go::IEvent
            {
            public:
                explicit PlayerDisconnectEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}
