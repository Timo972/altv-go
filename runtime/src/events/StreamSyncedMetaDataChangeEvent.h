#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"
#include "GoRuntime.h"

namespace Go
{
    class StreamSyncedMetaDataChangeEvent : public Go::IEvent
            {
            public:
                explicit StreamSyncedMetaDataChangeEvent(ModuleLibrary *module);
                void Call(const alt::CEvent *ev) override;
            };
}