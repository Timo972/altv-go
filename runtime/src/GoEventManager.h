#pragma once

#include <iostream>
#include <algorithm>
#include <set>

#include "Main.h"
#include "Library.h"
#include "GoEventFactory.h"

namespace Go
{
class EventsManager : public Go::EventFactory
    {
    private:
        std::vector<alt::CEvent::Type> _registeredEvents;
    public:
        EventsManager() = default;
        bool RegisterEvent(alt::CEvent::Type type);
        bool UnregisterEvent(alt::CEvent::Type type);
        bool IsEventRegistered(alt::CEvent::Type type);
        void NotifyEvent(const alt::CEvent *ev, const std::string &resourceName);
    };
}
