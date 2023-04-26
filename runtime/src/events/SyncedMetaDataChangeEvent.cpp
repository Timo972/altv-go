#include "SyncedMetaDataChangeEvent.h"

Go::SyncedMetaDataChangeEvent::SyncedMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::SyncedMetaDataChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altSyncedMetaDataChangeEvent", void (*)(Entity entity, const char* key, GoValue oldValue, GoValue newValue));

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

    Entity e = Go::Runtime::GetBaseObject(entity);

    GoValue newValue{};
    GoValue oldValue{};
    Go::Runtime::MValueToGo(newValueMeta, &newValue);
    Go::Runtime::MValueToGo(oldValueMeta, &oldValue);

    call(e, key, oldValue, newValue);

    // TODO: free GoValues
}
