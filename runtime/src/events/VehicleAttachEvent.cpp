#include "VehicleAttachEvent.h"
#include "GoRuntime.h"

Go::VehicleAttachEvent::VehicleAttachEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::VehicleAttachEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altVehicleAttachEvent", void (*)(Entity vehicle, Entity attachedVehicle));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call VehicleAttachEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CVehicleAttachEvent *>(ev);
    auto vehicle = Go::Runtime::GetEntity(event->GetTarget());
    auto attached = Go::Runtime::GetEntity(event->GetAttached());

    call(vehicle, attached);
}
