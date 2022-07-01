#include "ServerStartedEvent.h"

Go::ServerStartedEvent::ServerStartedEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::ServerStartedEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altServerStartedEvent", void (*)());

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call ServerStartedEvent.");
        return;
    }

    call();
}
