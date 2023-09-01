#include "NetOwnerChangeEvent.h"

Go::NetOwnerChangeEvent::NetOwnerChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::NetOwnerChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altNetOwnerChangeEvent", void (*)(CBaseObject *entity, CBaseObject *owner, CBaseObject *oldOwner));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call NetOwnerChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CNetOwnerChangeEvent *>(ev);

    CBaseObject entity;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &entity);
    CBaseObject newOwner;
    Go::Runtime::GetCBaseObject(event->GetNewOwner(), &newOwner);
    CBaseObject oldOwner;
    Go::Runtime::GetCBaseObject(event->GetOldOwner(), &oldOwner);

    call(&entity, &newOwner, &oldOwner);
}
