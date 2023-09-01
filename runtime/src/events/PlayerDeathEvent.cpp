#include "PlayerDeathEvent.h"

Go::PlayerDeathEvent::PlayerDeathEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerDeathEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerDeathEvent", bool (*)(CBaseObject playerObject, CBaseObject killerObject, unsigned long weapon));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerDeathEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerDeathEvent *>(ev);
    auto player = Go::Runtime::GetCBaseObject(event->GetTarget());
    auto killer = Go::Runtime::GetCBaseObject(event->GetKiller());
    auto weapon = event->GetWeapon();

    call(player, killer, weapon);
}
