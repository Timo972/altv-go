#include "VehicleAttachEvent.h"
#include "GoRuntime.h"

Go::VehicleAttachEvent::VehicleAttachEvent(ModuleLibrary *module) : IEvent(module) {}

void Go::VehicleAttachEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altVehicleAttachEvent", void (*)(CBaseObject *vehicle, CBaseObject *attachedVehicle));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call VehicleAttachEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CVehicleAttachEvent *>(ev);

    CBaseObject vehicle;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &vehicle);
    CBaseObject attached;
    Go::Runtime::GetCBaseObject(event->GetAttached(), &attached);

    call(&vehicle, &attached);
}
