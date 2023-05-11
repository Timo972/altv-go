#include "ConsoleCommandEvent.h"

Go::ConsoleCommandEvent::ConsoleCommandEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::ConsoleCommandEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altConsoleCommandEvent", void (*)(const char* name, Array arr));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call ConsoleCommandEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CConsoleCommandEvent *>(ev);
    auto name = event->GetName();
    auto args = event->GetArgs();

    call(name.c_str(), Go::Runtime::CreateStringArray(args));
}
