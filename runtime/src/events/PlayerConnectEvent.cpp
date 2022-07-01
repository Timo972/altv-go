#include "PlayerConnectEvent.h"

Go::PlayerConnectEvent::PlayerConnectEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerConnectEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerConnectEvent", void (*)(alt::IPlayer *playerObject));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerConnectEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerConnectEvent *>(ev);
    auto player = event->GetTarget().Get();

    call(player);
}
