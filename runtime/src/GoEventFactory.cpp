#include "GoEventFactory.h"

Go::IEvent::IEvent(ModuleLibrary *module) : Library(module) { }

void Go::EventFactory::CallEvent(const alt::CEvent *ev) {
    auto event = EventsMap.find(static_cast<const EventType>(ev->GetType()));

    if(event == EventsMap.end())
    {
        return;
    }

    event->second->Call(ev);
}

void Go::EventFactory::RegisterEventHandler(Go::EventType type, Go::IEvent *handler) {
    EventsMap.insert({{type, handler}});
}
