#include "GlobalSyncedMetaDataChangeEvent.h"
#include "GoRuntime.h"

Go::GlobalSyncedMetaDataChangeEvent::GlobalSyncedMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::GlobalSyncedMetaDataChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altGlobalSyncedMetaDataChangeEvent", void (*)(const char* key, Array newValue, Array oldValue));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call GlobalSyncedMetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CGlobalSyncedMetaDataChangeEvent *>(ev);
    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();

    auto newValue = Go::Runtime::MValueToProtoBytes(newValueMeta);
    auto oldValue = Go::Runtime::MValueToProtoBytes(oldValueMeta);

    call(key, newValue, oldValue);

#ifdef _WIN32
    delete[] newValue.array;
    delete[] oldValue.array;
#endif
}
