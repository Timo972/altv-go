#include "FireEvent.h"
#include "GoRuntime.h"

Go::FireEvent::FireEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::FireEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altFireEvent", int (*)(Entity player, Array fires));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call FireEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CFireEvent *>(ev);
    auto source = Go::Runtime::GetEntity(event->GetSource());
    auto fires = event->GetFires();

    Array cFireArr;
    cFireArr.size = fires.size();
    auto args = new FireInfo[cFireArr.size];

    for (uint64_t i = 0; i < cFireArr.size; i++) {
        auto fire = fires[i];
        FireInfo info;
        Position pos;
        pos.x = fire.position.x;
        pos.y = fire.position.y;
        pos.z = fire.position.z;
        info.position = pos;
        info.weaponHash = fire.weaponHash;
        args[i] = info;
    }

    cFireArr.array = args;

    auto cancel = call(source, cFireArr);

#ifdef _WIN32
    delete[] args;
#endif

    if (cancel == 0) {
        event->Cancel();
    }
}
