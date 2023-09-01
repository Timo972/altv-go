#include "SyncedMetaDataChangeEvent.h"

Go::SyncedMetaDataChangeEvent::SyncedMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::SyncedMetaDataChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altSyncedMetaDataChangeEvent", void (*)(CBaseObject *entity, const char* key, CArray oldValue, CArray newValue));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call SyncedMetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CSyncedMetaDataChangeEvent *>(ev);

    CBaseObject *entity; 
    Go::Runtime::GetCBaseObject(event->GetTarget(), entity);

    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();

    auto newValue = Go::Runtime::EncodeMValue(newValueMeta);
    auto oldValue = Go::Runtime::EncodeMValue(oldValueMeta);

    call(entity, key, oldValue, newValue);

    // TODO: free Arrays
}
