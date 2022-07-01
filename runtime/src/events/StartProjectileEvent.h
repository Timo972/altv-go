#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class StartProjectileEvent : public Go::IEvent
            {
            public:
                explicit StartProjectileEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}