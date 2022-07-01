#include "ResourceStopEvent.h"

Go::ResourceStopEvent::ResourceStopEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::ResourceStopEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altResourceStopEvent", void (*)(const char* name));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call ResourceStopEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CResourceStopEvent *>(ev);
    auto resource = event->GetResource();

    auto name = resource->GetName().c_str();

    call(name);
}
