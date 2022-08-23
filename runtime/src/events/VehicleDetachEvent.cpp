#include "VehicleDetachEvent.h"
#include "GoRuntime.h"

Go::VehicleDetachEvent::VehicleDetachEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::VehicleDetachEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altVehicleDetachEvent", void (*)(Entity vehicle, Entity detachedVehicle));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call VehicleDetachEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CVehicleDetachEvent *>(ev);
    auto vehicle = Go::Runtime::GetEntity(event->GetTarget());
    auto detached = Go::Runtime::GetEntity(event->GetDetached());

    call(vehicle, detached);
}
