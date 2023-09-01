#include "VehicleDetachEvent.h"
#include "GoRuntime.h"

Go::VehicleDetachEvent::VehicleDetachEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::VehicleDetachEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altVehicleDetachEvent", void (*)(CBaseObject *vehicle, CBaseObject *detachedVehicle));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call VehicleDetachEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CVehicleDetachEvent *>(ev);

    CBaseObject vehicle;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &vehicle);
    CBaseObject detached;
    Go::Runtime::GetCBaseObject(event->GetDetached(), &detached);

    call(&vehicle, &detached);
}
