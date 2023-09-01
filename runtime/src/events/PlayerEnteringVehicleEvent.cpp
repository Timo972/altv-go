#include "PlayerEnteringVehicleEvent.h"
#include "GoRuntime.h"

Go::PlayerEnteringVehicleEvent::PlayerEnteringVehicleEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerEnteringVehicleEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerEnteringVehicleEvent", void (*)(CBaseObject *player, CBaseObject *vehicle, unsigned short seat));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerEnteringVehicleEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerEnteringVehicleEvent *>(ev);

    CBaseObject vehicle;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &vehicle);
    CBaseObject player;
    Go::Runtime::GetCBaseObject(event->GetPlayer(), &player);

    auto seat = event->GetSeat();

    call(&player, &vehicle, seat);
}
