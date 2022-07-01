#pragma once

#ifdef WIN32
#include "windows.h"
#define SEPARATOR "\\"
#define LOAD_LIB(path) LoadLibrary(path)
#define GET_FUNC(module, name, type) (type) GetProcAddress(module, name);
using ModuleLibrary = HINSTANCE__;
#else
#include <dlfcn.h>
#define SEPARATOR "/"
#define LOAD_LIB(name) dlopen(name, RTLD_NOW);
#define GET_FUNC(module, name, type) (type) dlsym(module, name);
using ModuleLibrary = void;
#endif
