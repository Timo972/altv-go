#include "ConnectionQueueAddEvent.h"

Go::ConnectionQueueAddEvent::ConnectionQueueAddEvent(ModuleLibrary *module) : IEvent(module) {}

void Go::ConnectionQueueAddEvent::Call(const alt::CEvent *ev) {
    static auto call = GET_FUNC(Library, "altConnectionQueueAddEvent",
                                int (*)(void *handle, connectionInfo info));

    if (call == nullptr) {
        alt::ICore::Instance().LogError("Couldn't not call ConnectionQueueAddEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CConnectionQueueAddEvent *>(ev);
    auto info = event->GetConnectionInfo();
    auto conn = Go::Runtime::GetConnectionInfo(info);

    int cancel = call(info.Get(), conn);

    if (cancel == 0) {
        event->Cancel();
    }
}
