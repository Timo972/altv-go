#include "VehicleDetachEvent.h"

Go::VehicleDetachEvent::VehicleDetachEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::VehicleDetachEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altVehicleDetachEvent", void (*)(alt::IVehicle* vehicle, alt::IVehicle* detachedVehicle));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call VehicleDetachEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CVehicleDetachEvent *>(ev);
    auto vehicle = event->GetTarget().Get();
    auto detached = event->GetDetached().Get();

    call(vehicle, detached);
}
