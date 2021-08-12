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

typedef struct pos
{
    float x;
    float y;
    float z;
} Position;

typedef void (*capi_log)(const char *message);

typedef void (*capi_register_alt_event)(const char *resourceName, unsigned short eventType);

typedef const char *(*capi_player_get_name)(void *p);
typedef int (*capi_player_has_meta_data)(void *base, const char *key);
typedef MetaData (*capi_player_get_meta_data)(void *base, const char *key);
typedef void (*capi_player_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_player_delete_meta_data)(void *base, const char *key);
typedef void (*capi_player_set_meta_data)(void *base, const char *key, void *val);
typedef Position (*capi_player_get_position)(void *player);
typedef void (*capi_player_set_position)(void *player, float x, float y, float z);
typedef long (*capi_player_get_dimension)(void *player);
typedef void (*capi_player_set_dimension)(void *player, long dimension);
typedef void (*capi_player_spawn)(void *player, float x, float y, float z, unsigned long delay);
typedef void (*capi_player_set_model)(void *player, unsigned long model);

typedef unsigned char (*capi_base_object_get_type)(void *base);

typedef void *(*capi_core_create_mvalue_bool)(int val);
typedef void *(*capi_core_create_mvalue_int)(long long val);
typedef void *(*capi_core_create_mvalue_uint)(unsigned long long val);
typedef void *(*capi_core_create_mvalue_double)(double val);
typedef void *(*capi_core_create_mvalue_string)(const char *val);

typedef int (*capi_core_get_mvalue_bool)(void *val);
typedef long long (*capi_core_get_mvalue_int)(void *val);
typedef unsigned long long (*capi_core_get_mvalue_uint)(void *val);
typedef double (*capi_core_get_mvalue_double)(void *val);
typedef const char *(*capi_core_get_mvalue_string)(void *val);

int load_module(const char *path);

// Core
void register_alt_event(const char *resourceName, unsigned short eventType);

void core_log_info(const char *message);
void core_log_debug(const char *message);
void core_log_warning(const char *message);
void core_log_error(const char *message);
void core_log_colored(const char *message);

// Player
const char *player_get_name(void *p);
int player_has_meta_data(void *base, const char *key);
MetaData player_get_meta_data(void *base, const char *key);
void player_set_meta_data(void *base, const char *key, void *val);
void player_delete_meta_data(void *base, const char *key);
Position player_get_position(void *player);
void player_set_position(void *player, float x, float y, float z);
long player_get_dimension(void *player);
void player_set_dimension(void *player, long);
void player_spawn(void *player, float x, float y, float z, unsigned long delay);
void player_set_model(void *player, unsigned long model);

// MValue
void *core_create_mvalue_bool(int value);
void *core_create_mvalue_int(long long val);
void *core_create_mvalue_uint(unsigned long long val);
void *core_create_mvalue_double(double val);
void *core_create_mvalue_string(const char *val);

int core_get_mvalue_bool(void *val);
long long core_get_mvalue_int(void *val);
unsigned long long core_get_mvalue_uint(void *val);
double core_get_mvalue_double(void *val);
const char *core_get_mvalue_string(void *val);

#endif