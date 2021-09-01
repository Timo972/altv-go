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

typedef struct rot
{
    float roll;
    float pitch;
    float yaw;
} Rotation;

typedef struct rgba
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} RGBA;

typedef struct cloth
{
    unsigned int drawableId;
    unsigned int textureId;
    unsigned int paletteId;
} Cloth;

typedef struct dlcCloth
{
    unsigned long dlc;
    unsigned int drawableId;
    unsigned int textureId;
    unsigned int paletteId;
} DlcCloth;

typedef struct prop
{
    unsigned int drawableId;
    unsigned int textureId;
} Prop;

typedef struct dlcProp
{
    unsigned long dlc;
    unsigned int drawableId;
    unsigned int textureId;
} DlcProp;

typedef struct fireInfo
{
    Position position;
    unsigned long weaponHash;
} FireInfo;

typedef struct neonState
{
    int left;
    int right;
    int front;
    int back;
} VehicleNeonState;

typedef struct entity
{
    unsigned char Type;
    const void *Ptr;
} Entity;

typedef struct array
{
    unsigned long long size;
    void *array;
} Array;

typedef struct data
{
    void *mValue;
    unsigned int Type;
} CustomData;

typedef void (*capi_log)(const char *message);

typedef void (*capi_register_alt_event)(const char *resourceName, unsigned short eventType);
typedef int (*capi_register_alt_export)(const char *resourceName, const char *exportName, CustomData data);
typedef MetaData (*capi_get_alt_export)(const char *targetResourceName, const char *exportName);

// Player
typedef const char *(*capi_player_get_name)(void *p);
typedef int (*capi_player_has_meta_data)(void *base, const char *key);
typedef MetaData (*capi_player_get_meta_data)(void *base, const char *key);
typedef void (*capi_player_set_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_player_delete_meta_data)(void *base, const char *key);
typedef int (*capi_player_has_synced_meta_data)(void *base, const char *key);
typedef MetaData (*capi_player_get_synced_meta_data)(void *base, const char *key);
typedef void (*capi_player_set_synced_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_player_delete_synced_meta_data)(void *base, const char *key);
typedef int (*capi_player_has_stream_synced_meta_data)(void *base, const char *key);
typedef MetaData (*capi_player_get_stream_synced_meta_data)(void *base, const char *key);
typedef void (*capi_player_set_stream_synced_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_player_delete_stream_synced_meta_data)(void *base, const char *key);
typedef Position (*capi_player_get_position)(void *p);
typedef void (*capi_player_set_position)(void *p, float x, float y, float z);
typedef Rotation (*capi_player_get_rotation)(void *p);
typedef void (*capi_player_set_rotation)(void *p, float roll, float pitch, float yaw);
typedef long (*capi_player_get_dimension)(void *p);
typedef void (*capi_player_set_dimension)(void *p, long dimension);
typedef void (*capi_player_spawn)(void *p, float x, float y, float z, unsigned long delay);
typedef void (*capi_player_despawn)(void *p);
typedef void (*capi_player_set_model)(void *p, unsigned long model);
typedef unsigned long (*capi_player_get_model)(void *p);
typedef unsigned int (*capi_player_get_health)(void *p);
typedef void (*capi_player_set_health)(void *p, unsigned int health);
typedef int (*capi_player_has_weapon_component)(void *p, unsigned long weapon, unsigned long component);
typedef Array (*capi_player_get_current_weapon_components)(void *p);
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
typedef void *(*capi_player_get_vehicle)(void *p);
typedef unsigned int (*capi_player_get_seat)(void *p);
typedef void *(*capi_player_get_entity_aiming_at)(void *p);
typedef Position (*capi_player_get_entity_aim_offset)(void *p);
typedef int (*capi_player_is_flashlight_active)(void *p);
typedef int (*capi_player_is_connected)(void *p);
typedef unsigned long (*capi_player_get_ping)(void *p);
typedef const char *(*capi_player_get_ip)(void *p);
typedef unsigned long long (*capi_player_get_social_id)(void *p);
typedef unsigned long long (*capi_player_get_hwid_hash)(void *p);
typedef unsigned long long (*capi_player_get_hwid_ex_hash)(void *p);
typedef const char *(*capi_player_get_auth_token)(void *p);
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
typedef void (*capi_player_kick)(void *p, const char *reason);
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
typedef void *(*capi_player_get_network_owner)(void *p);
typedef void (*capi_player_set_network_owner)(void *p, void *owner, int disableMigration);
typedef void (*capi_player_destroy)(void *p);
typedef int (*capi_player_is_valid)(void *p);

// Vehicle
typedef int (*capi_vehicle_has_meta_data)(void *base, const char *key);
typedef MetaData (*capi_vehicle_get_meta_data)(void *base, const char *key);
typedef void (*capi_vehicle_set_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_vehicle_delete_meta_data)(void *base, const char *key);
typedef int (*capi_vehicle_has_synced_meta_data)(void *base, const char *key);
typedef MetaData (*capi_vehicle_get_synced_meta_data)(void *base, const char *key);
typedef void (*capi_vehicle_set_synced_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_vehicle_delete_synced_meta_data)(void *base, const char *key);
typedef int (*capi_vehicle_has_stream_synced_meta_data)(void *base, const char *key);
typedef MetaData (*capi_vehicle_get_stream_synced_meta_data)(void *base, const char *key);
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
typedef void *(*capi_vehicle_get_network_owner)(void *v);
typedef void (*capi_vehicle_set_network_owner)(void *v, void *owner, int disableMigration);
typedef void *(*capi_vehicle_get_driver)(void *v);
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
typedef const char *(*capi_vehicle_get_numberplate_text)(void *v);
typedef unsigned long (*capi_vehicle_get_window_tint)(void *v);
typedef unsigned long (*capi_vehicle_get_dirt_level)(void *v);
typedef int (*capi_vehicle_is_extra_on)(void *v, unsigned int extraID);
typedef int (*capi_vehicle_is_neon_active)(void *v);
typedef VehicleNeonState (*capi_vehicle_get_neon_active)(void *v);
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
typedef long (*capi_vehicle_get_engine_health)(void *v);
typedef long (*capi_vehicle_get_petrol_tank_health)(void *v);
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
typedef void (*capi_vehicle_set_numberplate_text)(void *v, const char *text);
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
typedef void (*capi_vehicle_set_engine_health)(void *v, long health);
typedef void (*capi_vehicle_set_petrol_tank_health)(void *v, long health);
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
typedef void *(*capi_vehicle_get_attached)(void *v);
typedef void *(*capi_vehicle_get_attached_to)(void *v);
typedef const char *(*capi_vehicle_get_appearance_data_base64)(void *v);
typedef const char *(*capi_vehicle_get_health_data_base64)(void *v);
typedef const char *(*capi_vehicle_get_damage_data_base64)(void *v);
typedef const char *(*capi_vehicle_get_script_data_base64)(void *v);
typedef const char *(*capi_vehicle_get_game_state_base64)(void *v);
typedef void (*capi_vehicle_destroy)(void *v);
typedef int (*capi_vehicle_is_valid)(void *v);

typedef unsigned char (*capi_base_object_get_type)(void *base);

typedef void *(*capi_core_create_mvalue_bool)(int val);
typedef void *(*capi_core_create_mvalue_int)(long long val);
typedef void *(*capi_core_create_mvalue_uint)(unsigned long long val);
typedef void *(*capi_core_create_mvalue_double)(double val);
typedef void *(*capi_core_create_mvalue_string)(const char *val);
typedef void *(*capi_core_create_mvalue_base_object)(unsigned char type, void *val);
typedef void *(*capi_core_create_mvalue_vector2)(float x, float y);
typedef void *(*capi_core_create_mvalue_vector3)(float x, float y, float z);
typedef void *(*capi_core_create_mvalue_rgba)(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
typedef void *(*capi_core_create_mvalue_byte_array)(unsigned char *data, unsigned long long size);
typedef void *(*capi_core_create_mvalue_list)(const char *json, unsigned long long size);
typedef void *(*capi_create_mvalue_function)(const char *resourceName, unsigned long long id);
typedef MetaData (*capi_call_mvalue_function)(void *ptr, CustomData *mValues, unsigned long long size);

typedef int (*capi_core_get_mvalue_bool)(void *val);
typedef long long (*capi_core_get_mvalue_int)(void *val);
typedef unsigned long long (*capi_core_get_mvalue_uint)(void *val);
typedef double (*capi_core_get_mvalue_double)(void *val);
typedef const char *(*capi_core_get_mvalue_string)(void *val);
typedef Entity (*capi_core_get_mvalue_base_object)(void *val);
typedef Position (*capi_core_get_mvalue_vector2)(void *val);
typedef Position (*capi_core_get_mvalue_vector3)(void *val);
typedef RGBA (*capi_core_get_mvalue_rgba)(void *val);
typedef Array (*capi_core_get_mvalue_byte_array)(void *val);

typedef void *(*capi_core_create_vehicle)(unsigned long model, float posX, float posY, float posZ,
                                          float rotX, float rotY, float rotZ);
typedef void *(*capi_core_create_col_shape_cylinder)(float posX, float posY, float posZ, float radius, float height);
typedef void *(*capi_core_create_col_shape_cube)(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2);
typedef void *(*capi_core_create_col_shape_rectangle)(float x1, float y1, float x2, float y2, float z);
typedef void *(*capi_core_create_col_shape_circle)(float posX, float posY, float posZ, float radius);
typedef void *(*capi_core_create_col_shape_sphere)(float posX, float posY, float posZ, float radius);
typedef void *(*capi_core_create_checkpoint)(unsigned char type, float x, float y, float z, float radius, float height, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
typedef void *(*capi_core_create_voice_channel)(int spatial, float maxDistance);

typedef void (*capi_core_trigger_local_event)(const char *ev, CustomData *MValues, unsigned long long MValuesSize);
typedef void (*capi_core_trigger_client_event)(void *p, const char *ev, CustomData *MValues, unsigned long long MValuesSize);
typedef void (*capi_core_trigger_client_event_for)(void **p, unsigned long long clientSize, const char *ev, CustomData *MValues, unsigned long long MValuesSize);
typedef void (*capi_core_trigger_client_event_for_all)(const char *ev, CustomData *MValues, unsigned long long MValuesSize);

// Colshape
typedef int (*capi_col_shape_get_type)(void *c);
typedef int (*capi_col_shape_has_meta_data)(void *base, const char *key);
typedef MetaData (*capi_col_shape_get_meta_data)(void *base, const char *key);
typedef void (*capi_col_shape_set_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_col_shape_delete_meta_data)(void *base, const char *key);
typedef Position (*capi_col_shape_get_position)(void *p);
typedef void (*capi_col_shape_set_position)(void *p, float x, float y, float z);
typedef long (*capi_col_shape_get_dimension)(void *p);
typedef void (*capi_col_shape_set_dimension)(void *p, long dimension);
typedef int (*capi_col_shape_get_col_shape_type)(void *c);
typedef int (*capi_col_shape_is_entity_in)(void *c, void *e);
typedef int (*capi_col_shape_is_point_in)(void *c, float x, float y, float z);
typedef void (*capi_col_shape_set_players_only)(void *c, int state);
typedef int (*capi_col_shape_is_players_only)(void *c);
typedef void (*capi_col_shape_destroy)(void *c);
typedef int (*capi_col_shape_is_valid)(void *c);

// Checkpoint
typedef int (*capi_checkpoint_get_type)(void *c);
typedef int (*capi_checkpoint_has_meta_data)(void *base, const char *key);
typedef MetaData (*capi_checkpoint_get_meta_data)(void *base, const char *key);
typedef void (*capi_checkpoint_set_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_checkpoint_delete_meta_data)(void *base, const char *key);
typedef Position (*capi_checkpoint_get_position)(void *p);
typedef void (*capi_checkpoint_set_position)(void *p, float x, float y, float z);
typedef long (*capi_checkpoint_get_dimension)(void *p);
typedef void (*capi_checkpoint_set_dimension)(void *p, long dimension);
typedef int (*capi_checkpoint_get_col_shape_type)(void *c);
typedef int (*capi_checkpoint_is_entity_in)(void *c, void *e);
typedef int (*capi_checkpoint_is_point_in)(void *c, float x, float y, float z);
typedef void (*capi_checkpoint_set_players_only)(void *c, int state);
typedef int (*capi_checkpoint_is_players_only)(void *c);
typedef unsigned char (*capi_checkpoint_get_checkpoint_type)(void *c);
typedef float (*capi_checkpoint_get_height)(void *c);
typedef float (*capi_checkpoint_get_radius)(void *c);
typedef RGBA (*capi_checkpoint_get_color)(void *c);
typedef Position (*capi_checkpoint_get_next_position)(void *c);
typedef void (*capi_checkpoint_set_checkpoint_type)(void *c, unsigned char type);
typedef void (*capi_checkpoint_set_height)(void *c, float height);
typedef void (*capi_checkpoint_set_radius)(void *c, float radius);
typedef void (*capi_checkpoint_set_color)(void *c, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
typedef void (*capi_checkpoint_set_next_position)(void *c, float x, float y, float z);
typedef void (*capi_checkpoint_destroy)(void *c);
typedef int (*capi_checkpoint_is_valid)(void *c);

// VoiceChannel
typedef int (*capi_voice_channel_get_type)(void *c);
typedef int (*capi_voice_channel_has_meta_data)(void *base, const char *key);
typedef MetaData (*capi_voice_channel_get_meta_data)(void *base, const char *key);
typedef void (*capi_voice_channel_set_meta_data)(void *base, const char *key, void *val);
typedef void (*capi_voice_channel_delete_meta_data)(void *base, const char *key);
typedef int (*capi_voice_channel_is_spatial)(void *v);
typedef float (*capi_voice_channel_get_max_distance)(void *v);
typedef int (*capi_voice_channel_has_player)(void *v, void *p);
typedef void (*capi_voice_channel_add_player)(void *v, void *p);
typedef void (*capi_voice_channel_remove_player)(void *v, void *p);
typedef int (*capi_voice_channel_is_player_muted)(void *v, void *p);
typedef void (*capi_voice_channel_mute_player)(void *v, void *p);
typedef void (*capi_voice_channel_unmute_player)(void *v, void *p);
typedef void (*capi_voice_channel_destroy)(void *v);
typedef int (*capi_voice_channel_is_valid)(void *v);

typedef unsigned long (*capi_core_hash)(const char *str);
typedef int (*capi_core_file_exists)(const char *path);
typedef const char *(*capi_core_read_file)(const char *path);
typedef Entity (*capi_core_get_entity_by_id)(unsigned short id);
typedef int (*capi_core_has_meta_data)(const char *key);
typedef MetaData (*capi_core_get_meta_data)(const char *key);
typedef void (*capi_core_set_meta_data)(const char *key, void *val);
typedef void (*capi_core_delete_meta_data)(const char *key);
typedef int (*capi_core_has_synced_meta_data)(const char *key);
typedef MetaData (*capi_core_get_synced_meta_data)(const char *key);
typedef void (*capi_core_destroy_base_object)(void *h);
typedef int (*capi_core_start_resource)(const char *name);
typedef void (*capi_core_stop_resource)(const char *name);
typedef int (*capi_core_restart_resource)(const char *name);
typedef void (*capi_core_set_synced_meta_data)(const char *key, void *val);
typedef void (*capi_core_delete_synced_meta_data)(const char *key);
typedef Array (*capi_core_get_players_by_name)(const char *name);
typedef Array (*capi_core_get_players)();
typedef Array (*capi_core_get_vehicles)();
typedef void (*capi_core_set_password)(const char *password);
typedef const char * (*capi_core_get_branch)();
typedef const char * (*capi_core_get_version)();
typedef int (*capi_core_is_debug)();
typedef unsigned int (*capi_core_get_sdk_version)();
typedef const char * (*capi_core_get_root_directory)();

int load_module(const char *path);

// Core
void register_alt_event(const char *resourceName, unsigned short eventType);
int register_alt_export(const char *resourceName, const char *exportName, CustomData data);
MetaData get_alt_export(const char *targetResourceName, const char *exportName);

void core_log_info(const char *message);
void core_log_debug(const char *message);
void core_log_warning(const char *message);
void core_log_error(const char *message);
void core_log_colored(const char *message);
unsigned long core_hash(const char *str);
int core_file_exists(const char *path);
const char *core_read_file(const char *path);
Entity core_get_entity_by_id(unsigned short id);
int core_has_meta_data(const char *key);
MetaData core_get_meta_data(const char *key);
void core_set_meta_data(const char *key, void *val);
void core_delete_meta_data(const char *key);
int core_has_synced_meta_data(const char *key);
MetaData core_get_synced_meta_data(const char *key);
void core_destroy_base_object(void *h);
int core_start_resource(const char *name);
void core_stop_resource(const char *name);
int core_restart_resource(const char *name);
void core_set_synced_meta_data(const char *key, void *val);
void core_delete_synced_meta_data(const char *key);
Array core_get_players_by_name(const char *name);
Array core_get_players();
Array core_get_vehicles();
void core_set_password(const char *password);
const char * core_get_branch();
const char * core_get_version();
int core_is_debug();
unsigned int core_get_sdk_version();
const char * core_get_root_directory();

// Player
const char *player_get_name(void *p);
int player_has_meta_data(void *base, const char *key);
MetaData player_get_meta_data(void *base, const char *key);
void player_set_meta_data(void *base, const char *key, void *val);
void player_delete_meta_data(void *base, const char *key);
int player_has_synced_meta_data(void *base, const char *key);
MetaData player_get_synced_meta_data(void *base, const char *key);
void player_set_synced_meta_data(void *base, const char *key, void *val);
void player_delete_synced_meta_data(void *base, const char *key);
int player_has_stream_synced_meta_data(void *base, const char *key);
MetaData player_get_stream_synced_meta_data(void *base, const char *key);
void player_set_stream_synced_meta_data(void *base, const char *key, void *val);
void player_delete_stream_synced_meta_data(void *base, const char *key);
Position player_get_position(void *p);
void player_set_position(void *p, float x, float y, float z);
Rotation player_get_rotation(void *p);
void player_set_rotation(void *p, float roll, float pitch, float yaw);
long player_get_dimension(void *p);
void player_set_dimension(void *p, long dimension);
void player_spawn(void *p, float x, float y, float z, unsigned long delay);
void player_despawn(void *p);
void player_set_model(void *p, unsigned long model);
unsigned long player_get_model(void *p);
unsigned int player_get_health(void *p);
void player_set_health(void *p, unsigned int health);
int player_has_weapon_component(void *p, unsigned long weapon, unsigned long component);
Array player_get_current_weapon_components(void *p);
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
void *player_get_vehicle(void *p);
unsigned int player_get_seat(void *p);
void *player_get_entity_aiming_at(void *p);
Position player_get_entity_aim_offset(void *p);
int player_is_flashlight_active(void *p);
int player_is_connected(void *p);
unsigned long player_get_ping(void *p);
const char *player_get_ip(void *p);
unsigned long long player_get_social_id(void *p);
unsigned long long player_get_hwid_hash(void *p);
unsigned long long player_get_hwid_ex_hash(void *p);
const char *player_get_auth_token(void *p);
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
void player_kick(void *p, const char *reason);
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
void *player_get_network_owner(void *p);
void player_set_network_owner(void *p, void *owner, int disableMigration);
void player_destroy(void *p);
int player_is_valid(void *p);

// Vehicle
int vehicle_has_meta_data(void *base, const char *key);
MetaData vehicle_get_meta_data(void *base, const char *key);
void vehicle_set_meta_data(void *base, const char *key, void *val);
void vehicle_delete_meta_data(void *base, const char *key);
int vehicle_has_synced_meta_data(void *base, const char *key);
MetaData vehicle_get_synced_meta_data(void *base, const char *key);
void vehicle_set_synced_meta_data(void *base, const char *key, void *val);
void vehicle_delete_synced_meta_data(void *base, const char *key);
int vehicle_has_stream_synced_meta_data(void *base, const char *key);
MetaData vehicle_get_stream_synced_meta_data(void *base, const char *key);
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
void *vehicle_get_network_owner(void *v);
void vehicle_set_network_owner(void *v, void *owner, int disableMigration);
void *vehicle_get_driver(void *v);
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
const char *vehicle_get_numberplate_text(void *v);
unsigned long vehicle_get_window_tint(void *v);
unsigned long vehicle_get_dirt_level(void *v);
int vehicle_is_extra_on(void *v, unsigned int extraID);
int vehicle_is_neon_active(void *v);
VehicleNeonState vehicle_get_neon_active(void *v);
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
long vehicle_get_engine_health(void *v);
long vehicle_get_petrol_tank_health(void *v);
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
void vehicle_set_numberplate_text(void *v, const char *text);
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
void vehicle_set_engine_health(void *v, long health);
void vehicle_set_petrol_tank_health(void *v, long health);
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
void *vehicle_get_attached(void *v);
void *vehicle_get_attached_to(void *v);
const char *vehicle_get_appearance_data_base64(void *v);
const char *vehicle_get_game_state_base64(void *v);
const char *vehicle_get_health_data_base64(void *v);
const char *vehicle_get_damage_data_base64(void *v);
const char *vehicle_get_script_data_base64(void *v);
void vehicle_destroy(void *v);
int vehicle_is_valid(void *v);

// MValue
void *core_create_mvalue_bool(int value);
void *core_create_mvalue_int(long long val);
void *core_create_mvalue_uint(unsigned long long val);
void *core_create_mvalue_double(double val);
void *core_create_mvalue_string(const char *val);
void *core_create_mvalue_base_object(unsigned  char type, void *val);
void *core_create_mvalue_vector2(float x, float y);
void *core_create_mvalue_vector3(float x, float y, float z);
void *core_create_mvalue_rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void *core_create_mvalue_byte_array(unsigned char *data, unsigned long long size);
void *core_create_mvalue_list(const char *json, unsigned long long size);
void *create_mvalue_function(const char *resourceName, unsigned long long id);
MetaData call_mvalue_function(void *ptr, CustomData *mValues, unsigned long long size);

int core_get_mvalue_bool(void *val);
long long core_get_mvalue_int(void *val);
unsigned long long core_get_mvalue_uint(void *val);
double core_get_mvalue_double(void *val);
const char *core_get_mvalue_string(void *val);
Entity core_get_mvalue_base_object(void *val);
Position core_get_mvalue_vector2(void *val);
Position core_get_mvalue_vector3(void *val);
RGBA core_get_mvalue_rgba(void *val);
Array core_get_mvalue_byte_array(void *val);

void *core_create_vehicle(unsigned long model, float posX, float posY, float posZ,
                          float rotX, float rotY, float rotZ);
void *core_create_col_shape_cylinder(float posX, float posY, float posZ, float radius, float height);
void *core_create_col_shape_cube(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2);
void *core_create_col_shape_rectangle(float x1, float y1, float x2, float y2, float z);
void *core_create_col_shape_circle(float posX, float posY, float posZ, float radius);
void *core_create_col_shape_sphere(float posX, float posY, float posZ, float radius);
void *core_create_checkpoint(unsigned char type, float x, float y, float z, float radius, float height, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void *core_create_voice_channel(int spatial, float maxDistance);

void core_trigger_local_event(const char *ev, CustomData *MValues, unsigned long long MValuesSize);
void core_trigger_client_event(void *p, const char *ev, CustomData *MValues, unsigned long long MValuesSize);
void core_trigger_client_event_for(void **p, unsigned long long clientSize, const char *ev, CustomData *MValues, unsigned long long MValuesSize);
void core_trigger_client_event_for_all(const char *ev, CustomData *MValues, unsigned long long MValuesSize);

// Colshape
int col_shape_get_type(void *c);
int col_shape_has_meta_data(void *base, const char *key);
MetaData col_shape_get_meta_data(void *base, const char *key);
void col_shape_set_meta_data(void *base, const char *key, void *val);
void col_shape_delete_meta_data(void *base, const char *key);
Position col_shape_get_position(void *p);
void col_shape_set_position(void *p, float x, float y, float z);
long col_shape_get_dimension(void *p);
void col_shape_set_dimension(void *p, long dimension);
int col_shape_get_col_shape_type(void *c);
int col_shape_is_entity_in(void *c, void *e);
int col_shape_is_point_in(void *c, float x, float y, float z);
void col_shape_set_players_only(void *c, int state);
int col_shape_is_players_only(void *c);
void col_shape_destroy(void *c);
int col_shape_is_valid(void *p);

// Checkpoint
int checkpoint_get_type(void *c);
int checkpoint_has_meta_data(void *base, const char *key);
MetaData checkpoint_get_meta_data(void *base, const char *key);
void checkpoint_set_meta_data(void *base, const char *key, void *val);
void checkpoint_delete_meta_data(void *base, const char *key);
Position checkpoint_get_position(void *p);
void checkpoint_set_position(void *p, float x, float y, float z);
long checkpoint_get_dimension(void *p);
void checkpoint_set_dimension(void *p, long dimension);
int checkpoint_get_col_shape_type(void *c);
int checkpoint_is_entity_in(void *c, void *e);
int checkpoint_is_point_in(void *c, float x, float y, float z);
void checkpoint_set_players_only(void *c, int state);
int checkpoint_is_players_only(void *c);
unsigned char checkpoint_get_checkpoint_type(void *c);
float checkpoint_get_height(void *c);
float checkpoint_get_radius(void *c);
RGBA checkpoint_get_color(void *c);
Position checkpoint_get_next_position(void *c);
void checkpoint_set_checkpoint_type(void *c, unsigned char type);
void checkpoint_set_height(void *c, float height);
void checkpoint_set_radius(void *c, float radius);
void checkpoint_set_color(void *c, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void checkpoint_set_next_position(void *c, float x, float y, float z);
void checkpoint_destroy(void *c);
int checkpoint_is_valid(void *p);

// VoiceChannel
int voice_channel_get_type(void *c);
int voice_channel_has_meta_data(void *base, const char *key);
MetaData voice_channel_get_meta_data(void *base, const char *key);
void voice_channel_set_meta_data(void *base, const char *key, void *val);
void voice_channel_delete_meta_data(void *base, const char *key);
int voice_channel_is_spatial(void *v);
float voice_channel_get_max_distance(void *v);
int voice_channel_has_player(void *v, void *p);
void voice_channel_add_player(void *v, void *p);
void voice_channel_remove_player(void *v, void *p);
int voice_channel_is_player_muted(void *v, void *p);
void voice_channel_mute_player(void *v, void *p);
void voice_channel_unmute_player(void *v, void *p);
void voice_channel_destroy(void *v);
int voice_channel_is_valid(void *p);

#endif