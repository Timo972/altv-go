#include "MetaDataChangeEvent.h"
// cpp-sdk does not include it by default??
#include "events/CMetaDataChangeEvent.h"
#include "GoRuntime.h"

Go::MetaDataChangeEvent::MetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::MetaDataChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altMetaDataChangeEvent", void (*)(const char* key, CArray oldValue, CArray newValue));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call MetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CMetaChangeEvent *>(ev);
    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();

    auto newValue = Go::Runtime::EncodeMValue(newValueMeta);
    auto oldValue = Go::Runtime::EncodeMValue(oldValueMeta);

    call(key, oldValue, newValue);

    // TODO: free Arrays
}
