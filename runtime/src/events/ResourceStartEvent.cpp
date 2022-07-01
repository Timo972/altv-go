#include "ResourceStartEvent.h"

Go::ResourceStartEvent::ResourceStartEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::ResourceStartEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altResourceStartEvent", void (*)(const char* name));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call ResourceStartEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CResourceStartEvent *>(ev);
    auto resource = event->GetResource();

    auto name = resource->GetName().c_str();

    call(name);
}
