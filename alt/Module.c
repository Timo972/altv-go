#include "Module.h"

Module module;
// Player
capi_player_get_name g_call_player_get_name;
capi_player_has_meta_data g_call_player_has_meta_data;
capi_player_get_meta_data g_call_player_get_meta_data;
capi_player_set_meta_data g_call_player_set_meta_data;
capi_player_delete_meta_data g_call_player_delete_meta_data;
capi_player_has_synced_meta_data g_call_player_has_synced_meta_data;
capi_player_get_synced_meta_data g_call_player_get_synced_meta_data;
capi_player_set_synced_meta_data g_call_player_set_synced_meta_data;
capi_player_delete_synced_meta_data g_call_player_delete_synced_meta_data;
capi_player_has_stream_synced_meta_data g_call_player_has_stream_synced_meta_data;
capi_player_get_stream_synced_meta_data g_call_player_get_stream_synced_meta_data;
capi_player_set_stream_synced_meta_data g_call_player_set_stream_synced_meta_data;
capi_player_delete_stream_synced_meta_data g_call_player_delete_stream_synced_meta_data;
capi_player_get_position g_call_player_get_position;
capi_player_set_position g_call_player_set_position;
capi_player_get_rotation g_call_player_get_rotation;
capi_player_set_rotation g_call_player_set_rotation;
capi_player_get_dimension g_call_player_get_dimension;
capi_player_set_dimension g_call_player_set_dimension;
capi_player_spawn g_call_player_spawn;
capi_player_despawn g_call_player_despawn;
capi_player_set_model g_call_player_set_model;
capi_player_get_model g_call_player_get_model;
capi_player_get_health g_call_player_get_health;
capi_player_set_health g_call_player_set_health;
capi_player_has_weapon_component g_call_player_has_weapon_component;
capi_player_get_weapon_tint_index g_call_player_get_weapon_tint_index;
capi_player_get_current_weapon_tint_index g_call_player_get_current_weapon_tint_index;
capi_player_get_current_weapon g_call_player_get_current_weapon;
capi_player_is_dead g_call_player_is_dead;
capi_player_is_jumping g_call_player_is_jumping;
capi_player_is_in_ragdoll g_call_player_is_in_ragdoll;
capi_player_is_aiming g_call_player_is_aiming;
capi_player_is_shooting g_call_player_is_shooting;
capi_player_is_reloading g_call_player_is_reloading;
capi_player_get_armour g_call_player_get_armour;
capi_player_set_armour g_call_player_set_armour;
capi_player_get_move_speed g_call_player_get_move_speed;
capi_player_get_aim_pos g_call_player_get_aim_pos;
capi_player_get_head_rotation g_call_player_get_head_rotation;
capi_player_is_in_vehicle g_call_player_is_in_vehicle;
capi_player_get_vehicle g_call_player_get_vehicle;
capi_player_get_seat g_call_player_get_seat;
capi_player_get_entity_aiming_at g_call_player_get_entity_aiming_at;
capi_player_get_entity_aim_offset g_call_player_get_entity_aim_offset;
capi_player_is_flashlight_active g_call_player_is_flashlight_active;
capi_player_is_connected g_call_player_is_connected;
capi_player_get_ping g_call_player_get_ping;
capi_player_get_ip g_call_player_get_ip;
capi_player_get_social_i_d g_call_player_get_social_id;
capi_player_get_hwid_hash g_call_player_get_hwid_hash;
capi_player_get_hwid_ex_hash g_call_player_get_hwid_ex_hash;
capi_player_get_auth_token g_call_player_get_auth_token;
capi_player_set_max_armour g_call_player_set_max_armour;
capi_player_set_current_weapon g_call_player_set_current_weapon;
capi_player_set_weapon_tint_index g_call_player_set_weapon_tint_index;
capi_player_add_weapon_component g_call_player_add_weapon_component;
capi_player_remove_weapon_component g_call_player_remove_weapon_component;
capi_player_clear_blood_damage g_call_player_clear_blood_damage;
capi_player_set_max_health g_call_player_set_max_health;
capi_player_give_weapon g_call_player_give_weapon;
capi_player_remove_weapon g_call_player_remove_weapon;
capi_player_remove_all_weapons g_call_player_remove_all_weapons;
capi_player_set_date_time g_call_player_set_date_time;
capi_player_set_weather g_call_player_set_weather;
capi_player_kick g_call_player_kick;
capi_player_set_clothes g_call_player_set_clothes;
capi_player_set_dlc_clothes g_call_player_set_dlc_clothes;
capi_player_set_props g_call_player_set_props;
capi_player_set_dlc_props g_call_player_set_dlc_props;
capi_player_clear_props g_call_player_clear_props;
capi_player_is_entity_in_streaming_range g_call_player_is_entity_in_streaming_range;
capi_player_get_max_health g_call_player_get_max_health;
capi_player_get_max_armour g_call_player_get_max_armour;
capi_player_detach g_call_player_detach;
capi_player_attach_to_entity g_call_player_attach_to_entity;
capi_player_set_visible g_call_player_set_visible;
capi_player_get_visible g_call_player_get_visible;
capi_player_get_id g_call_player_get_id;
capi_player_get_network_owner g_call_player_get_network_owner;
capi_player_set_network_owner g_call_player_set_network_owner;

// Vehicle
capi_core_create_vehicle g_call_core_create_vehicle;

int load_module(const char *path)
{
    module = LOAD_LIB(path);

    if (module == NULL)
    {
        return 0;
    }

    // Player
    g_call_player_get_name = GET_FUNC(module, "Player_GetName", capi_player_get_name);
    g_call_player_has_meta_data = GET_FUNC(module, "Player_HasMetaData", capi_player_has_meta_data);
    g_call_player_get_meta_data = GET_FUNC(module, "Player_GetMetaData", capi_player_get_meta_data);
    g_call_player_set_meta_data = GET_FUNC(module, "Player_SetMetaData", capi_player_set_meta_data);
    g_call_player_delete_meta_data = GET_FUNC(module, "Player_DeleteMetaData", capi_player_delete_meta_data);
    g_call_player_has_synced_meta_data = GET_FUNC(module, "Player_HasSyncedMetaData", capi_player_has_synced_meta_data);
    g_call_player_get_synced_meta_data = GET_FUNC(module, "Player_GetSyncedMetaData", capi_player_get_synced_meta_data);
    g_call_player_set_synced_meta_data = GET_FUNC(module, "Player_SetSyncedMetaData", capi_player_set_synced_meta_data);
    g_call_player_delete_synced_meta_data = GET_FUNC(module, "Player_DeleteSyncedMetaData", capi_player_delete_synced_meta_data);
    g_call_player_has_stream_synced_meta_data = GET_FUNC(module, "Player_HasStreamSyncedMetaData", capi_player_has_stream_synced_meta_data);
    g_call_player_get_stream_synced_meta_data = GET_FUNC(module, "Player_GetStreamSyncedMetaData", capi_player_get_stream_synced_meta_data);
    g_call_player_set_stream_synced_meta_data = GET_FUNC(module, "Player_SetStreamSyncedMetaData", capi_player_set_stream_synced_meta_data);
    g_call_player_delete_stream_synced_meta_data = GET_FUNC(module, "Player_DeleteStreamSyncedMetaData", capi_player_delete_stream_synced_meta_data);
    g_call_player_get_position = GET_FUNC(module, "Player_GetPosition", capi_player_get_position);
    g_call_player_set_position = GET_FUNC(module, "Player_SetPosition", capi_player_set_position);
    g_call_player_get_rotation = GET_FUNC(module, "Player_GetRotation", capi_player_get_rotation);
    g_call_player_set_rotation = GET_FUNC(module, "Player_SetRotation", capi_player_set_rotation);
    g_call_player_get_dimension = GET_FUNC(module, "Player_GetDimension", capi_player_get_dimension);
    g_call_player_set_dimension = GET_FUNC(module, "Player_SetDimension", capi_player_set_dimension);
    g_call_player_spawn = GET_FUNC(module, "Player_Spawn", capi_player_spawn);
    g_call_player_despawn = GET_FUNC(module, "Player_Despawn", capi_player_despawn);
    g_call_player_set_model = GET_FUNC(module, "Player_SetModel", capi_player_set_model);
    g_call_player_get_model = GET_FUNC(module, "Player_GetModel", capi_player_get_model);
    g_call_player_get_health = GET_FUNC(module, "Player_GetHealth", capi_player_get_health);
    g_call_player_set_health = GET_FUNC(module, "Player_SetHealth", capi_player_set_health);
    g_call_player_has_weapon_component = GET_FUNC(module, "Player_HasWeaponComponent", capi_player_has_weapon_component);
    g_call_player_get_weapon_tint_index = GET_FUNC(module, "Player_GetWeaponTintIndex", capi_player_get_weapon_tint_index);
    g_call_player_get_current_weapon_tint_index = GET_FUNC(module, "Player_GetCurrentWeaponTintIndex", capi_player_get_current_weapon_tint_index);
    g_call_player_get_current_weapon = GET_FUNC(module, "Player_GetCurrentWeapon", capi_player_get_current_weapon);
    g_call_player_is_dead = GET_FUNC(module, "Player_IsDead", capi_player_is_dead);
    g_call_player_is_jumping = GET_FUNC(module, "Player_IsJumping", capi_player_is_jumping);
    g_call_player_is_in_ragdoll = GET_FUNC(module, "Player_IsInRagdoll", capi_player_is_in_ragdoll);
    g_call_player_is_aiming = GET_FUNC(module, "Player_IsAiming", capi_player_is_aiming);
    g_call_player_is_shooting = GET_FUNC(module, "Player_IsShooting", capi_player_is_shooting);
    g_call_player_is_reloading = GET_FUNC(module, "Player_IsReloading", capi_player_is_reloading);
    g_call_player_get_armour = GET_FUNC(module, "Player_GetArmour", capi_player_get_armour);
    g_call_player_set_armour = GET_FUNC(module, "Player_SetArmour", capi_player_set_armour);
    g_call_player_get_move_speed = GET_FUNC(module, "Player_GetMoveSpeed", capi_player_get_move_speed);
    g_call_player_get_aim_pos = GET_FUNC(module, "Player_GetAimPos", capi_player_get_aim_pos);
    g_call_player_get_head_rotation = GET_FUNC(module, "Player_GetHeadRotation", capi_player_get_head_rotation);
    g_call_player_is_in_vehicle = GET_FUNC(module, "Player_IsInVehicle", capi_player_is_in_vehicle);
    g_call_player_get_vehicle = GET_FUNC(module, "Player_GetVehicle", capi_player_get_vehicle);
    g_call_player_get_seat = GET_FUNC(module, "Player_GetSeat", capi_player_get_seat);
    g_call_player_get_entity_aiming_at = GET_FUNC(module, "Player_GetEntityAimingAt", capi_player_get_entity_aiming_at);
    g_call_player_get_entity_aim_offset = GET_FUNC(module, "Player_GetEntityAimOffset", capi_player_get_entity_aim_offset);
    g_call_player_is_flashlight_active = GET_FUNC(module, "Player_IsFlashlightActive", capi_player_is_flashlight_active);
    g_call_player_is_connected = GET_FUNC(module, "Player_IsConnected", capi_player_is_connected);
    g_call_player_get_ping = GET_FUNC(module, "Player_GetPing", capi_player_get_ping);
    g_call_player_get_ip = GET_FUNC(module, "Player_GetIP", capi_player_get_ip);
    g_call_player_get_social_id = GET_FUNC(module, "Player_GetSocialID", capi_player_get_social_id);
    g_call_player_get_hwid_hash = GET_FUNC(module, "Player_GetHwidHash", capi_player_get_hwid_hash);
    g_call_player_get_hwid_ex_hash = GET_FUNC(module, "Player_GetHwidExHash", capi_player_get_hwid_ex_hash);
    g_call_player_get_auth_token = GET_FUNC(module, "Player_GetAuthToken", capi_player_get_auth_token);
    g_call_player_set_max_armour = GET_FUNC(module, "Player_SetMaxArmour", capi_player_set_max_armour);
    g_call_player_set_current_weapon = GET_FUNC(module, "Player_SetCurrentWeapon", capi_player_set_current_weapon);
    g_call_player_set_weapon_tint_index = GET_FUNC(module, "Player_SetWeaponTintIndex", capi_player_set_weapon_tint_index);
    g_call_player_add_weapon_component = GET_FUNC(module, "Player_AddWeaponComponent", capi_player_add_weapon_component);
    g_call_player_remove_weapon_component = GET_FUNC(module, "Player_RemoveWeaponComponent", capi_player_remove_weapon_component);
    g_call_player_clear_blood_damage = GET_FUNC(module, "Player_ClearBloodDamage", capi_player_clear_blood_damage);
    g_call_player_set_max_health = GET_FUNC(module, "Player_SetMaxHealth", capi_player_set_max_health);
    g_call_player_give_weapon = GET_FUNC(module, "Player_GiveWeapon", capi_player_give_weapon);
    g_call_player_remove_weapon = GET_FUNC(module, "Player_RemoveWeapon", capi_player_remove_weapon);
    g_call_player_remove_all_weapons = GET_FUNC(module, "Player_RemoveAllWeapons", capi_player_remove_all_weapons);
    g_call_player_set_date_time = GET_FUNC(module, "Player_SetDateTime", capi_player_set_date_time);
    g_call_player_set_weather = GET_FUNC(module, "Player_SetWeather", capi_player_set_weather);
    g_call_player_kick = GET_FUNC(module, "Player_Kick", capi_player_kick);
    g_call_player_set_clothes = GET_FUNC(module, "Player_SetClothes", capi_player_set_clothes);
    g_call_player_set_dlc_clothes = GET_FUNC(module, "Player_SetDlcClothes", capi_player_set_dlc_clothes);
    g_call_player_set_props = GET_FUNC(module, "Player_SetProps", capi_player_set_props);
    g_call_player_set_dlc_props = GET_FUNC(module, "Player_SetDlcProps", capi_player_set_dlc_props);
    g_call_player_clear_props = GET_FUNC(module, "Player_ClearProps", capi_player_clear_props);
    g_call_player_is_entity_in_streaming_range = GET_FUNC(module, "Player_IsEntityInStreamingRange", capi_player_is_entity_in_streaming_range);
    g_call_player_get_max_health = GET_FUNC(module, "Player_GetMaxHealth", capi_player_get_max_health);
    g_call_player_get_max_armour = GET_FUNC(module, "Player_GetMaxArmour", capi_player_get_max_armour);
    g_call_player_detach = GET_FUNC(module, "Player_Detach", capi_player_detach);
    g_call_player_attach_to_entity = GET_FUNC(module, "Player_AttachToEntity", capi_player_attach_to_entity);
    g_call_player_set_visible = GET_FUNC(module, "Player_SetVisible", capi_player_set_visible);
    g_call_player_get_visible = GET_FUNC(module, "Player_GetVisible", capi_player_get_visible);
    g_call_player_get_id = GET_FUNC(module, "Player_GetID", capi_player_get_id);
    g_call_player_get_network_owner = GET_FUNC(module, "Player_GetNetworkOwner", capi_player_get_network_owner);
    g_call_player_set_network_owner = GET_FUNC(module, "Player_SetNetworkOwner", capi_player_set_network_owner);

    return 1;
}
// Core
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

// Player
const char * player_get_name(void *p)
{
    return g_call_player_get_name(p);
}

int player_has_meta_data(void* base, const char *key)
{
    return g_call_player_has_meta_data(base, key);
}

MetaData player_get_meta_data(void* base, const char *key)
{
    return g_call_player_get_meta_data(base, key);
}

void player_set_meta_data(void *base, const char *key, void *val)
{
    return g_call_player_set_meta_data(base, key, val);
}

void player_delete_meta_data(void *base, const char *key)
{
    return g_call_player_delete_meta_data(base, key);
}

int player_has_synced_meta_data(void* base, const char *key)
{
    return g_call_player_has_synced_meta_data(base, key);
}

MetaData player_get_synced_meta_data(void* base, const char *key)
{
    return g_call_player_get_synced_meta_data(base, key);
}

void player_set_synced_meta_data(void *base, const char *key, void *val)
{
    return g_call_player_set_synced_meta_data(base, key, val);
}

void player_delete_synced_meta_data(void *base, const char *key)
{
    return g_call_player_delete_synced_meta_data(base, key);
}

int player_has_stream_synced_meta_data(void* base, const char *key)
{
    return g_call_player_has_stream_synced_meta_data(base, key);
}

MetaData player_get_stream_synced_meta_data(void* base, const char *key)
{
    return g_call_player_get_stream_synced_meta_data(base, key);
}

void player_set_stream_synced_meta_data(void *base, const char *key, void *val)
{
    return g_call_player_set_stream_synced_meta_data(base, key, val);
}

void player_delete_stream_synced_meta_data(void *base, const char *key)
{
    return g_call_player_delete_stream_synced_meta_data(base, key);
}

Position player_get_position(void *p)
{
    return g_call_player_get_position(p);
}

void player_set_position(void* p, float x, float y, float z)
{
    return g_call_player_set_position(p, x, y, z);
}

Rotation player_get_rotation(void *p)
{
    return g_call_player_get_rotation(p);
}

void player_set_rotation(void *p, float roll, float pitch, float yaw)
{
    return g_call_player_set_rotation(p, roll, pitch, yaw);
}

long player_get_dimension(void* p)
{
    return g_call_player_get_dimension(p);
}

void player_set_dimension(void* p, long dimension)
{
    return g_call_player_set_dimension(p, dimension);
}

void player_spawn(void *p, float x, float y, float z, unsigned long delay)
{
    return g_call_player_spawn(p, x, y, z, delay);
}

void player_despawn(void *p)
{
    return g_call_player_despawn(p);
}

void player_set_model(void *p, unsigned long model)
{
    return g_call_player_set_model(p, model);
}

unsigned long player_get_model(void *p)
{
    return g_call_player_get_model(p);
}

unsigned int player_get_health(void *p)
{
    return g_call_player_get_health(p);
}

void player_set_health(void *p, unsigned int health)
{
    return g_call_player_set_health(p, health);
}

bool player_has_weapon_component(void *p, unsigned long weapon, unsigned long component)
{
    return g_call_player_has_weapon_component(p, weapon, component);
}

unsigned int player_get_weapon_tint_index(void *p, unsigned long weapon)
{
    return g_call_player_get_weapon_tint_index(p, weapon);
}

unsigned int player_get_current_weapon_tint_index(void *p)
{
    return g_call_player_get_current_weapon_tint_index(p);
}

unsigned long player_get_current_weapon(void *p)
{
    return g_call_player_get_current_weapon(p);
}

bool player_is_dead(void *p)
{
    return g_call_player_is_dead(p);
}

bool player_is_jumping(void *p)
{
    return g_call_player_is_jumping(p);
}

bool player_is_in_ragdoll(void *p)
{
    return g_call_player_is_in_ragdoll(p);
}

bool player_is_aiming(void *p)
{
    return g_call_player_is_aiming(p);
}

bool player_is_shooting(void *p)
{
    return g_call_player_is_shooting(p);
}

bool player_is_reloading(void *p)
{
    return g_call_player_is_reloading(p);
}

unsigned int player_get_armour(void *p)
{
    return g_call_player_get_armour(p);
}

void player_set_armour(void *p, unsigned int armour)
{
    return g_call_player_set_armour(p, armour);
}

float player_get_move_speed(void *p)
{
    return g_call_player_get_move_speed(p);
}

Position player_get_aim_pos(void *p)
{
    return g_call_player_get_aim_pos(p);
}

Rotation player_get_head_rotation(void *p)
{
    return g_call_player_get_head_rotation(p);
}

bool player_is_in_vehicle(void *p)
{
    return g_call_player_is_in_vehicle(p);
}

void * player_get_vehicle(void *p)
{
    return g_call_player_get_vehicle(p);
}

unsigned int player_get_seat(void *p)
{
    return g_call_player_get_seat(p);
}

void * player_get_entity_aiming_at(void *p)
{
    return g_call_player_get_entity_aiming_at(p);
}

Position player_get_entity_aim_offset(void *p)
{
    return g_call_player_get_entity_aim_offset(p);
}

bool player_is_flashlight_active(void *p)
{
    return g_call_player_is_flashlight_active(p);
}

bool player_is_connected(void *p)
{
    return g_call_player_is_connected(p);
}

unsigned long player_get_ping(void *p)
{
    return g_call_player_get_ping(p);
}

const char* player_get_ip(void *p)
{
    return g_call_player_get_ip(p);
}

unsigned long long player_get_social_id(void *p)
{
    return g_call_player_get_social_id(p);
}

unsigned long long player_get_hwid_hash(void *p)
{
    return g_call_player_get_hwid_hash(p);
}

unsigned long long player_get_hwid_ex_hash(void *p)
{
    return g_call_player_get_hwid_ex_hash(p);
}

const char* player_get_auth_token(void *p)
{
    return g_call_player_get_auth_token(p);
}

void player_set_max_armour(void *p, unsigned int armour)
{
    return g_call_player_set_max_armour(p, armour);
}

void player_set_current_weapon(void *p, unsigned long weapon)
{
    return g_call_player_set_current_weapon(p, weapon);
}

void player_set_weapon_tint_index(void *p, unsigned long weapon, unsigned int tintIndex)
{
    return g_call_player_set_weapon_tint_index(p, weapon, tintIndex);
}

void player_add_weapon_component(void *p, unsigned long weapon, unsigned long component)
{
    return g_call_player_add_weapon_component(p, weapon, component);
}

void player_remove_weapon_component(void *p, unsigned long weapon, unsigned long component)
{
    return g_call_player_remove_weapon_component(p, weapon, component);
}

void player_clear_blood_damage(void *p)
{
    return g_call_player_clear_blood_damage(p);
}

void player_set_max_health(void *p, unsigned int health)
{
    return g_call_player_set_max_health(p, health);
}

void player_give_weapon(void *p, unsigned long weapon, long ammo, bool selectWeapon)
{
    return g_call_player_give_weapon(p, weapon, ammo, selectWeapon);
}

void player_remove_weapon(void *p, unsigned long weapon)
{
    return g_call_player_remove_weapon(p, weapon);
}

void player_remove_all_weapons(void *p)
{
    return g_call_player_remove_all_weapons(p);
}

void player_set_date_time(void *p, int day, int month, int year, int hour, int minute, int second)
{
    return g_call_player_set_date_time(p, day, month, year, hour, minute, second);
}

void player_set_weather(void *p, unsigned long weather)
{
    return g_call_player_set_weather(p, weather);
}

void player_kick(void *p, const char* reason)
{
    return g_call_player_kick(p, reason);
}

void player_set_clothes(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette)
{
    return g_call_player_set_clothes(p, component, drawable, texture, palette);
}

void player_set_dlc_clothes(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette, unsigned long dlc)
{
    return g_call_player_set_dlc_clothes(p, component, drawable, texture, palette, dlc);
}

void player_set_props(void *p, unsigned int component, unsigned int drawable, unsigned int texture)
{
    return g_call_player_set_props(p, component, drawable, texture);
}

void player_set_dlc_props(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned long dlc)
{
    return g_call_player_set_dlc_props(p, component, drawable, texture, dlc);
}

void player_clear_props(void *p, unsigned int component)
{
    return g_call_player_clear_props(p, component);
}

bool player_is_entity_in_streaming_range(void *p, void *entity)
{
    return g_call_player_is_entity_in_streaming_range(p, entity);
}

unsigned int player_get_max_health(void *p)
{
    return g_call_player_get_max_health(p);
}

unsigned int player_get_max_armour(void *p)
{
    return g_call_player_get_max_armour(p);
}

void player_detach(void *p)
{
    return g_call_player_detach(p);
}

void player_attach_to_entity(void *p, void *e, int otherBoneIndex, int myBoneIndex, Position position, Rotation rotation, bool collision, bool noFixedRotation)
{
    return g_call_player_attach_to_entity(p, e, otherBoneIndex, myBoneIndex, position, rotation, collision, noFixedRotation);
}

void player_set_visible(void *p, bool toggle)
{
    return g_call_player_set_visible(p, toggle);
}

bool player_get_visible(void *p)
{
    return g_call_player_get_visible(p);
}

unsigned long player_get_id(void *p)
{
    return g_call_player_get_id(p);
}

void * player_get_network_owner(void *p)
{
    return g_call_player_get_network_owner(p);
}

void player_set_network_owner(void *p, void *owner, bool disableMigration)
{
    return g_call_player_set_network_owner(p, owner, disableMigration);
}

// Core
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

void *core_create_vehicle(unsigned long model, float posX, float posY, float posZ,
                          float rotX, float rotY, float rotZ)
{
    g_call_core_create_vehicle(model, posX, posY, posZ, rotX, rotY, rotZ);
}