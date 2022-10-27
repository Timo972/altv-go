#include "GlobalSyncedMetaDataChangeEvent.h"
#include "GoRuntime.h"

Go::GlobalSyncedMetaDataChangeEvent::GlobalSyncedMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::GlobalSyncedMetaDataChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altGlobalSyncedMetaDataChangeEvent", void (*)(const char* key, GoValue oldValue, GoValue newValue));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call GlobalSyncedMetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CGlobalSyncedMetaDataChangeEvent *>(ev);
    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();

    GoValue newValue{};
    GoValue oldValue{};
    Go::Runtime::MValueToGo(newValueMeta, &newValue);
    Go::Runtime::MValueToGo(oldValueMeta, &oldValue);

    call(key, oldValue, newValue);

    // TODO: free GoValues
}
