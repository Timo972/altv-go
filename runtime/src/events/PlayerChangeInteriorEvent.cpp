#include "PlayerChangeInteriorEvent.h"
#include "GoRuntime.h"

Go::PlayerChangeInteriorEvent::PlayerChangeInteriorEvent(ModuleLibrary* module) : IEvent(module) { }

void Go::PlayerChangeInteriorEvent::Call(const alt::CEvent* ev)
{
    static auto call = GET_FUNC(Library, "altPlayerChangeInteriorEvent", void (*)(Entity playerObject, unsigned int oldInterior, unsigned int newInterior));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerChangeVehicleSeatEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerChangeInteriorEvent*>(ev);

    call(Go::Runtime::GetEntity(event->GetTarget()), event->GetOldInteriorLocation(), event->GetNewInteriorLocation());
}
