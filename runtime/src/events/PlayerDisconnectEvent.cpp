#include "PlayerDisconnectEvent.h"

Go::PlayerDisconnectEvent::PlayerDisconnectEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerDisconnectEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerDisconnectEvent", void (*)(alt::IPlayer *playerObject, const char *reason));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerDisconnectEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerDisconnectEvent *>(ev);
    auto player = event->GetTarget().Get();
    auto reason = event->GetReason().c_str();

    call(player, reason);
}
