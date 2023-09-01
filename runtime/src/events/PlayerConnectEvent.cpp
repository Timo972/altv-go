#include "PlayerConnectEvent.h"
#include "GoRuntime.h"

Go::PlayerConnectEvent::PlayerConnectEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerConnectEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerConnectEvent", void (*)(CBaseObject *playerObject));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerConnectEvent.");
        return;
    }

    auto event = static_cast<const alt::CPlayerConnectEvent *>(ev);

    CBaseObject player;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &player);

    call(&player);
}
