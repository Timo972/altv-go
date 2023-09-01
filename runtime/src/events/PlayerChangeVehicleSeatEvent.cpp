#include "PlayerChangeVehicleSeatEvent.h"
#include "GoRuntime.h"

Go::PlayerChangeVehicleSeatEvent::PlayerChangeVehicleSeatEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerChangeVehicleSeatEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerChangeVehicleSeatEvent", void (*)(CBaseObject *playerObject, CBaseObject *vehicleObject, unsigned char oldSeat, unsigned char newSeat));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerChangeVehicleSeatEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerChangeVehicleSeatEvent *>(ev);

    CBaseObject *player;
    Go::Runtime::GetCBaseObject(event->GetPlayer(), player);
    CBaseObject *vehicle;
    Go::Runtime::GetCBaseObject(event->GetTarget(), vehicle);

    auto newSeat = event->GetNewSeat();
    auto oldSeat = event->GetOldSeat();

    call(player, vehicle, oldSeat, newSeat);
}
