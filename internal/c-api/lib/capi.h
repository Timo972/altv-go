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

int load_module(const char *path);


typedef struct pos {
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
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
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

typedef struct fireInfo {
    Position position;
    unsigned long weaponHash;
} FireInfo;

typedef struct neonState {
    unsigned char left;
    unsigned char right;
    unsigned char front;
    unsigned char back;
} VehicleNeonState;

typedef struct entity {
    unsigned char typ;
    void *ptr;
    unsigned int id;
    unsigned int model;
} Entity;

typedef struct array {
    unsigned long long size;
    void *array;
} Array;

typedef struct connectionInfo {
    unsigned int id;
    const char *name;
    unsigned long long socialID;
    const char *socialName;
    unsigned long long hwidHash;
    unsigned long long hwidExHash;
    const char *authToken;
    unsigned char isDebug;
    const char *branch;
    unsigned int build;
    const char *cdnUrl;
    unsigned long long passwordHash;
    const char *ip;
    long long discordUserID;
    const char *cloudAuthHash;
} ConnectionInfo;

typedef struct weapon {
    unsigned int hash;
    unsigned char tintIndex;
    Array components;
} Weapon;

typedef struct headBlendData {
    unsigned int shapeFirstID;
    unsigned int shapeSecondID;
    unsigned int shapeThirdID;
    unsigned int skinFirstID;
    unsigned int skinSecondID;
    unsigned int skinThirdID;
    float shapeMix;
    float skinMix;
    float thirdMix;
} HeadBlendData;

typedef struct headOverlay {
    unsigned char index;
    float opacity;
    unsigned char colorType;
    unsigned char colorIndex;
    unsigned char secondColorIndex;
} HeadOverlay;

typedef struct vector2 {
    float x;
    float y;
} Vector2;

typedef struct vehicleModelInfo {
   const char *title;
   unsigned char modelType;
   unsigned char wheelsCount;
   // bool
   unsigned char hasArmoredWindows;
   unsigned char hasAutoAttachTrailer;
   Array bones;

   unsigned char primaryColor;
   unsigned char secondaryColor;
   unsigned char pearlColor;
   unsigned char wheelsColor;
   unsigned char interiorColor;
   unsigned char dashboardColor;

   unsigned short modKits[2];
   unsigned short extras;
   unsigned short defaultExtras;
} VehicleModelInfo;

typedef struct pedModelInfo {
    unsigned int hash;
    const char* name;
    Array bones;
} PedModelInfo;

typedef struct boneInfo {
    unsigned short id;
    unsigned short index;
    const char* name;
} BoneInfo;



typedef const char * (*capi_player_get_name)(void *p);

typedef int (*capi_player_has_meta_data)(void *base,  const char *key);

typedef Array (*capi_player_get_meta_data)(void *base,  const char *key);

typedef void (*capi_player_set_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_player_delete_meta_data)(void *base,  const char *key);

typedef int (*capi_player_has_synced_meta_data)(void *base,  const char *key);

typedef Array (*capi_player_get_synced_meta_data)(void *base,  const char *key);

typedef void (*capi_player_set_synced_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_player_delete_synced_meta_data)(void *base,  const char *key);

typedef int (*capi_player_has_stream_synced_meta_data)(void *base,  const char *key);

typedef Array (*capi_player_get_stream_synced_meta_data)(void *base,  const char *key);

typedef void (*capi_player_set_stream_synced_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_player_delete_stream_synced_meta_data)(void *base,  const char *key);

typedef Position (*capi_player_get_position)(void *p);

typedef void (*capi_player_set_position)(void *p,  float x,  float y,  float z);

typedef Rotation (*capi_player_get_rotation)(void *p);

typedef void (*capi_player_set_rotation)(void *p,  float roll,  float pitch,  float yaw);

typedef long (*capi_player_get_dimension)(void *p);

typedef void (*capi_player_set_dimension)(void *p,  long dimension);

typedef void (*capi_player_spawn)(void *p,  float x,  float y,  float z,  unsigned long delay);

typedef void (*capi_player_despawn)(void *p);

typedef void (*capi_player_set_model)(void *p,  unsigned long model);

typedef unsigned long (*capi_player_get_model)(void *p);

typedef unsigned int (*capi_player_get_health)(void *p);

typedef void (*capi_player_set_health)(void *p,  unsigned int health);

typedef int (*capi_player_has_weapon_component)(void *p,  unsigned long weapon,  unsigned long component);

typedef Array (*capi_player_get_current_weapon_components)(void *p);

typedef unsigned int (*capi_player_get_weapon_tint_index)(void *p,  unsigned long weapon);

typedef unsigned int (*capi_player_get_current_weapon_tint_index)(void *p);

typedef unsigned long (*capi_player_get_current_weapon)(void *p);

typedef int (*capi_player_is_dead)(void *p);

typedef int (*capi_player_is_jumping)(void *p);

typedef int (*capi_player_is_in_ragdoll)(void *p);

typedef int (*capi_player_is_aiming)(void *p);

typedef int (*capi_player_is_shooting)(void *p);

typedef int (*capi_player_is_reloading)(void *p);

typedef unsigned int (*capi_player_get_armour)(void *p);

typedef void (*capi_player_set_armour)(void *p,  unsigned int armour);

typedef float (*capi_player_get_move_speed)(void *p);

typedef Position (*capi_player_get_aim_pos)(void *p);

typedef Rotation (*capi_player_get_head_rotation)(void *p);

typedef int (*capi_player_is_in_vehicle)(void *p);

typedef Entity (*capi_player_get_vehicle)(void *p);

typedef unsigned int (*capi_player_get_seat)(void *p);

typedef Entity (*capi_player_get_entity_aiming_at)(void *p);

typedef Position (*capi_player_get_entity_aim_offset)(void *p);

typedef int (*capi_player_is_flashlight_active)(void *p);

typedef int (*capi_player_is_connected)(void *p);

typedef unsigned long (*capi_player_get_ping)(void *p);

typedef const char * (*capi_player_get_ip)(void *p);

typedef unsigned long long (*capi_player_get_social_id)(void *p);

typedef unsigned long long (*capi_player_get_hwid_hash)(void *p);

typedef unsigned long long (*capi_player_get_hwid_ex_hash)(void *p);

typedef const char * (*capi_player_get_auth_token)(void *p);

typedef void (*capi_player_set_max_armour)(void *p,  unsigned int armour);

typedef void (*capi_player_set_current_weapon)(void *p,  unsigned long weapon);

typedef void (*capi_player_set_weapon_tint_index)(void *p,  unsigned long weapon,  unsigned int tintIndex);

typedef void (*capi_player_add_weapon_component)(void *p,  unsigned long weapon,  unsigned long component);

typedef void (*capi_player_remove_weapon_component)(void *p,  unsigned long weapon,  unsigned long component);

typedef void (*capi_player_clear_blood_damage)(void *p);

typedef void (*capi_player_set_max_health)(void *p,  unsigned int health);

typedef void (*capi_player_give_weapon)(void *p,  unsigned long weapon,  long ammo,  int selectWeapon);

typedef void (*capi_player_remove_weapon)(void *p,  unsigned long weapon);

typedef void (*capi_player_remove_all_weapons)(void *p,  unsigned short removeAmmo);

typedef void (*capi_player_set_date_time)(void *p,  int day,  int month,  int year,  int hour,  int minute,  int second);

typedef void (*capi_player_set_weather)(void *p,  unsigned long weather);

typedef void (*capi_player_kick)(void *p,  const char *reason);

typedef Cloth (*capi_player_get_clothes)(void *p,  unsigned int component);

typedef DlcCloth (*capi_player_get_dlc_clothes)(void *p,  unsigned int component);

typedef Prop (*capi_player_get_props)(void *p,  unsigned int component);

typedef DlcProp (*capi_player_get_dlc_props)(void *p,  unsigned int component);

typedef void
 (*capi_player_set_clothes)(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned int palette);

typedef void
 (*capi_player_set_dlc_clothes)(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned int palette, 
                     unsigned long dlc);

typedef void (*capi_player_set_props)(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture);

typedef void
 (*capi_player_set_dlc_props)(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned long dlc);

typedef void (*capi_player_clear_props)(void *p,  unsigned int component);

typedef int (*capi_player_is_entity_in_streaming_range)(void *p,  unsigned short entityId);

typedef unsigned int (*capi_player_get_max_health)(void *p);

typedef unsigned int (*capi_player_get_max_armour)(void *p);

typedef void (*capi_player_detach)(void *p);

typedef void
 (*capi_player_attach_to_entity)(void *p,  Entity e,  int otherBoneIndex,  int myBoneIndex,  Position position,  Rotation rotation, 
                      int collision,  int noFixedRotation);

typedef void (*capi_player_set_visible)(void *p,  int toggle);

typedef int (*capi_player_get_visible)(void *p);

typedef unsigned long (*capi_player_get_id)(void *p);

typedef Entity (*capi_player_get_network_owner)(void *p);

typedef void (*capi_player_set_network_owner)(void *p,  void *owner,  int disableMigration);

typedef void (*capi_player_destroy)(void *p);

typedef int (*capi_player_is_valid)(const char* resourceName,  void *p);

typedef int (*capi_player_get_streamed)(void *p);

typedef void (*capi_player_set_streamed)(void *p,  int toggle);

typedef int (*capi_player_get_invincible)(void *p);

typedef void (*capi_player_set_invincible)(void *p,  int toggle);

typedef void (*capi_player_set_into_vehicle)(void *p,  void *v,  unsigned char seat);

typedef int (*capi_player_is_frozen)(void *p);

typedef void (*capi_player_set_frozen)(void *p,  int state);

typedef int (*capi_player_has_collision)(void *p);

typedef void (*capi_player_set_collision)(void *p,  int state);

typedef void
 (*capi_player_play_ambient_speech)(void *p,  const char *speechName,  const char *speechParam,  unsigned int speechDictHash);

typedef int (*capi_player_set_head_overlay)(void *p,  unsigned char overlayID,  unsigned char index,  float opacity);

typedef int (*capi_player_remove_head_overlay)(void *p,  unsigned char overlayID);

typedef int
 (*capi_player_set_head_overlay_color)(void *p,  unsigned char overlayID,  unsigned char colorType,  unsigned char colorIndex, 
                           unsigned char secondColorIndex);

typedef HeadOverlay (*capi_player_get_head_overlay)(void *p,  unsigned char overlayID);

typedef int (*capi_player_set_face_feature)(void *p,  unsigned char index,  float scale);

typedef float (*capi_player_get_face_feature_scale)(void *p,  unsigned char index);

typedef int (*capi_player_remove_face_feature)(void *p,  unsigned char index);

typedef int
 (*capi_player_set_head_blend_palette_color)(void *p,  unsigned char id,  unsigned char red,  unsigned char green,  unsigned char blue);

typedef RGBA (*capi_player_get_head_blend_palette_color)(void *p,  unsigned char id);

typedef void
 (*capi_player_set_head_blend_data)(void *p,  unsigned int shapeFirstID,  unsigned int shapeSecondID,  unsigned int shapeThirdID, 
                        unsigned int skinFirstID,  unsigned int skinSecondID,  unsigned int skinThirdID, 
                        float shapeMix,  float skinMix,  float thirdMix);

typedef HeadBlendData (*capi_player_get_head_blend_data)(void *p);

typedef int (*capi_player_set_eye_color)(void *p,  short eyeColor);

typedef short (*capi_player_get_eye_color)(void *p);

typedef void (*capi_player_set_hair_color)(void *p,  unsigned char hairColor);

typedef unsigned char (*capi_player_get_hair_color)(void *p);

typedef void (*capi_player_set_hair_highlight_color)(void *p,  unsigned char hairHighlightColor);

typedef unsigned char (*capi_player_get_hair_highlight_color)(void *p);

typedef Array (*capi_player_get_weapons)(void *p);

typedef int (*capi_player_has_local_meta_data)(void *p,  const char *key);

typedef void (*capi_player_set_local_meta_data)(void *p,  const char *key,  Array data);

typedef Array (*capi_player_get_local_meta_data)(void *p,  const char *key);

typedef void (*capi_player_delete_local_meta_data)(void *p,  const char *key);

typedef unsigned int (*capi_player_get_current_animation_dict)(void *p);

typedef unsigned int (*capi_player_get_current_animation_name)(void *p);

typedef unsigned char (*capi_player_is_spawned)(void *p);

typedef float (*capi_player_get_forward_speed)(void *p);

typedef float (*capi_player_get_strafe_speed)(void *p);

typedef long long (*capi_player_get_discord_id)(void *p);

typedef unsigned int (*capi_player_get_interior_location)(void *p);

typedef unsigned int (*capi_player_get_last_damaged_body_part)(void *p);

typedef void (*capi_player_set_last_damaged_body_part)(void *p,  unsigned int bodyPart);

typedef int (*capi_runtime_register_alt_event)(const char *resourceName,  unsigned short eventType);

typedef int (*capi_runtime_unregister_alt_event)(const char *resourceName,  unsigned short eventType);

typedef int (*capi_runtime_register_alt_export)(const char *resourceName,  const char *exportName,  Array value);

typedef Array (*capi_runtime_get_alt_export)(const char *targetResourceName,  const char *exportName);

typedef void * (*capi_runtime_create_m_value_function)(const char *resourceName,  unsigned long long id);

typedef Array (*capi_runtime_call_m_value_function)(void *ptr,  Array args);

typedef void (*capi_connection_accept)(void *handle,  unsigned char sendNames);

typedef void (*capi_connection_decline)(void *handle,  const char *reason);

typedef int (*capi_connection_is_accepted)(void *handle);

typedef int (*capi_vehicle_has_meta_data)(void *base,  const char *key);

typedef Array (*capi_vehicle_get_meta_data)(void *base,  const char *key);

typedef void (*capi_vehicle_set_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_vehicle_delete_meta_data)(void *base,  const char *key);

typedef int (*capi_vehicle_has_synced_meta_data)(void *base,  const char *key);

typedef Array (*capi_vehicle_get_synced_meta_data)(void *base,  const char *key);

typedef void (*capi_vehicle_set_synced_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_vehicle_delete_synced_meta_data)(void *base,  const char *key);

typedef int (*capi_vehicle_has_stream_synced_meta_data)(void *base,  const char *key);

typedef Array (*capi_vehicle_get_stream_synced_meta_data)(void *base,  const char *key);

typedef void (*capi_vehicle_set_stream_synced_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_vehicle_delete_stream_synced_meta_data)(void *base,  const char *key);

typedef Position (*capi_vehicle_get_position)(void *v);

typedef void (*capi_vehicle_set_position)(void *v,  float x,  float y,  float z);

typedef Rotation (*capi_vehicle_get_rotation)(void *v);

typedef void (*capi_vehicle_set_rotation)(void *v,  float roll,  float pitch,  float yaw);

typedef long (*capi_vehicle_get_dimension)(void *v);

typedef void (*capi_vehicle_set_dimension)(void *v,  long dimension);

typedef unsigned long (*capi_vehicle_get_id)(void *v);

typedef unsigned long (*capi_vehicle_get_model)(void *v);

typedef void (*capi_vehicle_detach)(void *v);

typedef void
 (*capi_vehicle_attach_to_entity)(void *v,  Entity e,  int otherBoneIndex,  int myBoneIndex,  Position position,  Rotation rotation, 
                       int collision,  int noFixedRotation);

typedef void (*capi_vehicle_set_visible)(void *v,  int toggle);

typedef int (*capi_vehicle_get_visible)(void *v);

typedef Entity (*capi_vehicle_get_network_owner)(void *v);

typedef void (*capi_vehicle_set_network_owner)(void *v,  void *owner,  int disableMigration);

typedef Entity (*capi_vehicle_get_driver)(void *v);

typedef int (*capi_vehicle_is_destroyed)(void *v);

typedef unsigned long (*capi_vehicle_get_mod)(void *v,  unsigned int category);

typedef unsigned long (*capi_vehicle_get_mods_count)(void *v,  unsigned int category);

typedef unsigned long (*capi_vehicle_get_mod_kits_count)(void *v);

typedef unsigned long (*capi_vehicle_get_mod_kit)(void *v);

typedef int (*capi_vehicle_is_primary_color_rgb)(void *v);

typedef unsigned long (*capi_vehicle_get_primary_color)(void *v);

typedef RGBA (*capi_vehicle_get_primary_color_rgb)(void *v);

typedef int (*capi_vehicle_is_secondary_color_rgb)(void *v);

typedef unsigned long (*capi_vehicle_get_secondary_color)(void *v);

typedef RGBA (*capi_vehicle_get_secondary_color_rgb)(void *v);

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

typedef const char * (*capi_vehicle_get_numberplate_text)(void *v);

typedef unsigned long (*capi_vehicle_get_window_tint)(void *v);

typedef unsigned long (*capi_vehicle_get_dirt_level)(void *v);

typedef int (*capi_vehicle_is_extra_on)(void *v,  unsigned int extraID);

typedef int (*capi_vehicle_is_neon_active)(void *v);

typedef VehicleNeonState (*capi_vehicle_get_neon_active)(void *v);

typedef RGBA (*capi_vehicle_get_neon_color)(void *v);

typedef unsigned long (*capi_vehicle_get_livery)(void *v);

typedef unsigned long (*capi_vehicle_get_roof_livery)(void *v);

typedef const char * (*capi_vehicle_get_appearance_data_base64)(void *v);

typedef int (*capi_vehicle_is_engine_on)(void *v);

typedef int (*capi_vehicle_is_handbrake_active)(void *v);

typedef unsigned long (*capi_vehicle_get_headlight_color)(void *v);

typedef unsigned long (*capi_vehicle_get_radio_station_index)(void *v);

typedef int (*capi_vehicle_is_siren_active)(void *v);

typedef unsigned long (*capi_vehicle_get_lock_state)(void *v);

typedef unsigned long (*capi_vehicle_get_door_state)(void *v,  unsigned int doorId);

typedef int (*capi_vehicle_is_window_opened)(void *v,  unsigned int windowId);

typedef int (*capi_vehicle_is_daylight_on)(void *v);

typedef int (*capi_vehicle_is_nightlight_on)(void *v);

typedef unsigned long (*capi_vehicle_get_roof_state)(void *v);

typedef int (*capi_vehicle_is_flamethrower_active)(void *v);

typedef float (*capi_vehicle_get_lights_multiplier)(void *v);

typedef const char * (*capi_vehicle_get_game_state_base64)(void *v);

typedef long (*capi_vehicle_get_engine_health)(void *v);

typedef long (*capi_vehicle_get_petrol_tank_health)(void *v);

typedef unsigned long (*capi_vehicle_get_wheels_count)(void *v);

typedef int (*capi_vehicle_is_wheel_burst)(void *v,  unsigned int wheelId);

typedef int (*capi_vehicle_does_wheel_has_tire)(void *v,  unsigned int wheelId);

typedef int (*capi_vehicle_is_wheel_detached)(void *v,  unsigned int wheelId);

typedef int (*capi_vehicle_is_wheel_on_fire)(void *v,  unsigned int wheelId);

typedef float (*capi_vehicle_get_wheel_health)(void *v,  unsigned int wheelId);

typedef unsigned long (*capi_vehicle_get_repairs_count)(void *v);

typedef unsigned long (*capi_vehicle_get_body_health)(void *v);

typedef unsigned long (*capi_vehicle_get_body_additional_health)(void *v);

typedef const char * (*capi_vehicle_get_health_data_base64)(void *v);

typedef unsigned long (*capi_vehicle_get_part_damage_level)(void *v,  unsigned int partId);

typedef unsigned long (*capi_vehicle_get_part_bullet_holes)(void *v,  unsigned int partId);

typedef int (*capi_vehicle_is_light_damaged)(void *v,  unsigned int lightId);

typedef int (*capi_vehicle_is_window_damaged)(void *v,  unsigned int windowId);

typedef int (*capi_vehicle_is_special_light_damaged)(void *v,  unsigned int specialLightId);

typedef int (*capi_vehicle_has_armored_windows)(void *v);

typedef float (*capi_vehicle_get_armored_window_health)(void *v,  unsigned int windowId);

typedef unsigned long (*capi_vehicle_get_armored_window_shoot_count)(void *v,  unsigned int windowId);

typedef unsigned long (*capi_vehicle_get_bumper_damage_level)(void *v,  unsigned int bumperId);

typedef const char * (*capi_vehicle_get_damage_data_base64)(void *v);

typedef int (*capi_vehicle_is_manual_engine_control)(void *v);

typedef const char * (*capi_vehicle_get_script_data_base64)(void *v);

typedef void (*capi_vehicle_toggle_extra)(void *v,  unsigned int extraID,  int state);

typedef void (*capi_vehicle_set_fixed)(void *v);

typedef int (*capi_vehicle_set_mod)(void *v,  unsigned int category,  unsigned int id);

typedef int (*capi_vehicle_set_mod_kit)(void *v,  unsigned int id);

typedef void (*capi_vehicle_set_primary_color)(void *v,  unsigned int color);

typedef void (*capi_vehicle_set_primary_color_rgb)(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

typedef void (*capi_vehicle_set_secondary_color)(void *v,  unsigned int color);

typedef void (*capi_vehicle_set_secondary_color_rgb)(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

typedef void (*capi_vehicle_set_pearl_color)(void *v,  unsigned int color);

typedef void (*capi_vehicle_set_wheel_color)(void *v,  unsigned int color);

typedef void (*capi_vehicle_set_interior_color)(void *v,  unsigned int color);

typedef void (*capi_vehicle_set_dashboard_color)(void *v,  unsigned int color);

typedef void (*capi_vehicle_set_tire_smoke_color)(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

typedef void (*capi_vehicle_set_wheels)(void *v,  unsigned int type,  unsigned int variation);

typedef void (*capi_vehicle_set_rear_wheels)(void *v,  unsigned int variation);

typedef void (*capi_vehicle_set_custom_tires)(void *v,  int state);

typedef void (*capi_vehicle_set_special_darkness)(void *v,  unsigned int value);

typedef void (*capi_vehicle_set_numberplate_index)(void *v,  unsigned int index);

typedef void (*capi_vehicle_set_numberplate_text)(void *v,  const char *text);

typedef void (*capi_vehicle_set_window_tint)(void *v,  unsigned int tint);

typedef void (*capi_vehicle_set_dirt_level)(void *v,  unsigned int level);

typedef void (*capi_vehicle_set_neon_active)(void *v,  int left,  int right,  int front,  int back);

typedef void (*capi_vehicle_set_neon_color)(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

typedef void (*capi_vehicle_set_livery)(void *v,  unsigned int livery);

typedef void (*capi_vehicle_set_roof_livery)(void *v,  unsigned int roofLivery);

typedef void (*capi_vehicle_load_appearance_data_from_base64)(void *v,  const char *base64);

typedef void (*capi_vehicle_set_engine_on)(void *v,  int state);

typedef void (*capi_vehicle_set_headlight_color)(void *v,  unsigned int color);

typedef void (*capi_vehicle_set_radio_station_index)(void *v,  unsigned int stationIndex);

typedef void (*capi_vehicle_set_siren_active)(void *v,  int state);

typedef void (*capi_vehicle_set_lock_state)(void *v,  unsigned int state);

typedef void (*capi_vehicle_set_door_state)(void *v,  unsigned int doorId,  unsigned int state);

typedef void (*capi_vehicle_set_window_opened)(void *v,  unsigned int windowId,  int state);

typedef void (*capi_vehicle_set_roof_state)(void *v,  unsigned int state);

typedef void (*capi_vehicle_set_lights_multiplier)(void *v,  float multiplier);

typedef void (*capi_vehicle_set_engine_health)(void *v,  unsigned long health);

typedef void (*capi_vehicle_set_petrol_tank_health)(void *v,  unsigned long health);

typedef void (*capi_vehicle_set_wheel_burst)(void *v,  unsigned int wheelId,  int state);

typedef void (*capi_vehicle_set_wheel_has_tire)(void *v,  unsigned int wheelId,  int state);

typedef void (*capi_vehicle_set_wheel_detached)(void *v,  unsigned int wheelId,  int state);

typedef void (*capi_vehicle_set_wheel_on_fire)(void *v,  unsigned int wheelId,  int state);

typedef void (*capi_vehicle_set_wheel_health)(void *v,  unsigned int wheelId,  float health);

typedef void (*capi_vehicle_set_wheel_fixed)(void *v,  unsigned int wheelId);

typedef void (*capi_vehicle_set_body_health)(void *v,  unsigned long health);

typedef void (*capi_vehicle_set_body_additional_health)(void *v,  unsigned long health);

typedef void (*capi_vehicle_set_part_damage_level)(void *v,  unsigned int partId,  unsigned int damage);

typedef void (*capi_vehicle_set_part_bullet_holes)(void *v,  unsigned int partId,  unsigned int shootsCount);

typedef void (*capi_vehicle_set_light_damaged)(void *v,  unsigned int lightId,  int isDamaged);

typedef void (*capi_vehicle_set_window_damaged)(void *v,  unsigned int windowId,  int isDamaged);

typedef void (*capi_vehicle_set_special_light_damaged)(void *v,  unsigned int specialLightId,  int isDamaged);

typedef void (*capi_vehicle_set_armored_window_health)(void *v,  unsigned int windowId,  float health);

typedef void (*capi_vehicle_set_armored_window_shoot_count)(void *v,  unsigned int windowId,  unsigned int count);

typedef void (*capi_vehicle_set_bumper_damage_level)(void *v,  unsigned int bumperId,  unsigned int damageLevel);

typedef void (*capi_vehicle_set_manual_engine_control)(void *v,  int state);

typedef void (*capi_vehicle_load_damage_data_from_base64)(void *v,  const char *base64);

typedef void (*capi_vehicle_load_script_data_from_base64)(void *v,  const char *base64);

typedef void (*capi_vehicle_load_game_state_from_base64)(void *v,  const char *base64);

typedef void (*capi_vehicle_load_health_data_from_base64)(void *v,  const char *base64);

typedef Entity (*capi_vehicle_get_attached)(void *v);

typedef Entity (*capi_vehicle_get_attached_to)(void *v);

typedef void (*capi_vehicle_destroy)(void *v);

typedef int (*capi_vehicle_is_valid)(const char *resourceName,  void *p);

typedef int (*capi_vehicle_get_streamed)(void *v);

typedef void (*capi_vehicle_set_streamed)(void *v,  int toggle);

typedef int (*capi_vehicle_is_frozen)(void *v);

typedef void (*capi_vehicle_set_frozen)(void *v,  int state);

typedef int (*capi_vehicle_has_collision)(void *v);

typedef void (*capi_vehicle_set_collision)(void *v,  int state);

typedef int (*capi_vehicle_is_drift_mode)(void *v);

typedef void (*capi_vehicle_set_drift_mode)(void *v,  int state);

typedef int (*capi_vehicle_is_train_mission_train)(void *v);

typedef void (*capi_vehicle_set_train_mission_train)(void *v,  int value);

typedef char (*capi_vehicle_get_train_track_id)(void *v);

typedef void (*capi_vehicle_set_train_track_id)(void *v,  char trackId);

typedef Entity (*capi_vehicle_get_train_engine_id)(void *v);

typedef void (*capi_vehicle_set_train_engine_id)(void *v,  void *e);

typedef char (*capi_vehicle_get_train_config_index)(void *v);

typedef void (*capi_vehicle_set_train_config_index)(void *v,  char trainConfigIndex);

typedef float (*capi_vehicle_get_train_distance_from_engine)(void *v);

typedef void (*capi_vehicle_set_train_distance_from_engine)(void *v,  float distanceFromEngine);

typedef int (*capi_vehicle_is_train_engine)(void *v);

typedef void (*capi_vehicle_set_train_is_engine)(void *v,  int isEngine);

typedef int (*capi_vehicle_is_train_caboose)(void *v);

typedef void (*capi_vehicle_set_train_is_caboose)(void *v,  int isCaboose);

typedef int (*capi_vehicle_get_train_direction)(void *v);

typedef void (*capi_vehicle_set_train_direction)(void *v,  int direction);

typedef int (*capi_vehicle_has_train_passenger_carriages)(void *v);

typedef void (*capi_vehicle_set_train_has_passenger_carriages)(void *v,  int hasPassengerCarriages);

typedef int (*capi_vehicle_get_train_render_derailed)(void *v);

typedef void (*capi_vehicle_set_train_render_derailed)(void *v,  int renderDerailed);

typedef int (*capi_vehicle_get_train_force_doors_open)(void *v);

typedef void (*capi_vehicle_set_train_force_doors_open)(void *v,  int forceDoorsOpen);

typedef float (*capi_vehicle_get_train_cruise_speed)(void *v);

typedef void (*capi_vehicle_set_train_cruise_speed)(void *v,  float cruiseSpeed);

typedef char (*capi_vehicle_get_train_carriage_config_index)(void *v);

typedef void (*capi_vehicle_set_train_carriage_config_index)(void *v,  char carriageConfigIndex);

typedef Entity (*capi_vehicle_get_train_linked_to_backward_id)(void *v);

typedef void (*capi_vehicle_set_train_linked_to_backward_id)(void *v,  void *e);

typedef Entity (*capi_vehicle_get_train_linked_to_forward_id)(void *v);

typedef void (*capi_vehicle_set_train_linked_to_forward_id)(void *v,  void *e);

typedef void (*capi_vehicle_set_train_unk1)(void *v,  int unk1);

typedef int (*capi_vehicle_get_train_unk1)(void *v);

typedef void (*capi_vehicle_set_train_unk2)(void *v,  int unk2);

typedef int (*capi_vehicle_get_train_unk2)(void *v);

typedef void (*capi_vehicle_set_train_unk3)(void *v,  int unk3);

typedef int (*capi_vehicle_get_train_unk3)(void *v);

typedef int (*capi_vehicle_is_boat_anchor_active)(void *v);

typedef void (*capi_vehicle_set_boat_anchor_active)(void *v,  int state);

typedef int (*capi_vehicle_set_search_light)(void *v,  int state,  Entity e);

typedef unsigned char (*capi_vehicle_get_light_state)(void *v);

typedef void (*capi_vehicle_set_light_state)(void *v,  unsigned char state);

typedef unsigned char (*capi_vehicle_has_timed_explosion)(void *v);

typedef Entity (*capi_vehicle_get_timed_explosion_culprit)(void *v);

typedef unsigned int (*capi_vehicle_get_timed_explosion_time)(void *v);

typedef void (*capi_vehicle_set_timed_explosion)(void *v,  unsigned char state,  void *culprit,  unsigned int time);

typedef unsigned char (*capi_vehicle_is_towing_disabled)(void *v);

typedef void (*capi_vehicle_set_towing_disabled)(void *v,  unsigned char state);

typedef float (*capi_vehicle_get_rocket_refuel_speed)(void *v);

typedef void (*capi_vehicle_set_rocket_refuel_speed)(void *v,  float speed);

typedef unsigned int (*capi_vehicle_get_counter_measure_count)(void *v);

typedef void (*capi_vehicle_set_counter_measure_count)(void *v,  unsigned int count);

typedef float (*capi_vehicle_get_script_max_speed)(void *v);

typedef void (*capi_vehicle_set_script_max_speed)(void *v,  float speed);

typedef int (*capi_vehicle_get_weapon_capacity)(void *v,  unsigned char index);

typedef void (*capi_vehicle_set_weapon_capacity)(void *v,  unsigned char index,  int capacity);

typedef unsigned char (*capi_vehicle_get_hybrid_extra_active)(void *v);

typedef void (*capi_vehicle_set_hybrid_extra_active)(void *v,  unsigned char state);

typedef unsigned char (*capi_vehicle_get_hybrid_extra_state)(void *v);

typedef void (*capi_vehicle_set_hybrid_extra_state)(void *v,  unsigned char state);

typedef int (*capi_voice_channel_is_valid)(const char* resourceName,  void *p);

typedef int (*capi_voice_channel_get_type)(void *c);

typedef int (*capi_voice_channel_has_meta_data)(void* base,  const char *key);

typedef Array (*capi_voice_channel_get_meta_data)(void* base,  const char *key);

typedef void (*capi_voice_channel_set_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_voice_channel_delete_meta_data)(void *base,  const char *key);

typedef void (*capi_voice_channel_destroy)(void *b);

typedef int (*capi_voice_channel_is_spatial)(void *v);

typedef float (*capi_voice_channel_get_max_distance)(void *v);

typedef int (*capi_voice_channel_has_player)(void *v,  void *p);

typedef void (*capi_voice_channel_add_player)(void *v,  void *p);

typedef void (*capi_voice_channel_remove_player)(void *v,  void *p);

typedef int (*capi_voice_channel_is_player_muted)(void *v,  void *p);

typedef void (*capi_voice_channel_mute_player)(void *v,  void *p);

typedef void (*capi_voice_channel_unmute_player)(void *v,  void *p);

typedef unsigned long long (*capi_voice_channel_get_player_count)(void *v);

typedef Array (*capi_voice_channel_get_players)(void *v);

typedef int (*capi_blip_get_type)(void *c);

typedef int (*capi_blip_has_meta_data)(void *base,  const char *key);

typedef Array (*capi_blip_get_meta_data)(void *base,  const char *key);

typedef void (*capi_blip_set_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_blip_delete_meta_data)(void *base,  const char *key);

typedef void (*capi_blip_destroy)(void *b);

typedef int (*capi_blip_is_valid)(const char *resourceName,  void *p);

typedef Position (*capi_blip_get_position)(void *p);

typedef void (*capi_blip_set_position)(void *p,  float x,  float y,  float z);

typedef long (*capi_blip_get_dimension)(void *p);

typedef void (*capi_blip_set_dimension)(void *p,  long dimension);

typedef int (*capi_blip_is_global)(void *b);

typedef Array (*capi_blip_get_targets)(void *b);

typedef int (*capi_blip_is_attached)(void *b);

typedef Entity (*capi_blip_attached_to)(void *b);

typedef void (*capi_blip_attach_to)(void *b,  Entity e);

typedef unsigned char (*capi_blip_get_blip_type)(void *b);

typedef Vector2 (*capi_blip_get_scale_xy)(void *b);

typedef void (*capi_blip_set_scale_xy)(void *b,  Vector2 scale);

typedef int (*capi_blip_get_display)(void *b);

typedef void (*capi_blip_set_display)(void *b,  int display);

typedef int (*capi_blip_get_sprite)(void *b);

typedef int (*capi_blip_get_color)(void *b);

typedef RGBA (*capi_blip_get_secondary_color)(void *b);

typedef int (*capi_blip_get_alpha)(void *b);

typedef int (*capi_blip_get_flash_timer)(void *b);

typedef int (*capi_blip_get_flash_interval)(void *b);

typedef int (*capi_blip_get_as_friendly)(void *b);

typedef int (*capi_blip_get_route)(void *b);

typedef int (*capi_blip_get_bright)(void *b);

typedef int (*capi_blip_get_number)(void *b);

typedef int (*capi_blip_get_show_cone)(void *b);

typedef int (*capi_blip_get_flashes)(void *b);

typedef int (*capi_blip_get_flashes_alternate)(void *b);

typedef int (*capi_blip_get_as_short_range)(void *b);

typedef int (*capi_blip_get_priority)(void *b);

typedef float (*capi_blip_get_rotation)(void *b);

typedef const char * (*capi_blip_get_gxt_name)(void *b);

typedef const char * (*capi_blip_get_name)(void *b);

typedef RGBA (*capi_blip_get_route_color)(void *b);

typedef int (*capi_blip_get_pulse)(void *b);

typedef int (*capi_blip_get_as_mission_creator)(void *b);

typedef int (*capi_blip_get_tick_visible)(void *b);

typedef int (*capi_blip_get_heading_indicator_visible)(void *b);

typedef int (*capi_blip_get_outline_indicator_visible)(void *b);

typedef int (*capi_blip_get_friend_indicator_visible)(void *b);

typedef int (*capi_blip_get_crew_indicator_visible)(void *b);

typedef int (*capi_blip_get_category)(void *b);

typedef int (*capi_blip_get_as_high_detail)(void *b);

typedef int (*capi_blip_get_shrinked)(void *b);

typedef void (*capi_blip_set_sprite)(void *b,  int sprite);

typedef void (*capi_blip_set_color)(void *b,  int color);

typedef void (*capi_blip_set_route)(void *b,  int state);

typedef void (*capi_blip_set_route_color)(void *b,  RGBA color);

typedef void (*capi_blip_set_secondary_color)(void *b,  RGBA color);

typedef void (*capi_blip_set_alpha)(void *b,  int alpha);

typedef void (*capi_blip_set_flash_timer)(void *b,  int timer);

typedef void (*capi_blip_set_flash_interval)(void *b,  int interval);

typedef void (*capi_blip_set_as_friendly)(void *b,  int friendly);

typedef void (*capi_blip_set_bright)(void *b,  int bright);

typedef void (*capi_blip_set_number)(void *b,  int number);

typedef void (*capi_blip_set_show_cone)(void *b,  int state);

typedef void (*capi_blip_set_flashes)(void *b,  int state);

typedef void (*capi_blip_set_flashes_alternate)(void *b,  int state);

typedef void (*capi_blip_set_as_short_range)(void *b,  int state);

typedef void (*capi_blip_set_priority)(void *b,  int state);

typedef void (*capi_blip_set_rotation)(void *b,  float rot);

typedef void (*capi_blip_set_gxt_name)(void *b,  const char *name);

typedef void (*capi_blip_set_name)(void *b,  const char *name);

typedef void (*capi_blip_set_pulse)(void *b,  int val);

typedef void (*capi_blip_set_as_mission_creator)(void *b,  int val);

typedef void (*capi_blip_set_tick_visible)(void *b,  int val);

typedef void (*capi_blip_set_heading_indicator_visible)(void *b,  int val);

typedef void (*capi_blip_set_outline_indicator_visible)(void *b,  int val);

typedef void (*capi_blip_set_friend_indicator_visible)(void *b,  int val);

typedef void (*capi_blip_set_crew_indicator_visible)(void *b,  int val);

typedef void (*capi_blip_set_category)(void *b,  int val);

typedef void (*capi_blip_set_as_high_detail)(void *b,  int val);

typedef void (*capi_blip_set_shrinked)(void *b,  int val);

typedef void (*capi_blip_fade)(void *b,  unsigned int opacity,  unsigned int duration);

typedef void (*capi_core_log_info)(const char *message);

typedef void (*capi_core_log_debug)(const char *message);

typedef void (*capi_core_log_warning)(const char *message);

typedef void (*capi_core_log_error)(const char *message);

typedef void (*capi_core_log_colored)(const char *message);

typedef Entity (*capi_core_create_vehicle)(unsigned long model,  float posX,  float posY,  float posZ, 
                                float rotX,  float rotY,  float rotZ);

typedef Entity
 (*capi_core_create_checkpoint)(unsigned char type,  float x,  float y,  float z,  float radius,  float height,  unsigned char r, 
                      unsigned char g,  unsigned char b,  unsigned char a,  unsigned long streamingDistance);

typedef Entity (*capi_core_create_voice_channel)(int spacial,  float maxDistance);

typedef const char * (*capi_core_get_version)();

typedef const char * (*capi_core_get_branch)();

typedef int (*capi_core_is_debug)();

typedef unsigned long (*capi_core_hash)(const char *str);

typedef int (*capi_core_file_exists)(const char *path);

typedef const char * (*capi_core_read_file)(const char *path);

typedef Entity (*capi_core_get_entity_by_id)(unsigned short id);

typedef Entity (*capi_core_get_base_object_by_id)(unsigned char type,  unsigned int id);

typedef Array (*capi_core_get_entities)();

typedef Array (*capi_core_get_players)();

typedef Array (*capi_core_get_vehicles)();

typedef Array (*capi_core_get_blips)();

typedef Array (*capi_core_get_col_shapes)();

typedef Array (*capi_core_get_checkpoints)();

typedef Array (*capi_core_get_virtual_entities)();

typedef Array (*capi_core_get_virtual_entity_groups)();

typedef Array (*capi_core_get_markers)();

typedef Array (*capi_core_get_peds)();

typedef int (*capi_core_has_meta_data)(const char *key);

typedef Array (*capi_core_get_meta_data)(const char *key);

typedef void (*capi_core_set_meta_data)(const char *key,  Array data);

typedef void (*capi_core_delete_meta_data)(const char *key);

typedef int (*capi_core_has_synced_meta_data)(const char *key);

typedef Array (*capi_core_get_synced_meta_data)(const char *key);

typedef Array (*capi_core_get_required_permissions)();

typedef Array (*capi_core_get_optional_permissions)();

typedef void (*capi_core_destroy_base_object)(void *h);

typedef const char * (*capi_core_get_root_directory)();

typedef int (*capi_core_start_resource)(const char *name);

typedef void (*capi_core_stop_resource)(const char *name);

typedef void (*capi_core_restart_resource)(const char *name);

typedef void (*capi_core_set_synced_meta_data)(const char *key,  Array data);

typedef void (*capi_core_delete_synced_meta_data)(const char *key);

typedef Array (*capi_core_get_players_by_name)(const char *name);

typedef unsigned int (*capi_core_get_net_time)();

typedef void (*capi_core_set_password)(const char *password);

typedef const char * (*capi_core_get_sdk_hash)();

typedef Entity (*capi_core_create_col_shape_cylinder)(float posX,  float posY,  float posZ,  float radius,  float height);

typedef Entity (*capi_core_create_col_shape_cube)(float posX1,  float posY1,  float posZ1,  float posX2,  float posY2,  float posZ2);

typedef Entity (*capi_core_create_col_shape_rectangle)(float x1,  float y1,  float x2,  float y2,  float z);

typedef Entity (*capi_core_create_col_shape_circle)(float posX,  float posY,  float posZ,  float radius);

typedef Entity (*capi_core_create_col_shape_sphere)(float posX,  float posY,  float posZ,  float radius);

typedef void (*capi_core_trigger_local_event)(const char *ev,  Array args);

typedef void (*capi_core_trigger_local_event_raw)(const char* ev,  char* bytes,  unsigned long long size);

typedef void (*capi_core_trigger_client_event)(void *p,  const char *ev,  Array args);

typedef void (*capi_core_trigger_client_event_for)(Array clients,  const char *ev,  Array args);

typedef void (*capi_core_trigger_client_event_for_all)(const char *ev,  Array args);

typedef Entity (*capi_core_create_point_blip_position)(float x,  float y,  float z,  unsigned short global);

typedef Entity (*capi_core_create_point_blip_entity)(Entity entity,  unsigned short global);

typedef Entity (*capi_core_create_area_blip)(float x,  float y,  float z,  float width,  float height,  unsigned short global);

typedef Entity (*capi_core_create_radius_blip)(float x,  float y,  float z,  float radius,  unsigned short global);

typedef Entity (*capi_core_create_col_shape_polygon)(float minZ,  float maxZ,  Array points);

typedef Array (*capi_core_get_all_resources)();

typedef const char * (*capi_core_string_to_sha256)(const char *str);

typedef void (*capi_core_stop_server)();

typedef VehicleModelInfo (*capi_core_get_vehicle_model_by_hash)(unsigned int hash);

typedef PedModelInfo (*capi_core_get_ped_model_by_hash)(unsigned int hash);

typedef Array (*capi_core_get_server_config)();

typedef unsigned long long (*capi_core_hash_server_password)(const char *password);

typedef void* (*capi_core_get_resource_by_name)(const char *resourceName);

typedef int (*capi_col_shape_get_type)(void *c);

typedef int (*capi_col_shape_has_meta_data)(void* base,  const char *key);

typedef Array (*capi_col_shape_get_meta_data)(void* base,  const char *key);

typedef void (*capi_col_shape_set_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_col_shape_delete_meta_data)(void *base,  const char *key);

typedef void (*capi_col_shape_destroy)(void *b);

typedef int (*capi_col_shape_is_valid)(const char* resourceName,  void *p);

typedef Position (*capi_col_shape_get_position)(void *p);

typedef void (*capi_col_shape_set_position)(void* p,  float x,  float y,  float z);

typedef long (*capi_col_shape_get_dimension)(void* p);

typedef void (*capi_col_shape_set_dimension)(void* p,  long dimension);

typedef int (*capi_col_shape_get_col_shape_type)(void *c);

typedef int (*capi_col_shape_is_entity_in)(void *c,  Entity e);

typedef int (*capi_col_shape_is_point_in)(void *c,  float x,  float y,  float z);

typedef void (*capi_col_shape_set_players_only)(void *c,  int state);

typedef int (*capi_col_shape_is_players_only)(void *c);

typedef unsigned char (*capi_col_shape_is_entity_id_in)(void *c,  unsigned short id);

typedef unsigned char (*capi_resource_is_started)(void *r);

typedef const char * (*capi_resource_get_type)(void *r);

typedef const char * (*capi_resource_get_name)(void* r);

typedef const char * (*capi_resource_get_main)(void *r);

typedef Array (*capi_resource_get_config)(void *r);

typedef Array (*capi_resource_get_exports)(void *r);

typedef Array (*capi_resource_get_dependencies)(void *r);

typedef Array (*capi_resource_get_dependants)(void *r);

typedef Array (*capi_resource_get_required_permissions)(void *r);

typedef Array (*capi_resource_get_optional_permissions)(void *r);

typedef const char * (*capi_resource_get_path)(void *r);

typedef int (*capi_checkpoint_get_type)(void *c);

typedef int (*capi_checkpoint_has_meta_data)(void* base,  const char *key);

typedef Array (*capi_checkpoint_get_meta_data)(void* base,  const char *key);

typedef void (*capi_checkpoint_set_meta_data)(void *base,  const char *key,  Array data);

typedef void (*capi_checkpoint_delete_meta_data)(void *base,  const char *key);

typedef void (*capi_checkpoint_destroy)(void *b);

typedef int (*capi_checkpoint_is_valid)(const char* resourceName,  void *p);

typedef Position (*capi_checkpoint_get_position)(void *p);

typedef void (*capi_checkpoint_set_position)(void* p,  float x,  float y,  float z);

typedef long (*capi_checkpoint_get_dimension)(void* p);

typedef void (*capi_checkpoint_set_dimension)(void* p,  long dimension);

typedef int (*capi_checkpoint_get_col_shape_type)(void *c);

typedef int (*capi_checkpoint_is_entity_in)(void *c,  Entity e);

typedef int (*capi_checkpoint_is_point_in)(void *c,  float x,  float y,  float z);

typedef void (*capi_checkpoint_set_players_only)(void *c,  int state);

typedef int (*capi_checkpoint_is_players_only)(void *c);

typedef unsigned char (*capi_checkpoint_is_entity_id_in)(void *c,  unsigned short id);

typedef unsigned char (*capi_checkpoint_get_checkpoint_type)(void *c);

typedef float (*capi_checkpoint_get_height)(void *c);

typedef float (*capi_checkpoint_get_radius)(void *c);

typedef RGBA (*capi_checkpoint_get_color)(void *c);

typedef Position (*capi_checkpoint_get_next_position)(void *c);

typedef void (*capi_checkpoint_set_checkpoint_type)(void *c,  unsigned char type);

typedef void (*capi_checkpoint_set_height)(void *c,  float height);

typedef void (*capi_checkpoint_set_radius)(void *c,  float radius);

typedef void (*capi_checkpoint_set_color)(void *c,  unsigned char r,  unsigned char g,  unsigned char b,  unsigned char a);

typedef void (*capi_checkpoint_set_next_position)(void *c,  float x,  float y,  float z);



const char * player_get_name(void *p);

int player_has_meta_data(void *base,  const char *key);

Array player_get_meta_data(void *base,  const char *key);

void player_set_meta_data(void *base,  const char *key,  Array data);

void player_delete_meta_data(void *base,  const char *key);

int player_has_synced_meta_data(void *base,  const char *key);

Array player_get_synced_meta_data(void *base,  const char *key);

void player_set_synced_meta_data(void *base,  const char *key,  Array data);

void player_delete_synced_meta_data(void *base,  const char *key);

int player_has_stream_synced_meta_data(void *base,  const char *key);

Array player_get_stream_synced_meta_data(void *base,  const char *key);

void player_set_stream_synced_meta_data(void *base,  const char *key,  Array data);

void player_delete_stream_synced_meta_data(void *base,  const char *key);

Position player_get_position(void *p);

void player_set_position(void *p,  float x,  float y,  float z);

Rotation player_get_rotation(void *p);

void player_set_rotation(void *p,  float roll,  float pitch,  float yaw);

long player_get_dimension(void *p);

void player_set_dimension(void *p,  long dimension);

void player_spawn(void *p,  float x,  float y,  float z,  unsigned long delay);

void player_despawn(void *p);

void player_set_model(void *p,  unsigned long model);

unsigned long player_get_model(void *p);

unsigned int player_get_health(void *p);

void player_set_health(void *p,  unsigned int health);

int player_has_weapon_component(void *p,  unsigned long weapon,  unsigned long component);

Array player_get_current_weapon_components(void *p);

unsigned int player_get_weapon_tint_index(void *p,  unsigned long weapon);

unsigned int player_get_current_weapon_tint_index(void *p);

unsigned long player_get_current_weapon(void *p);

int player_is_dead(void *p);

int player_is_jumping(void *p);

int player_is_in_ragdoll(void *p);

int player_is_aiming(void *p);

int player_is_shooting(void *p);

int player_is_reloading(void *p);

unsigned int player_get_armour(void *p);

void player_set_armour(void *p,  unsigned int armour);

float player_get_move_speed(void *p);

Position player_get_aim_pos(void *p);

Rotation player_get_head_rotation(void *p);

int player_is_in_vehicle(void *p);

Entity player_get_vehicle(void *p);

unsigned int player_get_seat(void *p);

Entity player_get_entity_aiming_at(void *p);

Position player_get_entity_aim_offset(void *p);

int player_is_flashlight_active(void *p);

int player_is_connected(void *p);

unsigned long player_get_ping(void *p);

const char * player_get_ip(void *p);

unsigned long long player_get_social_id(void *p);

unsigned long long player_get_hwid_hash(void *p);

unsigned long long player_get_hwid_ex_hash(void *p);

const char * player_get_auth_token(void *p);

void player_set_max_armour(void *p,  unsigned int armour);

void player_set_current_weapon(void *p,  unsigned long weapon);

void player_set_weapon_tint_index(void *p,  unsigned long weapon,  unsigned int tintIndex);

void player_add_weapon_component(void *p,  unsigned long weapon,  unsigned long component);

void player_remove_weapon_component(void *p,  unsigned long weapon,  unsigned long component);

void player_clear_blood_damage(void *p);

void player_set_max_health(void *p,  unsigned int health);

void player_give_weapon(void *p,  unsigned long weapon,  long ammo,  int selectWeapon);

void player_remove_weapon(void *p,  unsigned long weapon);

void player_remove_all_weapons(void *p,  unsigned short removeAmmo);

void player_set_date_time(void *p,  int day,  int month,  int year,  int hour,  int minute,  int second);

void player_set_weather(void *p,  unsigned long weather);

void player_kick(void *p,  const char *reason);

Cloth player_get_clothes(void *p,  unsigned int component);

DlcCloth player_get_dlc_clothes(void *p,  unsigned int component);

Prop player_get_props(void *p,  unsigned int component);

DlcProp player_get_dlc_props(void *p,  unsigned int component);

void
 player_set_clothes(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned int palette);

void
 player_set_dlc_clothes(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned int palette, 
                     unsigned long dlc);

void player_set_props(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture);

void
 player_set_dlc_props(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned long dlc);

void player_clear_props(void *p,  unsigned int component);

int player_is_entity_in_streaming_range(void *p,  unsigned short entityId);

unsigned int player_get_max_health(void *p);

unsigned int player_get_max_armour(void *p);

void player_detach(void *p);

void
 player_attach_to_entity(void *p,  Entity e,  int otherBoneIndex,  int myBoneIndex,  Position position,  Rotation rotation, 
                      int collision,  int noFixedRotation);

void player_set_visible(void *p,  int toggle);

int player_get_visible(void *p);

unsigned long player_get_id(void *p);

Entity player_get_network_owner(void *p);

void player_set_network_owner(void *p,  void *owner,  int disableMigration);

void player_destroy(void *p);

int player_is_valid(const char* resourceName,  void *p);

int player_get_streamed(void *p);

void player_set_streamed(void *p,  int toggle);

int player_get_invincible(void *p);

void player_set_invincible(void *p,  int toggle);

void player_set_into_vehicle(void *p,  void *v,  unsigned char seat);

int player_is_frozen(void *p);

void player_set_frozen(void *p,  int state);

int player_has_collision(void *p);

void player_set_collision(void *p,  int state);

void
 player_play_ambient_speech(void *p,  const char *speechName,  const char *speechParam,  unsigned int speechDictHash);

int player_set_head_overlay(void *p,  unsigned char overlayID,  unsigned char index,  float opacity);

int player_remove_head_overlay(void *p,  unsigned char overlayID);

int
 player_set_head_overlay_color(void *p,  unsigned char overlayID,  unsigned char colorType,  unsigned char colorIndex, 
                           unsigned char secondColorIndex);

HeadOverlay player_get_head_overlay(void *p,  unsigned char overlayID);

int player_set_face_feature(void *p,  unsigned char index,  float scale);

float player_get_face_feature_scale(void *p,  unsigned char index);

int player_remove_face_feature(void *p,  unsigned char index);

int
 player_set_head_blend_palette_color(void *p,  unsigned char id,  unsigned char red,  unsigned char green,  unsigned char blue);

RGBA player_get_head_blend_palette_color(void *p,  unsigned char id);

void
 player_set_head_blend_data(void *p,  unsigned int shapeFirstID,  unsigned int shapeSecondID,  unsigned int shapeThirdID, 
                        unsigned int skinFirstID,  unsigned int skinSecondID,  unsigned int skinThirdID, 
                        float shapeMix,  float skinMix,  float thirdMix);

HeadBlendData player_get_head_blend_data(void *p);

int player_set_eye_color(void *p,  short eyeColor);

short player_get_eye_color(void *p);

void player_set_hair_color(void *p,  unsigned char hairColor);

unsigned char player_get_hair_color(void *p);

void player_set_hair_highlight_color(void *p,  unsigned char hairHighlightColor);

unsigned char player_get_hair_highlight_color(void *p);

Array player_get_weapons(void *p);

int player_has_local_meta_data(void *p,  const char *key);

void player_set_local_meta_data(void *p,  const char *key,  Array data);

Array player_get_local_meta_data(void *p,  const char *key);

void player_delete_local_meta_data(void *p,  const char *key);

unsigned int player_get_current_animation_dict(void *p);

unsigned int player_get_current_animation_name(void *p);

unsigned char player_is_spawned(void *p);

float player_get_forward_speed(void *p);

float player_get_strafe_speed(void *p);

long long player_get_discord_id(void *p);

unsigned int player_get_interior_location(void *p);

unsigned int player_get_last_damaged_body_part(void *p);

void player_set_last_damaged_body_part(void *p,  unsigned int bodyPart);

int runtime_register_alt_event(const char *resourceName,  unsigned short eventType);

int runtime_unregister_alt_event(const char *resourceName,  unsigned short eventType);

int runtime_register_alt_export(const char *resourceName,  const char *exportName,  Array value);

Array runtime_get_alt_export(const char *targetResourceName,  const char *exportName);

void * runtime_create_m_value_function(const char *resourceName,  unsigned long long id);

Array runtime_call_m_value_function(void *ptr,  Array args);

void connection_accept(void *handle,  unsigned char sendNames);

void connection_decline(void *handle,  const char *reason);

int connection_is_accepted(void *handle);

int vehicle_has_meta_data(void *base,  const char *key);

Array vehicle_get_meta_data(void *base,  const char *key);

void vehicle_set_meta_data(void *base,  const char *key,  Array data);

void vehicle_delete_meta_data(void *base,  const char *key);

int vehicle_has_synced_meta_data(void *base,  const char *key);

Array vehicle_get_synced_meta_data(void *base,  const char *key);

void vehicle_set_synced_meta_data(void *base,  const char *key,  Array data);

void vehicle_delete_synced_meta_data(void *base,  const char *key);

int vehicle_has_stream_synced_meta_data(void *base,  const char *key);

Array vehicle_get_stream_synced_meta_data(void *base,  const char *key);

void vehicle_set_stream_synced_meta_data(void *base,  const char *key,  Array data);

void vehicle_delete_stream_synced_meta_data(void *base,  const char *key);

Position vehicle_get_position(void *v);

void vehicle_set_position(void *v,  float x,  float y,  float z);

Rotation vehicle_get_rotation(void *v);

void vehicle_set_rotation(void *v,  float roll,  float pitch,  float yaw);

long vehicle_get_dimension(void *v);

void vehicle_set_dimension(void *v,  long dimension);

unsigned long vehicle_get_id(void *v);

unsigned long vehicle_get_model(void *v);

void vehicle_detach(void *v);

void
 vehicle_attach_to_entity(void *v,  Entity e,  int otherBoneIndex,  int myBoneIndex,  Position position,  Rotation rotation, 
                       int collision,  int noFixedRotation);

void vehicle_set_visible(void *v,  int toggle);

int vehicle_get_visible(void *v);

Entity vehicle_get_network_owner(void *v);

void vehicle_set_network_owner(void *v,  void *owner,  int disableMigration);

Entity vehicle_get_driver(void *v);

int vehicle_is_destroyed(void *v);

unsigned long vehicle_get_mod(void *v,  unsigned int category);

unsigned long vehicle_get_mods_count(void *v,  unsigned int category);

unsigned long vehicle_get_mod_kits_count(void *v);

unsigned long vehicle_get_mod_kit(void *v);

int vehicle_is_primary_color_rgb(void *v);

unsigned long vehicle_get_primary_color(void *v);

RGBA vehicle_get_primary_color_rgb(void *v);

int vehicle_is_secondary_color_rgb(void *v);

unsigned long vehicle_get_secondary_color(void *v);

RGBA vehicle_get_secondary_color_rgb(void *v);

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

const char * vehicle_get_numberplate_text(void *v);

unsigned long vehicle_get_window_tint(void *v);

unsigned long vehicle_get_dirt_level(void *v);

int vehicle_is_extra_on(void *v,  unsigned int extraID);

int vehicle_is_neon_active(void *v);

VehicleNeonState vehicle_get_neon_active(void *v);

RGBA vehicle_get_neon_color(void *v);

unsigned long vehicle_get_livery(void *v);

unsigned long vehicle_get_roof_livery(void *v);

const char * vehicle_get_appearance_data_base64(void *v);

int vehicle_is_engine_on(void *v);

int vehicle_is_handbrake_active(void *v);

unsigned long vehicle_get_headlight_color(void *v);

unsigned long vehicle_get_radio_station_index(void *v);

int vehicle_is_siren_active(void *v);

unsigned long vehicle_get_lock_state(void *v);

unsigned long vehicle_get_door_state(void *v,  unsigned int doorId);

int vehicle_is_window_opened(void *v,  unsigned int windowId);

int vehicle_is_daylight_on(void *v);

int vehicle_is_nightlight_on(void *v);

unsigned long vehicle_get_roof_state(void *v);

int vehicle_is_flamethrower_active(void *v);

float vehicle_get_lights_multiplier(void *v);

const char * vehicle_get_game_state_base64(void *v);

long vehicle_get_engine_health(void *v);

long vehicle_get_petrol_tank_health(void *v);

unsigned long vehicle_get_wheels_count(void *v);

int vehicle_is_wheel_burst(void *v,  unsigned int wheelId);

int vehicle_does_wheel_has_tire(void *v,  unsigned int wheelId);

int vehicle_is_wheel_detached(void *v,  unsigned int wheelId);

int vehicle_is_wheel_on_fire(void *v,  unsigned int wheelId);

float vehicle_get_wheel_health(void *v,  unsigned int wheelId);

unsigned long vehicle_get_repairs_count(void *v);

unsigned long vehicle_get_body_health(void *v);

unsigned long vehicle_get_body_additional_health(void *v);

const char * vehicle_get_health_data_base64(void *v);

unsigned long vehicle_get_part_damage_level(void *v,  unsigned int partId);

unsigned long vehicle_get_part_bullet_holes(void *v,  unsigned int partId);

int vehicle_is_light_damaged(void *v,  unsigned int lightId);

int vehicle_is_window_damaged(void *v,  unsigned int windowId);

int vehicle_is_special_light_damaged(void *v,  unsigned int specialLightId);

int vehicle_has_armored_windows(void *v);

float vehicle_get_armored_window_health(void *v,  unsigned int windowId);

unsigned long vehicle_get_armored_window_shoot_count(void *v,  unsigned int windowId);

unsigned long vehicle_get_bumper_damage_level(void *v,  unsigned int bumperId);

const char * vehicle_get_damage_data_base64(void *v);

int vehicle_is_manual_engine_control(void *v);

const char * vehicle_get_script_data_base64(void *v);

void vehicle_toggle_extra(void *v,  unsigned int extraID,  int state);

void vehicle_set_fixed(void *v);

int vehicle_set_mod(void *v,  unsigned int category,  unsigned int id);

int vehicle_set_mod_kit(void *v,  unsigned int id);

void vehicle_set_primary_color(void *v,  unsigned int color);

void vehicle_set_primary_color_rgb(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

void vehicle_set_secondary_color(void *v,  unsigned int color);

void vehicle_set_secondary_color_rgb(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

void vehicle_set_pearl_color(void *v,  unsigned int color);

void vehicle_set_wheel_color(void *v,  unsigned int color);

void vehicle_set_interior_color(void *v,  unsigned int color);

void vehicle_set_dashboard_color(void *v,  unsigned int color);

void vehicle_set_tire_smoke_color(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

void vehicle_set_wheels(void *v,  unsigned int type,  unsigned int variation);

void vehicle_set_rear_wheels(void *v,  unsigned int variation);

void vehicle_set_custom_tires(void *v,  int state);

void vehicle_set_special_darkness(void *v,  unsigned int value);

void vehicle_set_numberplate_index(void *v,  unsigned int index);

void vehicle_set_numberplate_text(void *v,  const char *text);

void vehicle_set_window_tint(void *v,  unsigned int tint);

void vehicle_set_dirt_level(void *v,  unsigned int level);

void vehicle_set_neon_active(void *v,  int left,  int right,  int front,  int back);

void vehicle_set_neon_color(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

void vehicle_set_livery(void *v,  unsigned int livery);

void vehicle_set_roof_livery(void *v,  unsigned int roofLivery);

void vehicle_load_appearance_data_from_base64(void *v,  const char *base64);

void vehicle_set_engine_on(void *v,  int state);

void vehicle_set_headlight_color(void *v,  unsigned int color);

void vehicle_set_radio_station_index(void *v,  unsigned int stationIndex);

void vehicle_set_siren_active(void *v,  int state);

void vehicle_set_lock_state(void *v,  unsigned int state);

void vehicle_set_door_state(void *v,  unsigned int doorId,  unsigned int state);

void vehicle_set_window_opened(void *v,  unsigned int windowId,  int state);

void vehicle_set_roof_state(void *v,  unsigned int state);

void vehicle_set_lights_multiplier(void *v,  float multiplier);

void vehicle_set_engine_health(void *v,  unsigned long health);

void vehicle_set_petrol_tank_health(void *v,  unsigned long health);

void vehicle_set_wheel_burst(void *v,  unsigned int wheelId,  int state);

void vehicle_set_wheel_has_tire(void *v,  unsigned int wheelId,  int state);

void vehicle_set_wheel_detached(void *v,  unsigned int wheelId,  int state);

void vehicle_set_wheel_on_fire(void *v,  unsigned int wheelId,  int state);

void vehicle_set_wheel_health(void *v,  unsigned int wheelId,  float health);

void vehicle_set_wheel_fixed(void *v,  unsigned int wheelId);

void vehicle_set_body_health(void *v,  unsigned long health);

void vehicle_set_body_additional_health(void *v,  unsigned long health);

void vehicle_set_part_damage_level(void *v,  unsigned int partId,  unsigned int damage);

void vehicle_set_part_bullet_holes(void *v,  unsigned int partId,  unsigned int shootsCount);

void vehicle_set_light_damaged(void *v,  unsigned int lightId,  int isDamaged);

void vehicle_set_window_damaged(void *v,  unsigned int windowId,  int isDamaged);

void vehicle_set_special_light_damaged(void *v,  unsigned int specialLightId,  int isDamaged);

void vehicle_set_armored_window_health(void *v,  unsigned int windowId,  float health);

void vehicle_set_armored_window_shoot_count(void *v,  unsigned int windowId,  unsigned int count);

void vehicle_set_bumper_damage_level(void *v,  unsigned int bumperId,  unsigned int damageLevel);

void vehicle_set_manual_engine_control(void *v,  int state);

void vehicle_load_damage_data_from_base64(void *v,  const char *base64);

void vehicle_load_script_data_from_base64(void *v,  const char *base64);

void vehicle_load_game_state_from_base64(void *v,  const char *base64);

void vehicle_load_health_data_from_base64(void *v,  const char *base64);

Entity vehicle_get_attached(void *v);

Entity vehicle_get_attached_to(void *v);

void vehicle_destroy(void *v);

int vehicle_is_valid(const char *resourceName,  void *p);

int vehicle_get_streamed(void *v);

void vehicle_set_streamed(void *v,  int toggle);

int vehicle_is_frozen(void *v);

void vehicle_set_frozen(void *v,  int state);

int vehicle_has_collision(void *v);

void vehicle_set_collision(void *v,  int state);

int vehicle_is_drift_mode(void *v);

void vehicle_set_drift_mode(void *v,  int state);

int vehicle_is_train_mission_train(void *v);

void vehicle_set_train_mission_train(void *v,  int value);

char vehicle_get_train_track_id(void *v);

void vehicle_set_train_track_id(void *v,  char trackId);

Entity vehicle_get_train_engine_id(void *v);

void vehicle_set_train_engine_id(void *v,  void *e);

char vehicle_get_train_config_index(void *v);

void vehicle_set_train_config_index(void *v,  char trainConfigIndex);

float vehicle_get_train_distance_from_engine(void *v);

void vehicle_set_train_distance_from_engine(void *v,  float distanceFromEngine);

int vehicle_is_train_engine(void *v);

void vehicle_set_train_is_engine(void *v,  int isEngine);

int vehicle_is_train_caboose(void *v);

void vehicle_set_train_is_caboose(void *v,  int isCaboose);

int vehicle_get_train_direction(void *v);

void vehicle_set_train_direction(void *v,  int direction);

int vehicle_has_train_passenger_carriages(void *v);

void vehicle_set_train_has_passenger_carriages(void *v,  int hasPassengerCarriages);

int vehicle_get_train_render_derailed(void *v);

void vehicle_set_train_render_derailed(void *v,  int renderDerailed);

int vehicle_get_train_force_doors_open(void *v);

void vehicle_set_train_force_doors_open(void *v,  int forceDoorsOpen);

float vehicle_get_train_cruise_speed(void *v);

void vehicle_set_train_cruise_speed(void *v,  float cruiseSpeed);

char vehicle_get_train_carriage_config_index(void *v);

void vehicle_set_train_carriage_config_index(void *v,  char carriageConfigIndex);

Entity vehicle_get_train_linked_to_backward_id(void *v);

void vehicle_set_train_linked_to_backward_id(void *v,  void *e);

Entity vehicle_get_train_linked_to_forward_id(void *v);

void vehicle_set_train_linked_to_forward_id(void *v,  void *e);

void vehicle_set_train_unk1(void *v,  int unk1);

int vehicle_get_train_unk1(void *v);

void vehicle_set_train_unk2(void *v,  int unk2);

int vehicle_get_train_unk2(void *v);

void vehicle_set_train_unk3(void *v,  int unk3);

int vehicle_get_train_unk3(void *v);

int vehicle_is_boat_anchor_active(void *v);

void vehicle_set_boat_anchor_active(void *v,  int state);

int vehicle_set_search_light(void *v,  int state,  Entity e);

unsigned char vehicle_get_light_state(void *v);

void vehicle_set_light_state(void *v,  unsigned char state);

unsigned char vehicle_has_timed_explosion(void *v);

Entity vehicle_get_timed_explosion_culprit(void *v);

unsigned int vehicle_get_timed_explosion_time(void *v);

void vehicle_set_timed_explosion(void *v,  unsigned char state,  void *culprit,  unsigned int time);

unsigned char vehicle_is_towing_disabled(void *v);

void vehicle_set_towing_disabled(void *v,  unsigned char state);

float vehicle_get_rocket_refuel_speed(void *v);

void vehicle_set_rocket_refuel_speed(void *v,  float speed);

unsigned int vehicle_get_counter_measure_count(void *v);

void vehicle_set_counter_measure_count(void *v,  unsigned int count);

float vehicle_get_script_max_speed(void *v);

void vehicle_set_script_max_speed(void *v,  float speed);

int vehicle_get_weapon_capacity(void *v,  unsigned char index);

void vehicle_set_weapon_capacity(void *v,  unsigned char index,  int capacity);

unsigned char vehicle_get_hybrid_extra_active(void *v);

void vehicle_set_hybrid_extra_active(void *v,  unsigned char state);

unsigned char vehicle_get_hybrid_extra_state(void *v);

void vehicle_set_hybrid_extra_state(void *v,  unsigned char state);

int voice_channel_is_valid(const char* resourceName,  void *p);

int voice_channel_get_type(void *c);

int voice_channel_has_meta_data(void* base,  const char *key);

Array voice_channel_get_meta_data(void* base,  const char *key);

void voice_channel_set_meta_data(void *base,  const char *key,  Array data);

void voice_channel_delete_meta_data(void *base,  const char *key);

void voice_channel_destroy(void *b);

int voice_channel_is_spatial(void *v);

float voice_channel_get_max_distance(void *v);

int voice_channel_has_player(void *v,  void *p);

void voice_channel_add_player(void *v,  void *p);

void voice_channel_remove_player(void *v,  void *p);

int voice_channel_is_player_muted(void *v,  void *p);

void voice_channel_mute_player(void *v,  void *p);

void voice_channel_unmute_player(void *v,  void *p);

unsigned long long voice_channel_get_player_count(void *v);

Array voice_channel_get_players(void *v);

int blip_get_type(void *c);

int blip_has_meta_data(void *base,  const char *key);

Array blip_get_meta_data(void *base,  const char *key);

void blip_set_meta_data(void *base,  const char *key,  Array data);

void blip_delete_meta_data(void *base,  const char *key);

void blip_destroy(void *b);

int blip_is_valid(const char *resourceName,  void *p);

Position blip_get_position(void *p);

void blip_set_position(void *p,  float x,  float y,  float z);

long blip_get_dimension(void *p);

void blip_set_dimension(void *p,  long dimension);

int blip_is_global(void *b);

Array blip_get_targets(void *b);

int blip_is_attached(void *b);

Entity blip_attached_to(void *b);

void blip_attach_to(void *b,  Entity e);

unsigned char blip_get_blip_type(void *b);

Vector2 blip_get_scale_xy(void *b);

void blip_set_scale_xy(void *b,  Vector2 scale);

int blip_get_display(void *b);

void blip_set_display(void *b,  int display);

int blip_get_sprite(void *b);

int blip_get_color(void *b);

RGBA blip_get_secondary_color(void *b);

int blip_get_alpha(void *b);

int blip_get_flash_timer(void *b);

int blip_get_flash_interval(void *b);

int blip_get_as_friendly(void *b);

int blip_get_route(void *b);

int blip_get_bright(void *b);

int blip_get_number(void *b);

int blip_get_show_cone(void *b);

int blip_get_flashes(void *b);

int blip_get_flashes_alternate(void *b);

int blip_get_as_short_range(void *b);

int blip_get_priority(void *b);

float blip_get_rotation(void *b);

const char * blip_get_gxt_name(void *b);

const char * blip_get_name(void *b);

RGBA blip_get_route_color(void *b);

int blip_get_pulse(void *b);

int blip_get_as_mission_creator(void *b);

int blip_get_tick_visible(void *b);

int blip_get_heading_indicator_visible(void *b);

int blip_get_outline_indicator_visible(void *b);

int blip_get_friend_indicator_visible(void *b);

int blip_get_crew_indicator_visible(void *b);

int blip_get_category(void *b);

int blip_get_as_high_detail(void *b);

int blip_get_shrinked(void *b);

void blip_set_sprite(void *b,  int sprite);

void blip_set_color(void *b,  int color);

void blip_set_route(void *b,  int state);

void blip_set_route_color(void *b,  RGBA color);

void blip_set_secondary_color(void *b,  RGBA color);

void blip_set_alpha(void *b,  int alpha);

void blip_set_flash_timer(void *b,  int timer);

void blip_set_flash_interval(void *b,  int interval);

void blip_set_as_friendly(void *b,  int friendly);

void blip_set_bright(void *b,  int bright);

void blip_set_number(void *b,  int number);

void blip_set_show_cone(void *b,  int state);

void blip_set_flashes(void *b,  int state);

void blip_set_flashes_alternate(void *b,  int state);

void blip_set_as_short_range(void *b,  int state);

void blip_set_priority(void *b,  int state);

void blip_set_rotation(void *b,  float rot);

void blip_set_gxt_name(void *b,  const char *name);

void blip_set_name(void *b,  const char *name);

void blip_set_pulse(void *b,  int val);

void blip_set_as_mission_creator(void *b,  int val);

void blip_set_tick_visible(void *b,  int val);

void blip_set_heading_indicator_visible(void *b,  int val);

void blip_set_outline_indicator_visible(void *b,  int val);

void blip_set_friend_indicator_visible(void *b,  int val);

void blip_set_crew_indicator_visible(void *b,  int val);

void blip_set_category(void *b,  int val);

void blip_set_as_high_detail(void *b,  int val);

void blip_set_shrinked(void *b,  int val);

void blip_fade(void *b,  unsigned int opacity,  unsigned int duration);

void core_log_info(const char *message);

void core_log_debug(const char *message);

void core_log_warning(const char *message);

void core_log_error(const char *message);

void core_log_colored(const char *message);

Entity core_create_vehicle(unsigned long model,  float posX,  float posY,  float posZ, 
                                float rotX,  float rotY,  float rotZ);

Entity
 core_create_checkpoint(unsigned char type,  float x,  float y,  float z,  float radius,  float height,  unsigned char r, 
                      unsigned char g,  unsigned char b,  unsigned char a,  unsigned long streamingDistance);

Entity core_create_voice_channel(int spacial,  float maxDistance);

const char * core_get_version();

const char * core_get_branch();

int core_is_debug();

unsigned long core_hash(const char *str);

int core_file_exists(const char *path);

const char * core_read_file(const char *path);

Entity core_get_entity_by_id(unsigned short id);

Entity core_get_base_object_by_id(unsigned char type,  unsigned int id);

Array core_get_entities();

Array core_get_players();

Array core_get_vehicles();

Array core_get_blips();

Array core_get_col_shapes();

Array core_get_checkpoints();

Array core_get_virtual_entities();

Array core_get_virtual_entity_groups();

Array core_get_markers();

Array core_get_peds();

int core_has_meta_data(const char *key);

Array core_get_meta_data(const char *key);

void core_set_meta_data(const char *key,  Array data);

void core_delete_meta_data(const char *key);

int core_has_synced_meta_data(const char *key);

Array core_get_synced_meta_data(const char *key);

Array core_get_required_permissions();

Array core_get_optional_permissions();

void core_destroy_base_object(void *h);

const char * core_get_root_directory();

int core_start_resource(const char *name);

void core_stop_resource(const char *name);

void core_restart_resource(const char *name);

void core_set_synced_meta_data(const char *key,  Array data);

void core_delete_synced_meta_data(const char *key);

Array core_get_players_by_name(const char *name);

unsigned int core_get_net_time();

void core_set_password(const char *password);

const char * core_get_sdk_hash();

Entity core_create_col_shape_cylinder(float posX,  float posY,  float posZ,  float radius,  float height);

Entity core_create_col_shape_cube(float posX1,  float posY1,  float posZ1,  float posX2,  float posY2,  float posZ2);

Entity core_create_col_shape_rectangle(float x1,  float y1,  float x2,  float y2,  float z);

Entity core_create_col_shape_circle(float posX,  float posY,  float posZ,  float radius);

Entity core_create_col_shape_sphere(float posX,  float posY,  float posZ,  float radius);

void core_trigger_local_event(const char *ev,  Array args);

void core_trigger_local_event_raw(const char* ev,  char* bytes,  unsigned long long size);

void core_trigger_client_event(void *p,  const char *ev,  Array args);

void core_trigger_client_event_for(Array clients,  const char *ev,  Array args);

void core_trigger_client_event_for_all(const char *ev,  Array args);

Entity core_create_point_blip_position(float x,  float y,  float z,  unsigned short global);

Entity core_create_point_blip_entity(Entity entity,  unsigned short global);

Entity core_create_area_blip(float x,  float y,  float z,  float width,  float height,  unsigned short global);

Entity core_create_radius_blip(float x,  float y,  float z,  float radius,  unsigned short global);

Entity core_create_col_shape_polygon(float minZ,  float maxZ,  Array points);

Array core_get_all_resources();

const char * core_string_to_sha256(const char *str);

void core_stop_server();

VehicleModelInfo core_get_vehicle_model_by_hash(unsigned int hash);

PedModelInfo core_get_ped_model_by_hash(unsigned int hash);

Array core_get_server_config();

unsigned long long core_hash_server_password(const char *password);

void* core_get_resource_by_name(const char *resourceName);

int col_shape_get_type(void *c);

int col_shape_has_meta_data(void* base,  const char *key);

Array col_shape_get_meta_data(void* base,  const char *key);

void col_shape_set_meta_data(void *base,  const char *key,  Array data);

void col_shape_delete_meta_data(void *base,  const char *key);

void col_shape_destroy(void *b);

int col_shape_is_valid(const char* resourceName,  void *p);

Position col_shape_get_position(void *p);

void col_shape_set_position(void* p,  float x,  float y,  float z);

long col_shape_get_dimension(void* p);

void col_shape_set_dimension(void* p,  long dimension);

int col_shape_get_col_shape_type(void *c);

int col_shape_is_entity_in(void *c,  Entity e);

int col_shape_is_point_in(void *c,  float x,  float y,  float z);

void col_shape_set_players_only(void *c,  int state);

int col_shape_is_players_only(void *c);

unsigned char col_shape_is_entity_id_in(void *c,  unsigned short id);

unsigned char resource_is_started(void *r);

const char * resource_get_type(void *r);

const char * resource_get_name(void* r);

const char * resource_get_main(void *r);

Array resource_get_config(void *r);

Array resource_get_exports(void *r);

Array resource_get_dependencies(void *r);

Array resource_get_dependants(void *r);

Array resource_get_required_permissions(void *r);

Array resource_get_optional_permissions(void *r);

const char * resource_get_path(void *r);

int checkpoint_get_type(void *c);

int checkpoint_has_meta_data(void* base,  const char *key);

Array checkpoint_get_meta_data(void* base,  const char *key);

void checkpoint_set_meta_data(void *base,  const char *key,  Array data);

void checkpoint_delete_meta_data(void *base,  const char *key);

void checkpoint_destroy(void *b);

int checkpoint_is_valid(const char* resourceName,  void *p);

Position checkpoint_get_position(void *p);

void checkpoint_set_position(void* p,  float x,  float y,  float z);

long checkpoint_get_dimension(void* p);

void checkpoint_set_dimension(void* p,  long dimension);

int checkpoint_get_col_shape_type(void *c);

int checkpoint_is_entity_in(void *c,  Entity e);

int checkpoint_is_point_in(void *c,  float x,  float y,  float z);

void checkpoint_set_players_only(void *c,  int state);

int checkpoint_is_players_only(void *c);

unsigned char checkpoint_is_entity_id_in(void *c,  unsigned short id);

unsigned char checkpoint_get_checkpoint_type(void *c);

float checkpoint_get_height(void *c);

float checkpoint_get_radius(void *c);

RGBA checkpoint_get_color(void *c);

Position checkpoint_get_next_position(void *c);

void checkpoint_set_checkpoint_type(void *c,  unsigned char type);

void checkpoint_set_height(void *c,  float height);

void checkpoint_set_radius(void *c,  float radius);

void checkpoint_set_color(void *c,  unsigned char r,  unsigned char g,  unsigned char b,  unsigned char a);

void checkpoint_set_next_position(void *c,  float x,  float y,  float z);

#endif