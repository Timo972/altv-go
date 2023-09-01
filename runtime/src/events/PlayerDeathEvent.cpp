#include "PlayerDeathEvent.h"

Go::PlayerDeathEvent::PlayerDeathEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerDeathEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerDeathEvent", bool (*)(CBaseObject *playerObject, CBaseObject *killerObject, unsigned long weapon));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerDeathEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerDeathEvent *>(ev);

    CBaseObject player;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &player);
    CBaseObject killer;
    Go::Runtime::GetCBaseObject(event->GetKiller(), &killer);

    auto weapon = event->GetWeapon();

    call(&player, &killer, weapon);
}
