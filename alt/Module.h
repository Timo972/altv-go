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

typedef struct rot {
    float roll;
    float pitch;
    float yaw;
} Rotation;

typedef struct rgba {
    unsigned long r;
    unsigned long g;
    unsigned long b;
    unsigned long a;
} RGBA;

typedef struct cloth {
    unsigned int drawableId;
    unsigned int textureId;
    unsigned int paletteId;
} Cloth;

typedef struct dlcCloth {
    unsigned long dlc;
    unsigned int drawableId;
    unsigned int textureId;
    unsigned int paletteId;
} DlcCloth;

typedef struct prop {
    unsigned int drawableId;
    unsigned int textureId;
} Prop;

typedef struct dlcProp {
    unsigned long dlc;
    unsigned int drawableId;
    unsigned int textureId;
} DlcProp;

typedef void (*capi_log)(const char *message);

typedef void (*capi_register_alt_event)(const char *resourceName, unsigned short eventType);

// Player
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
typedef int (*capi_player_has_weapon_component)(void *p, unsigned long weapon, unsigned long component);
typedef unsigned int (*capi_player_get_weapon_tint_index)(void *p, unsigned long weapon);
typedef unsigned int (*capi_player_get_current_weapon_tint_index)(void *p);
typedef unsigned long (*capi_player_get_current_weapon)(void *p);
typedef int (*capi_player_is_dead)(void *p);
typedef int (*capi_player_is_jumping)(void *p);
typedef int (*capi_player_is_in_ragdoll)(void *p);
typedef int (*capi_player_is_aiming)(void *p);
typedef int (*capi_player_is_shooting)(void *p);
typedef int (*capi_player_is_reloading)(void *p);
typedef unsigned int (*capi_player_get_armour)(void *p);
typedef void (*capi_player_set_armour)(void *p, unsigned int armour);
typedef float (*capi_player_get_move_speed)(void *p);
typedef Position (*capi_player_get_aim_pos)(void *p);
typedef Rotation (*capi_player_get_head_rotation)(void *p);
typedef int (*capi_player_is_in_vehicle)(void *p);
typedef void * (*capi_player_get_vehicle)(void *p);
typedef unsigned int (*capi_player_get_seat)(void *p);
typedef void * (*capi_player_get_entity_aiming_at)(void *p);
typedef Position (*capi_player_get_entity_aim_offset)(void *p);
typedef int (*capi_player_is_flashlight_active)(void *p);
typedef int (*capi_player_is_connected)(void *p);
typedef unsigned long (*capi_player_get_ping)(void *p);
typedef const char* (*capi_player_get_ip)(void *p);
typedef unsigned long long (*capi_player_get_social_id)(void *p);
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
typedef void (*capi_player_give_weapon)(void *p, unsigned long weapon, long ammo, int selectWeapon);
typedef void (*capi_player_remove_weapon)(void *p, unsigned long weapon);
typedef void (*capi_player_remove_all_weapons)(void *p);
typedef void (*capi_player_set_date_time)(void *p, int day, int month, int year, int hour, int minute, int second);
typedef void (*capi_player_set_weather)(void *p, unsigned long weather);
typedef void (*capi_player_kick)(void *p, const char* reason);
typedef Cloth (*capi_player_get_clothes)(void *p, unsigned int component);
typedef DlcCloth (*capi_player_get_dlc_clothes)(void *p, unsigned int component);
typedef Prop (*capi_player_get_props)(void *p, unsigned int component);
typedef DlcProp (*capi_player_get_dlc_props)(void *p, unsigned int component);
typedef void (*capi_player_set_clothes)(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette);
typedef void (*capi_player_set_dlc_clothes)(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette, unsigned long dlc);
typedef void (*capi_player_set_props)(void *p, unsigned int component, unsigned int drawable, unsigned int texture);
typedef void (*capi_player_set_dlc_props)(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned long dlc);
typedef void (*capi_player_clear_props)(void *p, unsigned int component);
typedef int (*capi_player_is_entity_in_streaming_range)(void *p, void *entity);
typedef unsigned int (*capi_player_get_max_health)(void *p);
typedef unsigned int (*capi_player_get_max_armour)(void *p);
typedef void (*capi_player_detach)(void *p);
typedef void (*capi_player_attach_to_entity)(void *p, void *e, int otherBoneIndex, int myBoneIndex, Position position, Rotation rotation, int collision, int noFixedRotation);
typedef void (*capi_player_set_visible)(void *p, int toggle);
typedef int (*capi_player_get_visible)(void *p);
typedef unsigned long (*capi_player_get_id)(void *p);
typedef void * (*capi_player_get_network_owner)(void *p);
typedef void (*capi_player_set_network_owner)(void *p, void *owner, int disableMigration);

// Vehicle
typedef int (*capi_vehicle_has_meta_data)(void* base, const char *key);
typedef MetaData (*capi_vehicle_get_meta_data)(void* base, const char *key);
typedef void (*capi_vehicle_set_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_vehicle_delete_meta_data)(void *base, const char *key);
typedef int (*capi_vehicle_has_synced_meta_data)(void* base, const char *key);
typedef MetaData (*capi_vehicle_get_synced_meta_data)(void* base, const char *key);
typedef void (*capi_vehicle_set_synced_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_vehicle_delete_synced_meta_data)(void *base, const char *key);
typedef int (*capi_vehicle_has_stream_synced_meta_data)(void* base, const char *key);
typedef MetaData (*capi_vehicle_get_stream_synced_meta_data)(void* base, const char *key);
typedef void (*capi_vehicle_set_stream_synced_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_vehicle_delete_stream_synced_meta_data)(void *base, const char *key);
typedef Position (*capi_vehicle_get_position)(void *v);
typedef void (*capi_vehicle_set_position)(void *v, float x, float y, float z);
typedef Rotation (*capi_vehicle_get_rotation)(void *v);
typedef void (*capi_vehicle_set_rotation)(void *v, float roll, float pitch, float yaw);
typedef long (*capi_vehicle_get_dimension)(void *v);
typedef void (*capi_vehicle_set_dimension)(void *v, long dimension);
typedef unsigned long (*capi_vehicle_get_id)(void *v);
typedef unsigned long (*capi_vehicle_get_model)(void *v);
typedef void (*capi_vehicle_detach)(void *v);
typedef void (*capi_vehicle_attach_to_entity)(void *v, void *e, int otherBoneIndex, int myBoneIndex, Position position, Rotation rotation, int collision, int noFixedRotation);
typedef void (*capi_vehicle_set_visible)(void *v, int toggle);
typedef int (*capi_vehicle_get_visible)(void *v);
typedef void * (*capi_vehicle_get_network_owner)(void *v);
typedef void (*capi_vehicle_set_network_owner)(void *v, void *owner, int disableMigration);
typedef void * (*capi_vehicle_get_driver)(void *v);
typedef int (*capi_vehicle_is_destroyed)(void *v);
typedef unsigned long (*capi_vehicle_get_mod)(void *v, unsigned int category);
typedef unsigned long (*capi_vehicle_get_mods_count)(void *v, unsigned int category);
typedef unsigned long (*capi_vehicle_get_mod_kits_count)(void *v);
typedef unsigned long (*capi_vehicle_get_mod_kit)(void *v);
typedef int (*capi_vehicle_is_primary_color_r_g_b)(void *v);
typedef unsigned long (*capi_vehicle_get_primary_color)(void *v);
typedef RGBA (*capi_vehicle_get_primary_color_r_g_b)(void *v);
typedef int (*capi_vehicle_is_secondary_color_r_g_b)(void *v);
typedef unsigned long (*capi_vehicle_get_secondary_color)(void *v);
typedef RGBA (*capi_vehicle_get_secondary_color_r_g_b)(void *v);
typedef unsigned long (*capi_vehicle_get_pearl_color)(void *v);
typedef unsigned long (*capi_vehicle_get_wheel_color)(void *v);
typedef unsigned long (*capi_vehicle_get_interior_color)(void *v);
typedef unsigned long (*capi_vehicle_get_dashboard_color)(void *v);
typedef int (*capi_vehicle_is_tire_smoke_color_custom)(void *v);
typedef RGBA (*capi_vehicle_get_tire_smoke_color)(void *v);
typedef unsigned long (*capi_vehicle_get_wheel_type)(void *v);
typedef unsigned long (*capi_vehicle_get_wheel_variation)(void *v);
typedef unsigned long (*capi_vehicle_get_rear_wheel_variation)(void *v);
typedef int (*capi_vehicle_get_custom_tires)(void *v);
typedef unsigned long (*capi_vehicle_get_special_darkness)(void *v);
typedef unsigned long (*capi_vehicle_get_numberplate_index)(void *v);
typedef const char* (*capi_vehicle_get_numberplate_text)(void *v);
typedef unsigned long (*capi_vehicle_get_window_tint)(void *v);
typedef unsigned long (*capi_vehicle_get_dirt_level)(void *v);
typedef int (*capi_vehicle_is_extra_on)(void *v, unsigned int extraID);
typedef int (*capi_vehicle_is_neon_active)(void *v);
typedef void (*capi_vehicle_get_neon_active)(void *v, int *left, int *right, int *front, int *back);
typedef RGBA (*capi_vehicle_get_neon_color)(void *v);
typedef unsigned long (*capi_vehicle_get_livery)(void *v);
typedef unsigned long (*capi_vehicle_get_roof_livery)(void *v);
typedef int (*capi_vehicle_is_engine_on)(void *v);
typedef int (*capi_vehicle_is_handbrake_active)(void *v);
typedef unsigned long (*capi_vehicle_get_headlight_color)(void *v);
typedef unsigned long (*capi_vehicle_get_radio_station_index)(void *v);
typedef int (*capi_vehicle_is_siren_active)(void *v);
typedef unsigned long (*capi_vehicle_get_lock_state)(void *v);
typedef unsigned long (*capi_vehicle_get_door_state)(void *v, unsigned int doorId);
typedef int (*capi_vehicle_is_window_opened)(void *v, unsigned int windowId);
typedef int (*capi_vehicle_is_daylight_on)(void *v);
typedef int (*capi_vehicle_is_nightlight_on)(void *v);
typedef unsigned long (*capi_vehicle_get_roof_state)(void *v);
typedef int (*capi_vehicle_is_flamethrower_active)(void *v);
typedef float (*capi_vehicle_get_lights_multiplier)(void *v);
typedef unsigned long (*capi_vehicle_get_engine_health)(void *v);
typedef unsigned long (*capi_vehicle_get_petrol_tank_health)(void *v);
typedef unsigned long (*capi_vehicle_get_wheels_count)(void *v);
typedef int (*capi_vehicle_is_wheel_burst)(void *v, unsigned int wheelId);
typedef int (*capi_vehicle_does_wheel_has_tire)(void *v, unsigned int wheelId);
typedef int (*capi_vehicle_is_wheel_detached)(void *v, unsigned int wheelId);
typedef int (*capi_vehicle_is_wheel_on_fire)(void *v, unsigned int wheelId);
typedef float (*capi_vehicle_get_wheel_health)(void *v, unsigned int wheelId);
typedef unsigned long (*capi_vehicle_get_repairs_count)(void *v);
typedef unsigned long (*capi_vehicle_get_body_health)(void *v);
typedef unsigned long (*capi_vehicle_get_body_additional_health)(void *v);
typedef unsigned long (*capi_vehicle_get_part_damage_level)(void *v, unsigned int partId);
typedef unsigned long (*capi_vehicle_get_part_bullet_holes)(void *v, unsigned int partId);
typedef int (*capi_vehicle_is_light_damaged)(void *v, unsigned int lightId);
typedef int (*capi_vehicle_is_window_damaged)(void *v, unsigned int windowId);
typedef int (*capi_vehicle_is_special_light_damaged)(void *v, unsigned int specialLightId);
typedef int (*capi_vehicle_has_armored_windows)(void *v);
typedef float (*capi_vehicle_get_armored_window_health)(void *v, unsigned int windowId);
typedef unsigned long (*capi_vehicle_get_armored_window_shoot_count)(void *v, unsigned int windowId);
typedef unsigned long (*capi_vehicle_get_bumper_damage_level)(void *v, unsigned int bumperId);
typedef int (*capi_vehicle_is_manual_engine_control)(void *v);
typedef void (*capi_vehicle_toggle_extra)(void *v, unsigned int extraID, int state);
typedef void (*capi_vehicle_set_fixed)(void *v);
typedef int (*capi_vehicle_set_mod)(void *v, unsigned int category, unsigned int id);
typedef int (*capi_vehicle_set_mod_kit)(void *v, unsigned int id);
typedef void (*capi_vehicle_set_primary_color)(void *v, unsigned int color);
typedef void (*capi_vehicle_set_primary_color_r_g_b)(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a);
typedef void (*capi_vehicle_set_secondary_color)(void *v, unsigned int color);
typedef void (*capi_vehicle_set_secondary_color_r_g_b)(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a);
typedef void (*capi_vehicle_set_pearl_color)(void *v, unsigned int color);
typedef void (*capi_vehicle_set_wheel_color)(void *v, unsigned int color);
typedef void (*capi_vehicle_set_interior_color)(void *v, unsigned int color);
typedef void (*capi_vehicle_set_dashboard_color)(void *v, unsigned int color);
typedef void (*capi_vehicle_set_tire_smoke_color)(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a);
typedef void (*capi_vehicle_set_wheels)(void *v, unsigned int type, unsigned int variation);
typedef void (*capi_vehicle_set_rear_wheels)(void *v, unsigned int variation);
typedef void (*capi_vehicle_set_custom_tires)(void *v, int state);
typedef void (*capi_vehicle_set_special_darkness)(void *v, unsigned int value);
typedef void (*capi_vehicle_set_numberplate_index)(void *v, unsigned int index);
typedef void (*capi_vehicle_set_numberplate_text)(void *v, const char* text);
typedef void (*capi_vehicle_set_window_tint)(void *v, unsigned int tint);
typedef void (*capi_vehicle_set_dirt_level)(void *v, unsigned int level);
typedef void (*capi_vehicle_set_neon_active)(void *v, int left, int right, int front, int back);
typedef void (*capi_vehicle_set_neon_color)(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a);
typedef void (*capi_vehicle_set_livery)(void *v, unsigned int livery);
typedef void (*capi_vehicle_set_roof_livery)(void *v, unsigned int roofLivery);
typedef void (*capi_vehicle_set_engine_on)(void *v, int state);
typedef void (*capi_vehicle_set_headlight_color)(void *v, unsigned int color);
typedef void (*capi_vehicle_set_radio_station_index)(void *v, unsigned int stationIndex);
typedef void (*capi_vehicle_set_siren_active)(void *v, int state);
typedef void (*capi_vehicle_set_lock_state)(void *v, unsigned int state);
typedef void (*capi_vehicle_set_door_state)(void *v, unsigned int doorId, unsigned int state);
typedef void (*capi_vehicle_set_window_opened)(void *v, unsigned int windowId, int state);
typedef void (*capi_vehicle_set_roof_state)(void *v, unsigned int state);
typedef void (*capi_vehicle_set_lights_multiplier)(void *v, float multiplier);
typedef void (*capi_vehicle_set_engine_health)(void *v, unsigned long health);
typedef void (*capi_vehicle_set_petrol_tank_health)(void *v, unsigned long health);
typedef void (*capi_vehicle_set_wheel_burst)(void *v, unsigned int wheelId, int state);
typedef void (*capi_vehicle_set_wheel_has_tire)(void *v, unsigned int wheelId, int state);
typedef void (*capi_vehicle_set_wheel_detached)(void *v, unsigned int wheelId, int state);
typedef void (*capi_vehicle_set_wheel_on_fire)(void *v, unsigned int wheelId, int state);
typedef void (*capi_vehicle_set_wheel_health)(void *v, unsigned int wheelId, float health);
typedef void (*capi_vehicle_set_wheel_fixed)(void *v, unsigned int wheelId);
typedef void (*capi_vehicle_set_body_health)(void *v, unsigned long health);
typedef void (*capi_vehicle_set_body_additional_health)(void *v, unsigned long health);
typedef void (*capi_vehicle_set_part_damage_level)(void *v, unsigned int partId, unsigned int damage);
typedef void (*capi_vehicle_set_part_bullet_holes)(void *v, unsigned int partId, unsigned int shootsCount);
typedef void (*capi_vehicle_set_light_damaged)(void *v, unsigned int lightId, int isDamaged);
typedef void (*capi_vehicle_set_window_damaged)(void *v, unsigned int windowId, int isDamaged);
typedef void (*capi_vehicle_set_special_light_damaged)(void *v, unsigned int specialLightId, int isDamaged);
typedef void (*capi_vehicle_set_armored_window_health)(void *v, unsigned int windowId, float health);
typedef void (*capi_vehicle_set_armored_window_shoot_count)(void *v, unsigned int windowId, unsigned int count);
typedef void (*capi_vehicle_set_bumper_damage_level)(void *v, unsigned int bumperId, unsigned int damageLevel);
typedef void (*capi_vehicle_set_manual_engine_control)(void *v, int state);
typedef void * (*capi_vehicle_get_attached)(void *v);
typedef void * (*capi_vehicle_get_attached_to)(void *v);

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
int player_has_weapon_component(void *p, unsigned long weapon, unsigned long component);
unsigned int player_get_weapon_tint_index(void *p, unsigned long weapon);
unsigned int player_get_current_weapon_tint_index(void *p);
unsigned long player_get_current_weapon(void *p);
int player_is_dead(void *p);
int player_is_jumping(void *p);
int player_is_in_ragdoll(void *p);
int player_is_aiming(void *p);
int player_is_shooting(void *p);
int player_is_reloading(void *p);
unsigned int player_get_armour(void *p);
void player_set_armour(void *p, unsigned int armour);
float player_get_move_speed(void *p);
Position player_get_aim_pos(void *p);
Rotation player_get_head_rotation(void *p);
int player_is_in_vehicle(void *p);
void * player_get_vehicle(void *p);
unsigned int player_get_seat(void *p);
void * player_get_entity_aiming_at(void *p);
Position player_get_entity_aim_offset(void *p);
int player_is_flashlight_active(void *p);
int player_is_connected(void *p);
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
void player_give_weapon(void *p, unsigned long weapon, long ammo, int selectWeapon);
void player_remove_weapon(void *p, unsigned long weapon);
void player_remove_all_weapons(void *p);
void player_set_date_time(void *p, int day, int month, int year, int hour, int minute, int second);
void player_set_weather(void *p, unsigned long weather);
void player_kick(void *p, const char* reason);
Cloth player_get_clothes(void *p, unsigned int component);
DlcCloth player_get_dlc_clothes(void *p, unsigned int component);
Prop player_get_props(void *p, unsigned int component);
DlcProp player_get_dlc_props(void *p, unsigned int component);
void player_set_clothes(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette);
void player_set_dlc_clothes(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette, unsigned long dlc);
void player_set_props(void *p, unsigned int component, unsigned int drawable, unsigned int texture);
void player_set_dlc_props(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned long dlc);
void player_clear_props(void *p, unsigned int component);
int player_is_entity_in_streaming_range(void *p, void *entity);
unsigned int player_get_max_health(void *p);
unsigned int player_get_max_armour(void *p);
void player_detach(void *p);
void player_attach_to_entity(void *p, void *e, int otherBoneIndex, int myBoneIndex, Position position, Rotation rotation, int collision, int noFixedRotation);
void player_set_visible(void *p, int toggle);
int player_get_visible(void *p);
unsigned long player_get_id(void *p);
void * player_get_network_owner(void *p);
void player_set_network_owner(void *p, void *owner, int disableMigration);

// Vehicle
int vehicle_has_meta_data(void* base, const char *key);
MetaData vehicle_get_meta_data(void* base, const char *key);
void vehicle_set_meta_data(void *base, const char *key, void *val);
void vehicle_delete_meta_data(void *base, const char *key);
int vehicle_has_synced_meta_data(void* base, const char *key);
MetaData vehicle_get_synced_meta_data(void* base, const char *key);
void vehicle_set_synced_meta_data(void *base, const char *key, void *val);
void vehicle_delete_synced_meta_data(void *base, const char *key);
int vehicle_has_stream_synced_meta_data(void* base, const char *key);
MetaData vehicle_get_stream_synced_meta_data(void* base, const char *key);
void vehicle_set_stream_synced_meta_data(void *base, const char *key, void *val);
void vehicle_delete_stream_synced_meta_data(void *base, const char *key);
Position vehicle_get_position(void *v);
void vehicle_set_position(void *v, float x, float y, float z);
Rotation vehicle_get_rotation(void *v);
void vehicle_set_rotation(void *v, float roll, float pitch, float yaw);
long vehicle_get_dimension(void *v);
void vehicle_set_dimension(void *v, long dimension);
unsigned long vehicle_get_id(void *v);
unsigned long vehicle_get_model(void *v);
void vehicle_detach(void *v);
void vehicle_attach_to_entity(void *v, void *e, int otherBoneIndex, int myBoneIndex, Position position, Rotation rotation, int collision, int noFixedRotation);
void vehicle_set_visible(void *v, int toggle);
int vehicle_get_visible(void *v);
void * vehicle_get_network_owner(void *v);
void vehicle_set_network_owner(void *v, void *owner, int disableMigration);
void * vehicle_get_driver(void *v);
int vehicle_is_destroyed(void *v);
unsigned long vehicle_get_mod(void *v, unsigned int category);
unsigned long vehicle_get_mods_count(void *v, unsigned int category);
unsigned long vehicle_get_mod_kits_count(void *v);
unsigned long vehicle_get_mod_kit(void *v);
int vehicle_is_primary_color_r_g_b(void *v);
unsigned long vehicle_get_primary_color(void *v);
RGBA vehicle_get_primary_color_r_g_b(void *v);
int vehicle_is_secondary_color_r_g_b(void *v);
unsigned long vehicle_get_secondary_color(void *v);
RGBA vehicle_get_secondary_color_r_g_b(void *v);
unsigned long vehicle_get_pearl_color(void *v);
unsigned long vehicle_get_wheel_color(void *v);
unsigned long vehicle_get_interior_color(void *v);
unsigned long vehicle_get_dashboard_color(void *v);
int vehicle_is_tire_smoke_color_custom(void *v);
RGBA vehicle_get_tire_smoke_color(void *v);
unsigned long vehicle_get_wheel_type(void *v);
unsigned long vehicle_get_wheel_variation(void *v);
unsigned long vehicle_get_rear_wheel_variation(void *v);
int vehicle_get_custom_tires(void *v);
unsigned long vehicle_get_special_darkness(void *v);
unsigned long vehicle_get_numberplate_index(void *v);
const char* vehicle_get_numberplate_text(void *v);
unsigned long vehicle_get_window_tint(void *v);
unsigned long vehicle_get_dirt_level(void *v);
int vehicle_is_extra_on(void *v, unsigned int extraID);
int vehicle_is_neon_active(void *v);
void vehicle_get_neon_active(void *v, int *left, int *right, int *front, int *back);
RGBA vehicle_get_neon_color(void *v);
unsigned long vehicle_get_livery(void *v);
unsigned long vehicle_get_roof_livery(void *v);
int vehicle_is_engine_on(void *v);
int vehicle_is_handbrake_active(void *v);
unsigned long vehicle_get_headlight_color(void *v);
unsigned long vehicle_get_radio_station_index(void *v);
int vehicle_is_siren_active(void *v);
unsigned long vehicle_get_lock_state(void *v);
unsigned long vehicle_get_door_state(void *v, unsigned int doorId);
int vehicle_is_window_opened(void *v, unsigned int windowId);
int vehicle_is_daylight_on(void *v);
int vehicle_is_nightlight_on(void *v);
unsigned long vehicle_get_roof_state(void *v);
int vehicle_is_flamethrower_active(void *v);
float vehicle_get_lights_multiplier(void *v);
unsigned long vehicle_get_engine_health(void *v);
unsigned long vehicle_get_petrol_tank_health(void *v);
unsigned long vehicle_get_wheels_count(void *v);
int vehicle_is_wheel_burst(void *v, unsigned int wheelId);
int vehicle_does_wheel_has_tire(void *v, unsigned int wheelId);
int vehicle_is_wheel_detached(void *v, unsigned int wheelId);
int vehicle_is_wheel_on_fire(void *v, unsigned int wheelId);
float vehicle_get_wheel_health(void *v, unsigned int wheelId);
unsigned long vehicle_get_repairs_count(void *v);
unsigned long vehicle_get_body_health(void *v);
unsigned long vehicle_get_body_additional_health(void *v);
unsigned long vehicle_get_part_damage_level(void *v, unsigned int partId);
unsigned long vehicle_get_part_bullet_holes(void *v, unsigned int partId);
int vehicle_is_light_damaged(void *v, unsigned int lightId);
int vehicle_is_window_damaged(void *v, unsigned int windowId);
int vehicle_is_special_light_damaged(void *v, unsigned int specialLightId);
int vehicle_has_armored_windows(void *v);
float vehicle_get_armored_window_health(void *v, unsigned int windowId);
unsigned long vehicle_get_armored_window_shoot_count(void *v, unsigned int windowId);
unsigned long vehicle_get_bumper_damage_level(void *v, unsigned int bumperId);
int vehicle_is_manual_engine_control(void *v);
void vehicle_toggle_extra(void *v, unsigned int extraID, int state);
void vehicle_set_fixed(void *v);
int vehicle_set_mod(void *v, unsigned int category, unsigned int id);
int vehicle_set_mod_kit(void *v, unsigned int id);
void vehicle_set_primary_color(void *v, unsigned int color);
void vehicle_set_primary_color_r_g_b(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a);
void vehicle_set_secondary_color(void *v, unsigned int color);
void vehicle_set_secondary_color_r_g_b(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a);
void vehicle_set_pearl_color(void *v, unsigned int color);
void vehicle_set_wheel_color(void *v, unsigned int color);
void vehicle_set_interior_color(void *v, unsigned int color);
void vehicle_set_dashboard_color(void *v, unsigned int color);
void vehicle_set_tire_smoke_color(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a);
void vehicle_set_wheels(void *v, unsigned int type, unsigned int variation);
void vehicle_set_rear_wheels(void *v, unsigned int variation);
void vehicle_set_custom_tires(void *v, int state);
void vehicle_set_special_darkness(void *v, unsigned int value);
void vehicle_set_numberplate_index(void *v, unsigned int index);
void vehicle_set_numberplate_text(void *v, const char* text);
void vehicle_set_window_tint(void *v, unsigned int tint);
void vehicle_set_dirt_level(void *v, unsigned int level);
void vehicle_set_neon_active(void *v, int left, int right, int front, int back);
void vehicle_set_neon_color(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a);
void vehicle_set_livery(void *v, unsigned int livery);
void vehicle_set_roof_livery(void *v, unsigned int roofLivery);
void vehicle_set_engine_on(void *v, int state);
void vehicle_set_headlight_color(void *v, unsigned int color);
void vehicle_set_radio_station_index(void *v, unsigned int stationIndex);
void vehicle_set_siren_active(void *v, int state);
void vehicle_set_lock_state(void *v, unsigned int state);
void vehicle_set_door_state(void *v, unsigned int doorId, unsigned int state);
void vehicle_set_window_opened(void *v, unsigned int windowId, int state);
void vehicle_set_roof_state(void *v, unsigned int state);
void vehicle_set_lights_multiplier(void *v, float multiplier);
void vehicle_set_engine_health(void *v, unsigned long health);
void vehicle_set_petrol_tank_health(void *v, unsigned long health);
void vehicle_set_wheel_burst(void *v, unsigned int wheelId, int state);
void vehicle_set_wheel_has_tire(void *v, unsigned int wheelId, int state);
void vehicle_set_wheel_detached(void *v, unsigned int wheelId, int state);
void vehicle_set_wheel_on_fire(void *v, unsigned int wheelId, int state);
void vehicle_set_wheel_health(void *v, unsigned int wheelId, float health);
void vehicle_set_wheel_fixed(void *v, unsigned int wheelId);
void vehicle_set_body_health(void *v, unsigned long health);
void vehicle_set_body_additional_health(void *v, unsigned long health);
void vehicle_set_part_damage_level(void *v, unsigned int partId, unsigned int damage);
void vehicle_set_part_bullet_holes(void *v, unsigned int partId, unsigned int shootsCount);
void vehicle_set_light_damaged(void *v, unsigned int lightId, int isDamaged);
void vehicle_set_window_damaged(void *v, unsigned int windowId, int isDamaged);
void vehicle_set_special_light_damaged(void *v, unsigned int specialLightId, int isDamaged);
void vehicle_set_armored_window_health(void *v, unsigned int windowId, float health);
void vehicle_set_armored_window_shoot_count(void *v, unsigned int windowId, unsigned int count);
void vehicle_set_bumper_damage_level(void *v, unsigned int bumperId, unsigned int damageLevel);
void vehicle_set_manual_engine_control(void *v, int state);
void * vehicle_get_attached(void *v);
void * vehicle_get_attached_to(void *v);

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