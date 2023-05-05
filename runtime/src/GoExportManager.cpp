#include "GoExportManager.h"
#include "GoRuntime.h"

alt::MValue Go::Function::Call(alt::MValueArgs args) const {
    static auto call = GET_FUNC(Library, "altCallFunction", Array (*)(unsigned long long id, Array args));

    if (call == nullptr) {
        alt::ICore::Instance().LogError("Couldn't not call altCallFunction.");
        return alt::ICore::Instance().CreateMValueNone();
    }

    // auto data = Go::Runtime::EncodeMValueArgs(args);

    // Array res = call(id, data);

    // TODO: free Array

    // return Go::Runtime::DecodeMValue(res);
    return alt::ICore::Instance().CreateMValueNone();
}

void Go::ExportsManager::AddExport(const char *exportName, alt::MValue data) {
    if (IsExportSet(exportName))
        return;
    _registeredExports->Set(exportName, data);
}

bool Go::ExportsManager::IsExportSet(const char *exportName) {
    return _registeredExports->Get(exportName)->GetType() != alt::IMValue::Type::NONE;
}