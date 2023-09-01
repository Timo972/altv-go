#include "PlayerDamageEvent.h"

Go::PlayerDamageEvent::PlayerDamageEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerDamageEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerDamageEvent", bool (*)(CBaseObject playerObject, CBaseObject attackerObject, unsigned short healthDamage, unsigned short armourDamage, unsigned long weapon));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerDamageEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerDamageEvent *>(ev);
    auto player = Go::Runtime::GetCBaseObject(event->GetTarget());
    auto attacker = event->GetAttacker();
    auto healthDamage = event->GetHealthDamage();
    auto armourDamage = event->GetArmourDamage();
    auto weapon = event->GetWeapon();

    CBaseObject e = Go::Runtime::GetCBaseObject(attacker);

    call(player, e, healthDamage, armourDamage, weapon);
}
