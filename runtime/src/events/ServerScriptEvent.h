#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go {
    class ServerScriptEvent : public Go::IEvent {
    public:
        explicit ServerScriptEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}
