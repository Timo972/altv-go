#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class LocalSyncedMetaDataChangeEvent : public Go::IEvent
    {
    public:
        explicit LocalSyncedMetaDataChangeEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}