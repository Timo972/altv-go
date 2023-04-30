#pragma once

#include <iostream>

#include "Main.h"
#include "Library.h"

namespace Go {
    class IEvent {
    public:
        explicit IEvent(ModuleLibrary *module);

        virtual void Call(const alt::CEvent *ev) = 0;

    protected:
        ModuleLibrary *Library;
    };

    class EventFactory {
    private:
        std::unordered_map<alt::CEvent::Type, IEvent *> EventsMap;
    public:
        void RegisterEventHandler(alt::CEvent::Type type, IEvent *handler);

        void CallEvent(const alt::CEvent *ev);
    };
}