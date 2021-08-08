#ifndef CAPI_MODULE
#define CAPI_MODULE

#ifndef __linux__
#include <Windows.h>

#define SEPARATOR "\\"
#define LOAD_LIB(path) LoadLibrary(path)
#define GET_FUNC(module, name, type) (type) GetProcAddress(module, name);

typedef HINSTANCE Module;
#else
#include <stddef.h>
#include <dlfcn.h>

#define SEPARATOR "/"
#define LOAD_LIB(name) dlopen(name, RTLD_NOW);
#define GET_FUNC(module, name, type) (type) dlsym(module, name);

typedef void *Module;
#endif

typedef struct metaData
{
    const void *Ptr;
    unsigned int Type;
} MetaData;

typedef void (*capi_log_info)(const char *message);
typedef void (*capi_register_alt_event)(const char *resourceName, unsigned short eventType);
typedef const char *(*capi_player_get_name)(void *p);

typedef int (*capi_base_object_has_meta_data)(void *base, const char *key);
typedef MetaData (*capi_base_object_get_meta_data)(void *base, const char *key);
typedef void (*capi_base_object_set_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_base_object_delete_meta_data)(void *base, const char *key);

int load_module(const char *path);

void register_alt_event(const char *resourceName, unsigned short eventType);

void log_info(const char *message);

const char *player_get_name(void *p);

int base_object_has_meta_data(void *base, const char *key);
MetaData base_object_get_meta_data(void *base, const char *key);
void base_object_set_meta_data(void *base, const char *key, void *val);
void base_object_delete_meta_data(void *base, const char *key);

#endif