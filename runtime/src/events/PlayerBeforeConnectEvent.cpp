#include "PlayerBeforeConnectEvent.h"

Go::PlayerBeforeConnectEvent::PlayerBeforeConnectEvent(ModuleLibrary *module) : IEvent(module) {}

void Go::PlayerBeforeConnectEvent::Call(const alt::CEvent *ev) {
    static auto call = GET_FUNC(Library, "altPlayerBeforeConnectEvent",
                                void (*)(void *connectionHandle, connectionInfo info, const char *reason));

    if (call == nullptr) {
        alt::ICore::Instance().LogError("Couldn't not call PlayerBeforeConnectEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CPlayerBeforeConnectEvent *>(ev);
    auto info = event->GetConnectionInfo();
    auto reason = event->GetReason().c_str();
    auto conn = Go::Runtime::GetConnectionInfo(info);

    call(info.Get(), conn, reason);
}
