#include "Module.h"

Module module;

int load_module(const char *path)
{
    module = LOAD_LIB(path);

    if (module == NULL)
    {
        return 0;
    }

    return 1;
}

void register_alt_event(const char *resourceName, unsigned short eventType)
{
    capi_register_alt_event call = GET_FUNC(module, "RegisterAltEvent", capi_register_alt_event);
    call(resourceName, eventType);
}

void core_log_info(const char *message)
{
    capi_log call = GET_FUNC(module, "Core_LogInfo", capi_log);
    call(message);
}

void core_log_debug(const char *message)
{
    capi_log call = GET_FUNC(module, "Core_LogDebug", capi_log);
    call(message);
}

void core_log_warning(const char *message)
{
    capi_log call = GET_FUNC(module, "Core_LogWarning", capi_log);
    call(message);
}

void core_log_error(const char *message)
{
    capi_log call = GET_FUNC(module, "Core_LogError", capi_log);
    call(message);
}

void core_log_colored(const char *message)
{
    capi_log call = GET_FUNC(module, "Core_LogColored", capi_log);
    call(message);
}

const char *player_get_name(void *p)
{
    capi_player_get_name call = GET_FUNC(module, "Player_GetName", capi_player_get_name);
    return call(p);
}

unsigned char base_object_get_type(void *base)
{
    capi_base_object_get_type call = GET_FUNC(module, "BaseObject_GetType", capi_base_object_get_type);
    return call(base);
}

int base_object_has_meta_data(void *base, const char *key)
{
    capi_base_object_has_meta_data call = GET_FUNC(module, "BaseObject_HasMetaData", capi_base_object_has_meta_data);
    return call(base, key);
}

MetaData base_object_get_meta_data(void *base, const char *key)
{
    capi_base_object_get_meta_data call = GET_FUNC(module, "BaseObject_GetMetaData", capi_base_object_get_meta_data);
    return call(base, key);
}

void base_object_set_meta_data(void *base, const char *key, void *val)
{
    capi_base_object_set_meta_data call = GET_FUNC(module, "BaseObject_SetMetaData", capi_base_object_set_meta_data);
    return call(base, key, val);
}

void base_object_delete_meta_data(void *base, const char *key)
{
    capi_base_object_delete_meta_data call = GET_FUNC(module, "BaseObject_DeleteMetaData", capi_base_object_delete_meta_data);
    call(base, key);
}

void *core_create_mvalue_bool(int val)
{
    capi_core_create_mvalue_bool call = GET_FUNC(module, "Core_CreateMValueBool", capi_core_create_mvalue_bool);
    return call(val);
}

void *core_create_mvalue_int(long long val)
{
    capi_core_create_mvalue_int call = GET_FUNC(module, "Core_CreateMValueInt", capi_core_create_mvalue_int);
    return call(val);
}

void *core_create_mvalue_uint(unsigned long long val)
{
    capi_core_create_mvalue_uint call = GET_FUNC(module, "Core_CreateMValueUInt", capi_core_create_mvalue_uint);
    return call(val);
}

void *core_create_mvalue_double(double val)
{
    capi_core_create_mvalue_double call = GET_FUNC(module, "Core_CreateMValueDouble", capi_core_create_mvalue_double);
    return call(val);
}

void *core_create_mvalue_string(const char *val)
{
    capi_core_create_mvalue_string call = GET_FUNC(module, "Core_CreateMValueString", capi_core_create_mvalue_string);
    return call(val);
}

int core_get_mvalue_bool(void *val)
{
    capi_core_get_mvalue_bool call = GET_FUNC(module, "Core_GetMValueBool", capi_core_get_mvalue_bool);
    return call(val);
}

long long core_get_mvalue_int(void *val)
{
    capi_core_get_mvalue_int call = GET_FUNC(module, "Core_GetMValueInt", capi_core_get_mvalue_int);
    return call(val);
}

unsigned long long core_get_mvalue_uint(void *val)
{
    capi_core_get_mvalue_uint call = GET_FUNC(module, "Core_GetMValueUInt", capi_core_get_mvalue_uint);
    return call(val);
}

double core_get_mvalue_double(void *val)
{
    capi_core_get_mvalue_double call = GET_FUNC(module, "Core_GetMValueDouble", capi_core_get_mvalue_double);
    return call(val);
}

const char *core_get_mvalue_string(void *val)
{
    capi_core_get_mvalue_string call = GET_FUNC(module, "Core_GetMValueString", capi_core_get_mvalue_string);
    return call(val);
}