// copy this into Module.c
capi_core_log_info g_call_core_log_info;
capi_core_log_debug g_call_core_log_debug;
capi_core_log_warning g_call_core_log_warning;
capi_core_log_error g_call_core_log_error;
capi_core_log_colored g_call_core_log_colored;
capi_core_create_m_value_bool g_call_core_create_m_value_bool;
capi_core_create_m_value_int g_call_core_create_m_value_int;
capi_core_create_m_value_u_int g_call_core_create_m_value_u_int;
capi_core_create_m_value_double g_call_core_create_m_value_double;
capi_core_create_m_value_string g_call_core_create_m_value_string;
capi_core_get_m_value_bool g_call_core_get_m_value_bool;
capi_core_get_m_value_int g_call_core_get_m_value_int;
capi_core_get_m_value_u_int g_call_core_get_m_value_u_int;
capi_core_get_m_value_double g_call_core_get_m_value_double;
capi_core_get_m_value_string g_call_core_get_m_value_string;
capi_core_create_vehicle g_call_core_create_vehicle;



// copy this into int load_module(const char *path);
g_call_core_log_info = GET_FUNC(module, "Core_LogInfo", capi_core_log_info);
g_call_core_log_debug = GET_FUNC(module, "Core_LogDebug", capi_core_log_debug);
g_call_core_log_warning = GET_FUNC(module, "Core_LogWarning", capi_core_log_warning);
g_call_core_log_error = GET_FUNC(module, "Core_LogError", capi_core_log_error);
g_call_core_log_colored = GET_FUNC(module, "Core_LogColored", capi_core_log_colored);
g_call_core_create_m_value_bool = GET_FUNC(module, "Core_CreateMValueBool", capi_core_create_m_value_bool);
g_call_core_create_m_value_int = GET_FUNC(module, "Core_CreateMValueInt", capi_core_create_m_value_int);
g_call_core_create_m_value_u_int = GET_FUNC(module, "Core_CreateMValueUInt", capi_core_create_m_value_u_int);
g_call_core_create_m_value_double = GET_FUNC(module, "Core_CreateMValueDouble", capi_core_create_m_value_double);
g_call_core_create_m_value_string = GET_FUNC(module, "Core_CreateMValueString", capi_core_create_m_value_string);
g_call_core_get_m_value_bool = GET_FUNC(module, "Core_GetMValueBool", capi_core_get_m_value_bool);
g_call_core_get_m_value_int = GET_FUNC(module, "Core_GetMValueInt", capi_core_get_m_value_int);
g_call_core_get_m_value_u_int = GET_FUNC(module, "Core_GetMValueUInt", capi_core_get_m_value_u_int);
g_call_core_get_m_value_double = GET_FUNC(module, "Core_GetMValueDouble", capi_core_get_m_value_double);
g_call_core_get_m_value_string = GET_FUNC(module, "Core_GetMValueString", capi_core_get_m_value_string);
g_call_core_create_vehicle = GET_FUNC(module, "Core_CreateVehicle", capi_core_create_vehicle);
g_call_core_hash = GET_FUNC(module, "Core_Hash", capi_core_hash);
g_call_core_file_exists = GET_FUNC(module, "Core_FileExists", capi_core_file_exists);
g_call_core_read_file = GET_FUNC(module, "Core_ReadFile", capi_core_read_file);
g_call_core_get_entity_by_i_d = GET_FUNC(module, "Core_GetEntityByID", capi_core_get_entity_by_i_d);
g_call_core_has_meta_data = GET_FUNC(module, "Core_HasMetaData", capi_core_has_meta_data);
g_call_core_get_meta_data = GET_FUNC(module, "Core_GetMetaData", capi_core_get_meta_data);
g_call_core_set_meta_data = GET_FUNC(module, "Core_SetMetaData", capi_core_set_meta_data);
g_call_core_delete_meta_data = GET_FUNC(module, "Core_DeleteMetaData", capi_core_delete_meta_data);
g_call_core_has_synced_meta = GET_FUNC(module, "Core_HasSyncedMeta", capi_core_has_synced_meta);
g_call_core_get_synced_meta = GET_FUNC(module, "Core_GetSyncedMeta", capi_core_get_synced_meta);
g_call_core_destroy_base_object = GET_FUNC(module, "Core_DestroyBaseObject", capi_core_destroy_base_object);
g_call_core_start_resource = GET_FUNC(module, "Core_StartResource", capi_core_start_resource);
g_call_core_stop_resource = GET_FUNC(module, "Core_StopResource", capi_core_stop_resource);
g_call_core_restart_resource = GET_FUNC(module, "Core_RestartResource", capi_core_restart_resource);
g_call_core_set_synced_meta_data = GET_FUNC(module, "Core_SetSyncedMetaData", capi_core_set_synced_meta_data);
g_call_core_delete_synced_meta_data = GET_FUNC(module, "Core_DeleteSyncedMetaData", capi_core_delete_synced_meta_data);
g_call_core_get_players_by_name = GET_FUNC(module, "Core_GetPlayersByName", capi_core_get_players_by_name);
g_call_core_set_password = GET_FUNC(module, "Core_SetPassword", capi_core_set_password);


// copy into Module.c

void core_log_info(const char *message)
{
    return g_call_core_log_info(message);
}

void core_log_debug(const char *message)
{
    return g_call_core_log_debug(message);
}

void core_log_warning(const char *message)
{
    return g_call_core_log_warning(message);
}

void core_log_error(const char *message)
{
    return g_call_core_log_error(message);
}

void core_log_colored(const char *message)
{
    return g_call_core_log_colored(message);
}

void * core_create_m_value_bool(int value)
{
    return g_call_core_create_m_value_bool(value);
}

void * core_create_m_value_int(long long val)
{
    return g_call_core_create_m_value_int(val);
}

void * core_create_m_value_u_int(unsigned long long val)
{
    return g_call_core_create_m_value_u_int(val);
}

void * core_create_m_value_double(double val)
{
    return g_call_core_create_m_value_double(val);
}

void * core_create_m_value_string(const char *val)
{
    return g_call_core_create_m_value_string(val);
}

bool core_get_m_value_bool(void *val)
{
    return g_call_core_get_m_value_bool(val);
}

long long core_get_m_value_int(void *val)
{
    return g_call_core_get_m_value_int(val);
}

unsigned long long core_get_m_value_u_int(void *val)
{
    return g_call_core_get_m_value_u_int(val);
}

double core_get_m_value_double(void *val)
{
    return g_call_core_get_m_value_double(val);
}

const char * core_get_m_value_string(void *val)
{
    return g_call_core_get_m_value_string(val);
}

void * core_create_vehicle(unsigned long model, float posX, float posY, float posZ,
                               float rotX, float rotY, float rotZ)
{
    return g_call_core_create_vehicle(model, posX, posY, posZ, rotX, rotY, rotZ);
}

unsigned long core_hash(const char *str)
{
    return g_call_core_hash(str);
}

int core_file_exists(const char *path)
{
    return g_call_core_file_exists(path);
}

const char * core_read_file(const char *path)
{
    return g_call_core_read_file(path);
}

void * core_get_entity_by_i_d(unsigned short id)
{
    return g_call_core_get_entity_by_i_d(id);
}

int core_has_meta_data(const char *key)
{
    return g_call_core_has_meta_data(key);
}

MetaData core_get_meta_data(const char *key)
{
    return g_call_core_get_meta_data(key);
}

void core_set_meta_data(const char *key, void *val)
{
    return g_call_core_set_meta_data(key, val);
}

void core_delete_meta_data(const char *key)
{
    return g_call_core_delete_meta_data(key);
}

int core_has_synced_meta(const char *key)
{
    return g_call_core_has_synced_meta(key);
}

MetaData core_get_synced_meta(const char *key)
{
    return g_call_core_get_synced_meta(key);
}

void core_destroy_base_object(void *h)
{
    return g_call_core_destroy_base_object(h);
}

void * core_start_resource(const char *name)
{
    return g_call_core_start_resource(name);
}

void core_stop_resource(const char *name)
{
    return g_call_core_stop_resource(name);
}

void * core_restart_resource(const char *name)
{
    return g_call_core_restart_resource(name);
}

void core_set_synced_meta_data(const char *key, void *val)
{
    return g_call_core_set_synced_meta_data(key, val);
}

void core_delete_synced_meta_data(const char *key)
{
    return g_call_core_delete_synced_meta_data(key);
}

Array core_get_players_by_name(const char *name)
{
    return g_call_core_get_players_by_name(name);
}

void core_set_password(const char *password)
{
    return g_call_core_set_password(password);
}
