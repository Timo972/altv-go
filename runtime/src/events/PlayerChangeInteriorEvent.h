#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "events/CPlayerChangeInteriorEvent.h"

namespace Go
{
    class PlayerChangeInteriorEvent : public Go::IEvent
    {
    public:
        explicit PlayerChangeInteriorEvent(ModuleLibrary* module);
        void Call(const alt::CEvent* ev) override;
    };
}
