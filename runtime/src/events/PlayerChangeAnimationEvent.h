#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "events/CPlayerChangeAnimationEvent.h"

namespace Go
{
    class PlayerChangeAnimationEvent : public Go::IEvent
    {
    public:
        explicit PlayerChangeAnimationEvent(ModuleLibrary* module);
        void Call(const alt::CEvent* ev) override;
    };
}
