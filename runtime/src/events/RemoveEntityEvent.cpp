#include "RemoveEntityEvent.h"

Go::RemoveEntityEvent::RemoveEntityEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::RemoveEntityEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altRemoveEntityEvent", void (*)(alt::IEntity *entityObject));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call RemoveEntityEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CRemoveEntityEvent *>(ev);
    auto entity = event->GetEntity().Get();

    call(entity);
}
