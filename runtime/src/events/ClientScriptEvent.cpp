#include "ClientScriptEvent.h"
#include "GoRuntime.h"

Go::ClientScriptEvent::ClientScriptEvent(ModuleLibrary *module) : IEvent(module) {}

void Go::ClientScriptEvent::Call(const alt::CEvent *ev) {
    static auto call = GET_FUNC(Library, "altClientScriptEvent", bool (*)(CBaseObject player, const char *name, CArray args));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't call ClientScriptEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CClientScriptEvent*>(ev);
    auto player = Go::Runtime::GetCBaseObject(event->GetTarget());
    auto name = event->GetName().c_str();
    const auto& args = event->GetArgs();

    auto data = Go::Runtime::EncodeMValueArgs(args);

    call(player, name, data);

    // TODO: free Array
}
