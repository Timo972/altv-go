#include "LocalSyncedMetaDataChangeEvent.h"
#include "GoRuntime.h"

Go::LocalSyncedMetaDataChangeEvent::LocalSyncedMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) {}

void Go::LocalSyncedMetaDataChangeEvent::Call(const alt::CEvent *ev) {
    static auto call = GET_FUNC(Library, "altLocalSyncedMetaDataChangeEvent",
                                void(*)(Entity p, const char* key, GoValue oldValue, GoValue newValue));

    if (call == nullptr) {
        alt::ICore::Instance().LogError("Could not call LocalSyncedMetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CLocalMetaDataChangeEvent *>(ev);
    auto player = Go::Runtime::GetEntity(event->GetTarget());
    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();

    GoValue newValue{};
    GoValue oldValue{};
    Go::Runtime::MValueToGo(newValueMeta, &newValue);
    Go::Runtime::MValueToGo(oldValueMeta, &oldValue);

    call(player, key, oldValue, newValue);

#ifdef _WIN32
    delete[] newValue.array;
    delete[] oldValue.array;
#endif
}
