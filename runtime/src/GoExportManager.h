#pragma once

//#include <iostream>
//#include <algorithm>
//#include <set>

#include "Main.h"
#include "Library.h"

namespace Go
{
    class Function : public alt::IMValueFunction::Impl
            {
            public:
                Function(ModuleLibrary *module, unsigned long long id): Library(module), id(id) {}
                alt::MValue Call(alt::MValueArgs args) const override;
            protected:
                ModuleLibrary *Library;
                unsigned long long id;
            };
    class ExportsManager
            {
            public:
                ExportsManager() = default;
                void AddExport(const char *exportName, alt::MValue data);
                bool IsExportSet(const char *exportName);
            protected:
                alt::MValueDict _registeredExports = alt::ICore::Instance().CreateMValueDict();
            };
}