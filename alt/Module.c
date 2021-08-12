#include "Module.h"

Module module;

capi_player_has_meta_data g_call_player_has_meta_data;
capi_player_get_meta_data g_call_player_get_meta_data;
capi_player_set_meta_data g_call_player_set_meta_data;
capi_player_delete_meta_data g_call_player_delete_meta_data;
capi_player_get_position g_call_player_get_position;
capi_player_set_position g_call_player_set_position;
capi_player_get_dimension g_call_player_get_dimension;
capi_player_set_dimension g_call_player_set_dimension;
capi_player_spawn g_call_player_spawn;
capi_player_set_model g_call_player_set_model;

int load_module(const char *path)
{
    module = LOAD_LIB(path);

    if (module == NULL)
    {
        return 0;
    }

    g_call_player_has_meta_data = GET_FUNC(module, "Player_HasMetaData", capi_player_has_meta_data);
    g_call_player_get_meta_data = GET_FUNC(module, "Player_GetMetaData", capi_player_get_meta_data);
    g_call_player_set_meta_data = GET_FUNC(module, "Player_SetMetaData", capi_player_set_meta_data);
    g_call_player_delete_meta_data = GET_FUNC(module, "Player_DeleteMetaData", capi_player_delete_meta_data);
    g_call_player_get_position = GET_FUNC(module, "Player_GetPosition", capi_player_get_position);
    g_call_player_set_position = GET_FUNC(module, "Player_SetPosition", capi_player_set_position);
    g_call_player_get_dimension = GET_FUNC(module, "Player_GetDimension", capi_player_get_dimension);
    g_call_player_set_dimension = GET_FUNC(module, "Player_SetDimension", capi_player_set_dimension);
    g_call_player_spawn = GET_FUNC(module, "Player_Spawn", capi_player_spawn);
    g_call_player_set_model = GET_FUNC(module, "Player_SetModel", capi_player_set_model);

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

int player_has_meta_data(void *base, const char *key)
{
    return g_call_player_has_meta_data(base, key);
}

MetaData player_get_meta_data(void *base, const char *key)
{
    return g_call_player_get_meta_data(base, key);
}

void player_set_meta_data(void *base, const char *key, void *val)
{
    g_call_player_set_meta_data(base, key, val);
}

void player_delete_meta_data(void *base, const char *key)
{
    g_call_player_delete_meta_data(base, key);
}

Position player_get_position(void *player)
{
    return g_call_player_get_position(player);
}

void player_set_position(void *player, float x, float y, float z)
{
    g_call_player_set_position(player, x, y, z);
}

long player_get_dimension(void *player)
{
    return g_call_player_get_dimension(player);
}

void player_set_dimension(void *player, long dimension)
{
    g_call_player_set_dimension(player, dimension);
}

void player_spawn(void *player, float x, float y, float z, unsigned long delay)
{
    g_call_player_spawn(player, x, y, z, delay);
}

void player_set_model(void *player, unsigned long model)
{
    g_call_player_set_model(player, model);
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