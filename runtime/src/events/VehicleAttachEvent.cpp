#include "VehicleAttachEvent.h"

Go::VehicleAttachEvent::VehicleAttachEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::VehicleAttachEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altVehicleAttachEvent", void (*)(alt::IVehicle* vehicle, alt::IVehicle* attachedVehicle));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call VehicleAttachEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CVehicleAttachEvent *>(ev);
    auto vehicle = event->GetTarget().Get();
    auto attached = event->GetAttached().Get();

    call(vehicle, attached);
}
