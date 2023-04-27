#include "PlayerConnectEvent.h"
#include "GoRuntime.h"

Go::PlayerConnectEvent::PlayerConnectEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerConnectEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerConnectEvent", void (*)(Entity playerObject));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerConnectEvent.");
        return;
    }

    auto event = static_cast<const alt::CPlayerConnectEvent *>(ev);
    auto player = Go::Runtime::GetEntity(event->GetTarget());

    call(player);
}
