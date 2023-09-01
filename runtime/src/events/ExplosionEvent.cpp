#include "ExplosionEvent.h"

Go::ExplosionEvent::ExplosionEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::ExplosionEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altExplosionEvent", int (*)(CBaseObject source, CBaseObject target, CPosition position, short explosionType, unsigned int explosionFX));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call ExplosionEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CExplosionEvent *>(ev);
    auto target = event->GetTarget();
    auto source = Go::Runtime::GetCBaseObject(event->GetSource());
    auto pos = event->GetPosition();
    auto expFX = event->GetExplosionFX();
    auto expType = event->GetExplosionType();

    CBaseObject e = Go::Runtime::GetCBaseObject(target);

    CPosition cPos;
    cPos.x = pos.x;
    cPos.y = pos.y;
    cPos.z = pos.z;

    auto cancel = call(source, e, cPos, static_cast<short>(expType), expFX);

    if(cancel == 0) {
        event->Cancel();
    }
}
