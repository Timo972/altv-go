#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class FireEvent : public Go::IEvent
            {
            public:
                explicit FireEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}