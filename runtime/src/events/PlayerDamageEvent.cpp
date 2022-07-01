#include "PlayerDamageEvent.h"

Go::PlayerDamageEvent::PlayerDamageEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerDamageEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerDamageEvent", bool (*)(alt::IPlayer *playerObject, Entity attackerObject, unsigned short healthDamage, unsigned short armourDamage, unsigned long weapon));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerDamageEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerDamageEvent *>(ev);
    auto player = event->GetTarget().Get();
    auto attacker = event->GetAttacker();
    auto healthDamage = event->GetHealthDamage();
    auto armourDamage = event->GetArmourDamage();
    auto weapon = event->GetWeapon();

    Entity e = Go::Runtime::GetEntity(attacker);

    call(player, e, healthDamage, armourDamage, weapon);
}
