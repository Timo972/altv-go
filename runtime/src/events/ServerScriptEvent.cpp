#include "ServerScriptEvent.h"
#include "GoRuntime.h"

Go::ServerScriptEvent::ServerScriptEvent(ModuleLibrary *module) : IEvent(module) {}

void Go::ServerScriptEvent::Call(const alt::CEvent *ev) {
    static auto call = GET_FUNC(Library, "altServerScriptEvent", bool (*)(const char *name, Array args));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call ServerScriptEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CServerScriptEvent*>(ev);
    auto name = event->GetName().c_str();
    const auto& args = event->GetArgs();
 
    auto data = Go::Runtime::MValueArgsToProtoBytes(args);

    call(name, data);

#ifdef _WIN32
    delete[] data.array;
#endif
}
