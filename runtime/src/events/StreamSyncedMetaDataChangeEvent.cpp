#include "StreamSyncedMetaDataChangeEvent.h"
#include "GoRuntime.h"

Go::StreamSyncedMetaDataChangeEvent::StreamSyncedMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::StreamSyncedMetaDataChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altStreamSyncedMetaDataChangeEvent", void (*)(CBaseObject *entity, const char* key, CArray oldValue, CArray newValue));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call StreamSyncedMetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CStreamSyncedMetaDataChangeEvent *>(ev);
    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();
    
    CBaseObject entity;
    Go::Runtime::GetCBaseObject(event->GetTarget(), &entity);

    auto newValue = Go::Runtime::EncodeMValue(newValueMeta);
    auto oldValue = Go::Runtime::EncodeMValue(oldValueMeta);

    call(&entity, key, oldValue, newValue);

    // TODO: fee Arrays
}
