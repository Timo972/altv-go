#include "VehicleDamageEvent.h"

Go::VehicleDamageEvent::VehicleDamageEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::VehicleDamageEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altVehicleDamageEvent", bool (*)(CBaseObject *vehicle, CBaseObject *attacker, unsigned bodyHealthDamage, unsigned additionalBodyHealthDamage, unsigned engineHealthDamage, unsigned petrolTankHealthDamage, unsigned damageWidth));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call VehicleDamageEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CVehicleDamageEvent *>(ev);

    CBaseObject vehicle;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &vehicle);
    CBaseObject attacker;
    Go::Runtime::GetCBaseObject(event->GetDamager(), &attacker);

    auto bodyHealthDamage = event->GetBodyHealthDamage();
    auto bodyAdditionalHealthDamage = event->GetBodyAdditionalHealthDamage();
    auto engineHealthDamage = event->GetEngineHealthDamage();
    auto petrolTankHealthDamage = event->GetPetrolTankHealthDamage();
    auto damageWidth = event->GetDamagedWith();

    call(&vehicle, &attacker, bodyHealthDamage, bodyAdditionalHealthDamage, engineHealthDamage, petrolTankHealthDamage, damageWidth);
}
