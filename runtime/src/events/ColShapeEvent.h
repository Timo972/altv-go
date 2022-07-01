#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class ColShapeEvent : public Go::IEvent
            {
            public:
                explicit ColShapeEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}
