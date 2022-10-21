#include "PlayerRequestControlEvent.h"
#include "GoRuntime.h"

Go::PlayerRequestControlEvent::PlayerRequestControlEvent(ModuleLibrary* module) : IEvent(module) { }

void Go::PlayerRequestControlEvent::Call(const alt::CEvent* ev)
{
    static auto call = GET_FUNC(Library, "altPlayerRequestControlEvent", bool (*)(Entity playerObject, Entity target));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerRequestControlEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerRequestControlEvent*>(ev);
    auto entity = Go::Runtime::GetEntity(event->GetTarget());
    auto player = Go::Runtime::GetEntity(event->GetPlayer());

    bool ok = call(player, entity);
    if (!ok) 
        event->Cancel();
}
