#include "PlayerChangeVehicleSeatEvent.h"
#include "GoRuntime.h"

Go::PlayerChangeVehicleSeatEvent::PlayerChangeVehicleSeatEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerChangeVehicleSeatEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerChangeVehicleSeatEvent", void (*)(Entity playerObject, Entity vehicleObject, unsigned char oldSeat, unsigned char newSeat));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerChangeVehicleSeatEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerChangeVehicleSeatEvent *>(ev);
    auto vehicle = Go::Runtime::GetEntity(event->GetTarget());
    auto player = Go::Runtime::GetEntity(event->GetPlayer());
    auto newSeat = event->GetNewSeat();
    auto oldSeat = event->GetOldSeat();

    call(player, vehicle, oldSeat, newSeat);
}
