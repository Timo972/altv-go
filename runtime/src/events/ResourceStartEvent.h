#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class ResourceStartEvent : public Go::IEvent
            {
            public:
                explicit ResourceStartEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}