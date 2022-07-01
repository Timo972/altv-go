#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class PlayerRequestControlEvent : public Go::IEvent
    {
    public:
        explicit PlayerRequestControlEvent(ModuleLibrary* module);
        void Call(const alt::CEvent* ev) override;
    };
}
