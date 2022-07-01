#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
    class GlobalSyncedMetaDataChangeEvent : public Go::IEvent
            {
            public:
                explicit GlobalSyncedMetaDataChangeEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}