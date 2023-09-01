#include "PlayerEnterVehicleEvent.h"
#include "GoRuntime.h"

Go::PlayerEnterVehicleEvent::PlayerEnterVehicleEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerEnterVehicleEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerEnterVehicleEvent", void (*)(CBaseObject *playerObject, CBaseObject *vehicleObject, unsigned char seat));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerEnterVehicleEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerEnterVehicleEvent *>(ev);

    CBaseObject vehicle;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &vehicle);
    CBaseObject player;
    Go::Runtime::GetCBaseObject(event->GetPlayer(), &player);

    auto seat = event->GetSeat();

    call(&player, &vehicle, seat);
}
