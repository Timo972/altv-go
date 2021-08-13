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

typedef const char * (*capi_player_get_name)(void *p);
typedef int (*capi_player_has_meta_data)(void* base, const char *key);
typedef MetaData (*capi_player_get_meta_data)(void* base, const char *key);
typedef void (*capi_player_set_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_player_delete_meta_data)(void *base, const char *key);
typedef int (*capi_player_has_synced_meta_data)(void* base, const char *key);
typedef MetaData (*capi_player_get_synced_meta_data)(void* base, const char *key);
typedef void (*capi_player_set_synced_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_player_delete_synced_meta_data)(void *base, const char *key);
typedef int (*capi_player_has_stream_synced_meta_data)(void* base, const char *key);
typedef MetaData (*capi_player_get_stream_synced_meta_data)(void* base, const char *key);
typedef void (*capi_player_set_stream_synced_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_player_delete_stream_synced_meta_data)(void *base, const char *key);
typedef Position (*capi_player_get_position)(void *p);
typedef void (*capi_player_set_position)(void* p, float x, float y, float z);
typedef Rotation (*capi_player_get_rotation)(void *p);
typedef void (*capi_player_set_rotation)(void *p, float roll, float pitch, float yaw);
typedef long (*capi_player_get_dimension)(void* p);
typedef void (*capi_player_set_dimension)(void* p, long dimension);
typedef void (*capi_player_spawn)(void *p, float x, float y, float z, unsigned long delay);
typedef void (*capi_player_despawn)(void *p);
typedef void (*capi_player_set_model)(void *p, unsigned long model);
typedef unsigned long (*capi_player_get_model)(void *p);
typedef unsigned int (*capi_player_get_health)(void *p);
typedef void (*capi_player_set_health)(void *p, unsigned int health);
typedef bool (*capi_player_has_weapon_component)(void *p, unsigned long weapon, unsigned long component);
typedef unsigned int (*capi_player_get_weapon_tint_index)(void *p, unsigned long weapon);
typedef unsigned int (*capi_player_get_current_weapon_tint_index)(void *p);
typedef unsigned long (*capi_player_get_current_weapon)(void *p);
typedef bool (*capi_player_is_dead)(void *p);
typedef bool (*capi_player_is_jumping)(void *p);
typedef bool (*capi_player_is_in_ragdoll)(void *p);
typedef bool (*capi_player_is_aiming)(void *p);
typedef bool (*capi_player_is_shooting)(void *p);
typedef bool (*capi_player_is_reloading)(void *p);
typedef unsigned int (*capi_player_get_armour)(void *p);
typedef void (*capi_player_set_armour)(void *p, unsigned int armour);
typedef float (*capi_player_get_move_speed)(void *p);
typedef Position (*capi_player_get_aim_pos)(void *p);
typedef Rotation (*capi_player_get_head_rotation)(void *p);
typedef bool (*capi_player_is_in_vehicle)(void *p);
typedef void * (*capi_player_get_vehicle)(void *p);
typedef unsigned int (*capi_player_get_seat)(void *p);
typedef void * (*capi_player_get_entity_aiming_at)(void *p);
typedef Position (*capi_player_get_entity_aim_offset)(void *p);
typedef bool (*capi_player_is_flashlight_active)(void *p);
typedef bool (*capi_player_is_connected)(void *p);
typedef unsigned long (*capi_player_get_ping)(void *p);
typedef const char* (*capi_player_get_ip)(void *p);
typedef unsigned long long (*capi_player_get_social_i_d)(void *p);
typedef unsigned long long (*capi_player_get_hwid_hash)(void *p);
typedef unsigned long long (*capi_player_get_hwid_ex_hash)(void *p);
typedef const char* (*capi_player_get_auth_token)(void *p);
typedef void (*capi_player_set_max_armour)(void *p, unsigned int armour);
typedef void (*capi_player_set_current_weapon)(void *p, unsigned long weapon);
typedef void (*capi_player_set_weapon_tint_index)(void *p, unsigned long weapon, unsigned int tintIndex);
typedef void (*capi_player_add_weapon_component)(void *p, unsigned long weapon, unsigned long component);
typedef void (*capi_player_remove_weapon_component)(void *p, unsigned long weapon, unsigned long component);
typedef void (*capi_player_clear_blood_damage)(void *p);
typedef void (*capi_player_set_max_health)(void *p, unsigned int health);
typedef void (*capi_player_give_weapon)(void *p, unsigned long weapon, long ammo, bool selectWeapon);
typedef void (*capi_player_remove_weapon)(void *p, unsigned long weapon);
typedef void (*capi_player_remove_all_weapons)(void *p);
typedef void (*capi_player_set_date_time)(void *p, int day, int month, int year, int hour, int minute, int second);
typedef void (*capi_player_set_weather)(void *p, unsigned long weather);
typedef void (*capi_player_kick)(void *p, const char* reason);
typedef void (*capi_player_set_clothes)(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette);
typedef void (*capi_player_set_dlc_clothes)(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette, unsigned long dlc);
typedef void (*capi_player_set_props)(void *p, unsigned int component, unsigned int drawable, unsigned int texture);
typedef void (*capi_player_set_dlc_props)(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned long dlc);
typedef void (*capi_player_clear_props)(void *p, unsigned int component);
typedef bool (*capi_player_is_entity_in_streaming_range)(void *p, void *entity);
typedef unsigned int (*capi_player_get_max_health)(void *p);
typedef unsigned int (*capi_player_get_max_armour)(void *p);
typedef void (*capi_player_detach)(void *p);
typedef void (*capi_player_attach_to_entity)(void *p, void *e, int otherBoneIndex, int myBoneIndex, Position position, Rotation rotation, bool collision, bool noFixedRotation);
typedef void (*capi_player_set_visible)(void *p, bool toggle);
typedef bool (*capi_player_get_visible)(void *p);
typedef unsigned long (*capi_player_get_id)(void *p);
typedef void * (*capi_player_get_network_owner)(void *p);
typedef void (*capi_player_set_network_owner)(void *p, void *owner, bool disableMigration);

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

typedef void *(*capi_core_create_vehicle)(unsigned long model, float posX, float posY, float posZ,
                                          float rotX, float rotY, float rotZ);

int load_module(const char *path);

// Core
void register_alt_event(const char *resourceName, unsigned short eventType);

void core_log_info(const char *message);
void core_log_debug(const char *message);
void core_log_warning(const char *message);
void core_log_error(const char *message);
void core_log_colored(const char *message);

// Player
const char * player_get_name(void *p);
int player_has_meta_data(void* base, const char *key);
MetaData player_get_meta_data(void* base, const char *key);
void player_set_meta_data(void *base, const char *key, void *val);
void player_delete_meta_data(void *base, const char *key);
int player_has_synced_meta_data(void* base, const char *key);
MetaData player_get_synced_meta_data(void* base, const char *key);
void player_set_synced_meta_data(void *base, const char *key, void *val);
void player_delete_synced_meta_data(void *base, const char *key);
int player_has_stream_synced_meta_data(void* base, const char *key);
MetaData player_get_stream_synced_meta_data(void* base, const char *key);
void player_set_stream_synced_meta_data(void *base, const char *key, void *val);
void player_delete_stream_synced_meta_data(void *base, const char *key);
Position player_get_position(void *p);
void player_set_position(void* p, float x, float y, float z);
Rotation player_get_rotation(void *p);
void player_set_rotation(void *p, float roll, float pitch, float yaw);
long player_get_dimension(void* p);
void player_set_dimension(void* p, long dimension);
void player_spawn(void *p, float x, float y, float z, unsigned long delay);
void player_despawn(void *p);
void player_set_model(void *p, unsigned long model);
unsigned long player_get_model(void *p);
unsigned int player_get_health(void *p);
void player_set_health(void *p, unsigned int health);
bool player_has_weapon_component(void *p, unsigned long weapon, unsigned long component);
unsigned int player_get_weapon_tint_index(void *p, unsigned long weapon);
unsigned int player_get_current_weapon_tint_index(void *p);
unsigned long player_get_current_weapon(void *p);
bool player_is_dead(void *p);
bool player_is_jumping(void *p);
bool player_is_in_ragdoll(void *p);
bool player_is_aiming(void *p);
bool player_is_shooting(void *p);
bool player_is_reloading(void *p);
unsigned int player_get_armour(void *p);
void player_set_armour(void *p, unsigned int armour);
float player_get_move_speed(void *p);
Position player_get_aim_pos(void *p);
Rotation player_get_head_rotation(void *p);
bool player_is_in_vehicle(void *p);
void * player_get_vehicle(void *p);
unsigned int player_get_seat(void *p);
void * player_get_entity_aiming_at(void *p);
Position player_get_entity_aim_offset(void *p);
bool player_is_flashlight_active(void *p);
bool player_is_connected(void *p);
unsigned long player_get_ping(void *p);
const char* player_get_ip(void *p);
unsigned long long player_get_social_id(void *p);
unsigned long long player_get_hwid_hash(void *p);
unsigned long long player_get_hwid_ex_hash(void *p);
const char* player_get_auth_token(void *p);
void player_set_max_armour(void *p, unsigned int armour);
void player_set_current_weapon(void *p, unsigned long weapon);
void player_set_weapon_tint_index(void *p, unsigned long weapon, unsigned int tintIndex);
void player_add_weapon_component(void *p, unsigned long weapon, unsigned long component);
void player_remove_weapon_component(void *p, unsigned long weapon, unsigned long component);
void player_clear_blood_damage(void *p);
void player_set_max_health(void *p, unsigned int health);
void player_give_weapon(void *p, unsigned long weapon, long ammo, bool selectWeapon);
void player_remove_weapon(void *p, unsigned long weapon);
void player_remove_all_weapons(void *p);
void player_set_date_time(void *p, int day, int month, int year, int hour, int minute, int second);
void player_set_weather(void *p, unsigned long weather);
void player_kick(void *p, const char* reason);
void player_set_clothes(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette);
void player_set_dlc_clothes(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette, unsigned long dlc);
void player_set_props(void *p, unsigned int component, unsigned int drawable, unsigned int texture);
void player_set_dlc_props(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned long dlc);
void player_clear_props(void *p, unsigned int component);
bool player_is_entity_in_streaming_range(void *p, void *entity);
unsigned int player_get_max_health(void *p);
unsigned int player_get_max_armour(void *p);
void player_detach(void *p);
void player_attach_to_entity(void *p, void *e, int otherBoneIndex, int myBoneIndex, Position position, Rotation rotation, bool collision, bool noFixedRotation);
void player_set_visible(void *p, bool toggle);
bool player_get_visible(void *p);
unsigned long player_get_id(void *p);
void * player_get_network_owner(void *p);
void player_set_network_owner(void *p, void *owner, bool disableMigration);

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

void *core_create_vehicle(unsigned long model, float posX, float posY, float posZ,
                          float rotX, float rotY, float rotZ);

#endif