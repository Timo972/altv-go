#include "WeaponDamageEvent.h"

Go::WeaponDamageEvent::WeaponDamageEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::WeaponDamageEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altWeaponDamageEvent", int (*)(CBaseObject source, CBaseObject target, unsigned long weapon, unsigned short damage, CPosition offset, short bodyPart));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call WeaponDamageEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CWeaponDamageEvent *>(ev);
    auto target = Go::Runtime::GetCBaseObject(event->GetTarget());
    auto source = Go::Runtime::GetCBaseObject(event->GetSource());
    auto bodyPart = event->GetBodyPart();
    auto damage = event->GetDamageValue();
    auto weapon = event->GetWeaponHash();
    auto offset = event->GetShotOffset();

    CPosition cOffset;
    cOffset.x = offset[0];
    cOffset.y = offset[1];
    cOffset.z = offset[2];

    auto cancel = call(source, target, weapon, damage, cOffset, static_cast<short>(bodyPart));

    if(cancel == 0) {
        event->Cancel();
    }
}
