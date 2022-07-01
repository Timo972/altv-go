#pragma once

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go {
    class ClientScriptEvent : public Go::IEvent {
    public:
        explicit ClientScriptEvent(ModuleLibrary *module);
        void Call(const alt::CEvent *ev) override;
    };
}