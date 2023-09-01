#include "PlayerDamageEvent.h"

Go::PlayerDamageEvent::PlayerDamageEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerDamageEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerDamageEvent", bool (*)(CBaseObject *playerObject, CBaseObject *attackerObject, unsigned short healthDamage, unsigned short armourDamage, unsigned long weapon));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerDamageEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerDamageEvent *>(ev);

    CBaseObject player;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &player);
    CBaseObject attacker;
    Go::Runtime::GetCBaseObject(event->GetAttacker(), &attacker);

    auto healthDamage = event->GetHealthDamage();
    auto armourDamage = event->GetArmourDamage();
    auto weapon = event->GetWeapon();


    call(&player, &attacker, healthDamage, armourDamage, weapon);
}
