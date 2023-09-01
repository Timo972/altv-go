#include "ColShapeEvent.h"

Go::ColShapeEvent::ColShapeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::ColShapeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altColShapeEvent", void (*)(CBaseObject colshape, CBaseObject entity, int state));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call altColShapeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CColShapeEvent *>(ev);
    auto state = event->GetState();

    auto colShape = Go::Runtime::GetCBaseObject(event->GetTarget());
    auto entity = Go::Runtime::GetCBaseObject(event->GetEntity());

    call(colShape, entity, state);
}
