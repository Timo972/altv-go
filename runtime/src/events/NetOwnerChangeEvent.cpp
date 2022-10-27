#include "NetOwnerChangeEvent.h"

Go::NetOwnerChangeEvent::NetOwnerChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::NetOwnerChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altNetOwnerChangeEvent", void (*)(Entity entity, Entity owner, Entity oldOwner));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call NetOwnerChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CNetOwnerChangeEvent *>(ev);
    auto entity = Go::Runtime::GetEntity(event->GetTarget());
    auto newOwner = Go::Runtime::GetEntity(event->GetNewOwner());
    auto oldOwner = Go::Runtime::GetEntity(event->GetOldOwner());

    call(entity, newOwner, oldOwner);
}
