#include "ColShapeEvent.h"

Go::ColShapeEvent::ColShapeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::ColShapeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altColShapeEvent", void (*)(Entity colshape, Entity entity, int state));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call altColShapeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CColShapeEvent *>(ev);
    auto state = event->GetState();

    auto colShape = Go::Runtime::GetEntity(event->GetTarget());
    auto entity = Go::Runtime::GetEntity(event->GetEntity());

    Entity e = Go::Runtime::GetEntity(entity);


    call(colShape, e, state);
}
