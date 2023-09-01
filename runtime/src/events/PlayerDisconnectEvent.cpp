#include "PlayerDisconnectEvent.h"
#include "GoRuntime.h"

Go::PlayerDisconnectEvent::PlayerDisconnectEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerDisconnectEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerDisconnectEvent", void (*)(CBaseObject *playerObject, const char *reason));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerDisconnectEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerDisconnectEvent *>(ev);

    CBaseObject *player;
    Go::Runtime::GetCBaseObject(event->GetTarget(), player);

    auto reason = event->GetReason().c_str();

    call(player, reason);
}
