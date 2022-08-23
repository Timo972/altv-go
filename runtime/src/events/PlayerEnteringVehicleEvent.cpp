#include "PlayerEnteringVehicleEvent.h"
#include "GoRuntime.h"

Go::PlayerEnteringVehicleEvent::PlayerEnteringVehicleEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::PlayerEnteringVehicleEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altPlayerEnteringVehicleEvent", void (*)(Entity player, Entity vehicle, unsigned short seat));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerEnteringVehicleEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerEnteringVehicleEvent *>(ev);
    auto vehicle = Go::Runtime::GetEntity(event->GetTarget());
    auto player = Go::Runtime::GetEntity(event->GetPlayer());
    auto seat = event->GetSeat();

    call(player, vehicle, seat);
}
