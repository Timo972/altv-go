#include "VehicleDamageEvent.h"

Go::VehicleDamageEvent::VehicleDamageEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::VehicleDamageEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altVehicleDamageEvent", bool (*)(alt::IVehicle *vehicle, Entity attacker, unsigned bodyHealthDamage, unsigned additionalBodyHealthDamage, unsigned engineHealthDamage, unsigned petrolTankHealthDamage, unsigned damageWidth));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call VehicleDamageEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CVehicleDamageEvent *>(ev);
    auto vehicle = event->GetTarget().Get();
    auto attacker = event->GetDamager();
    auto bodyHealthDamage = event->GetBodyHealthDamage();
    auto bodyAdditionalHealthDamage = event->GetBodyAdditionalHealthDamage();
    auto engineHealthDamage = event->GetEngineHealthDamage();
    auto petrolTankHealthDamage = event->GetPetrolTankHealthDamage();
    auto damageWidth = event->GetDamagedWith();

    Entity e = Go::Runtime::GetEntity(attacker);

    call(vehicle, e, bodyHealthDamage, bodyAdditionalHealthDamage, engineHealthDamage, petrolTankHealthDamage, damageWidth);
}
