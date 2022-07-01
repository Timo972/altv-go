#include "NetOwnerChangeEvent.h"

Go::NetOwnerChangeEvent::NetOwnerChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::NetOwnerChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altNetOwnerChangeEvent", void (*)(Entity entity, alt::IPlayer* owner, alt::IPlayer* oldOwner));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call NetOwnerChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CNetOwnerChangeEvent *>(ev);
    auto entity = event->GetTarget();
    auto newOwner = event->GetNewOwner().Get();
    auto oldOwner = event->GetOldOwner().Get();

    Entity e = Go::Runtime::GetEntity(entity);

    call(e, newOwner, oldOwner);
}
