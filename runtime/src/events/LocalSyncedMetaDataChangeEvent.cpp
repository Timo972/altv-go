#include "LocalSyncedMetaDataChangeEvent.h"
#include "GoRuntime.h"

Go::LocalSyncedMetaDataChangeEvent::LocalSyncedMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) {}

void Go::LocalSyncedMetaDataChangeEvent::Call(const alt::CEvent *ev) {
    static auto call = GET_FUNC(Library, "altLocalSyncedMetaDataChangeEvent",
                                void(*)(void *p, const char* key, Array newValue, Array oldValue));

    if (call == nullptr) {
        alt::ICore::Instance().LogError("Could not call LocalSyncedMetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CLocalMetaDataChangeEvent *>(ev);
    auto player = event->GetTarget().Get();
    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();

    auto newValue = Go::Runtime::MValueToProtoBytes(newValueMeta);
    auto oldValue = Go::Runtime::MValueToProtoBytes(oldValueMeta);

    call(player, key, newValue, oldValue);

#ifdef _WIN32
    delete[] newValue.array;
    delete[] oldValue.array;
#endif
}
