#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class MetaDataChangeEvent : public Go::IEvent
    {
    public:
        explicit MetaDataChangeEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}