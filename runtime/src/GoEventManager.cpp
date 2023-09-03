#include "GoEventManager.h"

bool Go::EventsManager::RegisterEvent(alt::CEvent::Type type)
{
    if (IsEventRegistered(type))
        return true;
        
    _registeredEvents.push_back(type);
    alt::ICore::Instance().ToggleEvent(type, true);
    return true;
}

bool Go::EventsManager::UnregisterEvent(alt::CEvent::Type type)
{
    auto i = std::find(_registeredEvents.begin(), _registeredEvents.end(), type);

    if (i == _registeredEvents.end())
        return false;

    _registeredEvents.erase(i);
    alt::ICore::Instance().ToggleEvent(type, false);
    return true;
}

bool Go::EventsManager::IsEventRegistered(alt::CEvent::Type type)
{
    return std::find(_registeredEvents.begin(), _registeredEvents.end(), type) != _registeredEvents.end();
}

void Go::EventsManager::NotifyEvent(const alt::CEvent *ev, const std::string &resourceName)
{
    if (!IsEventRegistered(ev->GetType()))
        return;
    
    CallEvent(ev);
}
