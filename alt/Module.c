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
