#include "ResourceErrorEvent.h"

Go::ResourceErrorEvent::ResourceErrorEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::ResourceErrorEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altResourceErrorEvent", void (*)(const char* name));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call ResourceErrorEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CResourceErrorEvent *>(ev);
    auto resource = event->GetResource();

    auto name = resource->GetName().c_str();

    call(name);
}
