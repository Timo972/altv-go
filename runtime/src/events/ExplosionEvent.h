#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class ExplosionEvent : public Go::IEvent
            {
            public:
                explicit ExplosionEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}