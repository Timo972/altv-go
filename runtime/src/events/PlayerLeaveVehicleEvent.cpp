#include "PlayerLeaveVehicleEvent.h"
#include "GoRuntime.h"

Go::PlayerLeaveVehicleEvent::PlayerLeaveVehicleEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerLeaveVehicleEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerLeaveVehicleEvent", void (*)(Entity playerObject, Entity vehicleObject, unsigned char seat));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerLeaveVehicleEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerLeaveVehicleEvent *>(ev);
    auto vehicle = Go::Runtime::GetEntity(event->GetTarget());
    auto player = Go::Runtime::GetEntity(event->GetPlayer());
    auto seat = event->GetSeat();

    call(player, vehicle, seat);
}
