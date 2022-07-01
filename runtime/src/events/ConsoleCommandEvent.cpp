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

    auto size = args.size();

#ifdef _WIN32
    auto constArgs = new const char* [size];
#else
    const char* constArgs[size];
#endif

    for (uint64_t i = 0; i < size; i++) {
        constArgs[i] = args[i].c_str();
    }

    Array arr;
    arr.size = size;
    arr.array = constArgs;

    call(name.c_str(), arr);

// freeing is done in altv-go-pkg (convertArray)
// #ifdef _WIN32
//     delete[] constArgs;
// #endif
}
