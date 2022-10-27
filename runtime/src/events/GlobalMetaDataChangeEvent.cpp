#include "GlobalMetaDataChangeEvent.h"
#include "GoRuntime.h"

Go::GlobalMetaDataChangeEvent::GlobalMetaDataChangeEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::GlobalMetaDataChangeEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altGlobalMetaDataChangeEvent", void (*)(const char* key, GoValue oldValue, GoValue newValue));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Could not call GlobalMetaDataChangeEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CGlobalMetaDataChangeEvent *>(ev);
    auto key = event->GetKey().c_str();
    auto newValueMeta = event->GetVal();
    auto oldValueMeta = event->GetOldVal();

    GoValue oldV{};
    GoValue newV{};
    Go::Runtime::MValueToGo(oldValueMeta, &oldV);
    Go::Runtime::MValueToGo(newValueMeta, &newV);

    call(key, oldV, newV);

#ifdef _WIN32
    delete[] newValue.array;
    delete[] oldValue.array;
#endif
}
