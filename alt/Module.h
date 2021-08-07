#ifndef CAPI_MODULE
#define CAPI_MODULE

#ifndef __linux__
#include <Windows.h>

#define SEPARATOR "\\"
#define LOAD_LIB(path) LoadLibrary(path)
#define GET_FUNC(module, name, type) (type) GetProcAddress(module, name);

typedef HINSTANCE Module;
#else
#include <dlfcn.h>

#define SEPARATOR "/"
#define LOAD_LIB(name) dlopen(name, RTLD_NOW);
#define GET_FUNC(module, name, type) (type) dlsym(module, name);

typdef void Module;
#endif

typedef void (*capi_log_info)(const char *message);
typedef void (*capi_register_alt_event)(const char *resourceName, unsigned short eventType);
typedef const char *(*capi_player_get_name)(void *p);

int load_module(const char *path);

void register_alt_event(const char *resourceName, unsigned short eventType);
void log_info(const char *message);
const char *player_get_name(void *p);

#endif