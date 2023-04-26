#include "StreamSyncedMetaDataChangeEvent.h"
#include "GoRuntime.h"

Go::StreamSyncedMetaDataChangeEvent::StreamSyncedMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::StreamSyncedMetaDataChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altStreamSyncedMetaDataChangeEvent", void (*)(Entity entity, const char* key, GoValue oldValue, GoValue newValue));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call StreamSyncedMetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CStreamSyncedMetaDataChangeEvent *>(ev);
    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();

    Entity e = Go::Runtime::GetBaseObject(event->GetTarget());

    GoValue newValue{};
    GoValue oldValue{};
    Go::Runtime::MValueToGo(newValueMeta, &newValue);
    Go::Runtime::MValueToGo(oldValueMeta, &oldValue);

    call(e, key, oldValue, newValue);

    // TODO: fee GoValues
}
