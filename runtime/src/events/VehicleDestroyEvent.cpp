#include "VehicleDestroyEvent.h"
#include "GoRuntime.h"

Go::VehicleDestroyEvent::VehicleDestroyEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::VehicleDestroyEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altVehicleDestroyEvent", void (*)(CBaseObject *vehicle));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call VehicleDestroyEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CVehicleDestroyEvent *>(ev);

    CBaseObject vehicle;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &vehicle);

    call(&vehicle);
}
