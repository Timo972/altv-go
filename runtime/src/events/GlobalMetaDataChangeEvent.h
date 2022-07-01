#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class GlobalMetaDataChangeEvent : public Go::IEvent
            {
            public:
                explicit GlobalMetaDataChangeEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}