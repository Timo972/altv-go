#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class ResourceStopEvent : public Go::IEvent
            {
            public:
                explicit ResourceStopEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}