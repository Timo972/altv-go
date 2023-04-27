#include "ResourceErrorEvent.h"

Go::ResourceErrorEvent::ResourceErrorEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::ResourceErrorEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altResourceErrorEvent", void (*)(char* name));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call ResourceErrorEvent.");
        return;
    }

    auto event = static_cast<const alt::CResourceErrorEvent *>(ev);

    auto resource = event->GetResource();
    auto name = resource->GetName().c_str();

    call(const_cast<char *>(name));
}
