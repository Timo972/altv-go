#include "SyncedMetaDataChangeEvent.h"

Go::SyncedMetaDataChangeEvent::SyncedMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::SyncedMetaDataChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altSyncedMetaDataChangeEvent", void (*)(Entity entity, const char* key, Array newValue, Array oldValue));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call SyncedMetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CSyncedMetaDataChangeEvent *>(ev);
    auto entity = event->GetTarget();
    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();

    Entity e = Go::Runtime::GetEntity(entity);

    auto newValue = Go::Runtime::MValueToProtoBytes(newValueMeta);
    auto oldValue = Go::Runtime::MValueToProtoBytes(oldValueMeta);

    call(e, key, newValue, oldValue);

#ifdef _WIN32
    delete[] newValue.array;
    delete[] oldValue.array;
#endif
}
