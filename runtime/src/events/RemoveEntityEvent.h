#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class RemoveEntityEvent : public Go::IEvent
            {
            public:
                explicit RemoveEntityEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}
