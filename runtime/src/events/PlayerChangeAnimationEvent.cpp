#include "PlayerChangeAnimationEvent.h"

Go::PlayerChangeAnimationEvent::PlayerChangeAnimationEvent(ModuleLibrary* module) : IEvent(module) { }

void Go::PlayerChangeAnimationEvent::Call(const alt::CEvent* ev)
{
    static auto call = GET_FUNC(Library, "altPlayerChangeAnimationEvent", void (*)(alt::IPlayer * playerObject, unsigned int oldAnimDict, unsigned int oldAnimName, unsigned int newAnimDict, unsigned int newAnimName));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call PlayerChangeVehicleSeatEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerChangeAnimationEvent*>(ev);

    call(event->GetTarget().Get(), event->GetOldAnimationDict(), event->GetOldAnimationName(), event->GetNewAnimationDict(), event->GetNewAnimationName());
}
