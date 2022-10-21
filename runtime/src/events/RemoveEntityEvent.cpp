#include "RemoveEntityEvent.h"
#include "GoRuntime.h"

Go::RemoveEntityEvent::RemoveEntityEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::RemoveEntityEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altRemoveEntityEvent", void (*)(Entity entityObject));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call RemoveEntityEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CRemoveEntityEvent *>(ev);
    auto entity = Go::Runtime::GetEntity(event->GetEntity());

    call(entity);
}
