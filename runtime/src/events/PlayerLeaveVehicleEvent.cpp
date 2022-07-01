#include "PlayerLeaveVehicleEvent.h"

Go::PlayerLeaveVehicleEvent::PlayerLeaveVehicleEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerLeaveVehicleEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerLeaveVehicleEvent", void (*)(alt::IPlayer *playerObject, alt::IVehicle *vehicleObject, unsigned char seat));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerLeaveVehicleEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerLeaveVehicleEvent *>(ev);
    auto vehicle = event->GetTarget().Get();
    auto player = event->GetPlayer().Get();
    auto seat = event->GetSeat();

    call(player, vehicle, seat);
}
