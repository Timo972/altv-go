#include "version/version.h"
#include "Main.h"
#include "GoRuntime.h"

EXPORT bool altMain(alt::ICore* core) {
    // Make sure that protobuf headers and lib version match
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    alt::ICore::SetInstance(core);

    auto runtime = Go::Runtime::GetInstance();

    core->RegisterScriptRuntime("go", runtime);
    core->LogInfo("Go Module Loaded");

    return true;
}

EXPORT const char* GetSDKHash() {
    return ALT_SDK_VERSION;
}
