#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class ResourceErrorEvent : public Go::IEvent
            {
            public:
                explicit ResourceErrorEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}