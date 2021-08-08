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

void log_info(const char *message)
{
    capi_log_info call = GET_FUNC(module, "Core_LogInfo", capi_log_info);
    call(message);
}

const char *player_get_name(void *p)
{
    capi_player_get_name call = GET_FUNC(module, "Player_GetName", capi_player_get_name);
    return call(p);
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
