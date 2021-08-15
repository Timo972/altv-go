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
capi_player_get_current_weapon_components g_call_player_get_current_weapon_components;
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
capi_player_get_social_id g_call_player_get_social_id;
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
capi_player_get_clothes g_call_player_get_clothes;
capi_player_get_dlc_clothes g_call_player_get_dlc_clothes;
capi_player_get_props g_call_player_get_props;
capi_player_get_dlc_props g_call_player_get_dlc_props;
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
capi_core_create_col_shape_cylinder g_call_core_create_col_shape_cylinder;
capi_core_create_col_shape_cube g_call_core_create_col_shape_cube;
capi_core_create_col_shape_rectangle g_call_core_create_col_shape_rectangle;
capi_core_create_col_shape_circle g_call_core_create_col_shape_circle;
capi_core_create_col_shape_sphere g_call_core_create_col_shape_sphere;
capi_core_create_checkpoint g_call_core_create_checkpoint;
capi_core_create_voice_channel g_call_core_create_voice_channel;

capi_vehicle_has_meta_data g_call_vehicle_has_meta_data;
capi_vehicle_get_meta_data g_call_vehicle_get_meta_data;
capi_vehicle_set_meta_data g_call_vehicle_set_meta_data;
capi_vehicle_delete_meta_data g_call_vehicle_delete_meta_data;
capi_vehicle_has_synced_meta_data g_call_vehicle_has_synced_meta_data;
capi_vehicle_get_synced_meta_data g_call_vehicle_get_synced_meta_data;
capi_vehicle_set_synced_meta_data g_call_vehicle_set_synced_meta_data;
capi_vehicle_delete_synced_meta_data g_call_vehicle_delete_synced_meta_data;
capi_vehicle_has_stream_synced_meta_data g_call_vehicle_has_stream_synced_meta_data;
capi_vehicle_get_stream_synced_meta_data g_call_vehicle_get_stream_synced_meta_data;
capi_vehicle_set_stream_synced_meta_data g_call_vehicle_set_stream_synced_meta_data;
capi_vehicle_delete_stream_synced_meta_data g_call_vehicle_delete_stream_synced_meta_data;
capi_vehicle_get_position g_call_vehicle_get_position;
capi_vehicle_set_position g_call_vehicle_set_position;
capi_vehicle_get_rotation g_call_vehicle_get_rotation;
capi_vehicle_set_rotation g_call_vehicle_set_rotation;
capi_vehicle_get_dimension g_call_vehicle_get_dimension;
capi_vehicle_set_dimension g_call_vehicle_set_dimension;
capi_vehicle_get_id g_call_vehicle_get_id;
capi_vehicle_get_model g_call_vehicle_get_model;
capi_vehicle_detach g_call_vehicle_detach;
capi_vehicle_attach_to_entity g_call_vehicle_attach_to_entity;
capi_vehicle_set_visible g_call_vehicle_set_visible;
capi_vehicle_get_visible g_call_vehicle_get_visible;
capi_vehicle_get_network_owner g_call_vehicle_get_network_owner;
capi_vehicle_set_network_owner g_call_vehicle_set_network_owner;
capi_vehicle_get_driver g_call_vehicle_get_driver;
capi_vehicle_is_destroyed g_call_vehicle_is_destroyed;
capi_vehicle_get_mod g_call_vehicle_get_mod;
capi_vehicle_get_mods_count g_call_vehicle_get_mods_count;
capi_vehicle_get_mod_kits_count g_call_vehicle_get_mod_kits_count;
capi_vehicle_get_mod_kit g_call_vehicle_get_mod_kit;
capi_vehicle_is_primary_color_r_g_b g_call_vehicle_is_primary_color_r_g_b;
capi_vehicle_get_primary_color g_call_vehicle_get_primary_color;
capi_vehicle_get_primary_color_r_g_b g_call_vehicle_get_primary_color_r_g_b;
capi_vehicle_is_secondary_color_r_g_b g_call_vehicle_is_secondary_color_r_g_b;
capi_vehicle_get_secondary_color g_call_vehicle_get_secondary_color;
capi_vehicle_get_secondary_color_r_g_b g_call_vehicle_get_secondary_color_r_g_b;
capi_vehicle_get_pearl_color g_call_vehicle_get_pearl_color;
capi_vehicle_get_wheel_color g_call_vehicle_get_wheel_color;
capi_vehicle_get_interior_color g_call_vehicle_get_interior_color;
capi_vehicle_get_dashboard_color g_call_vehicle_get_dashboard_color;
capi_vehicle_is_tire_smoke_color_custom g_call_vehicle_is_tire_smoke_color_custom;
capi_vehicle_get_tire_smoke_color g_call_vehicle_get_tire_smoke_color;
capi_vehicle_get_wheel_type g_call_vehicle_get_wheel_type;
capi_vehicle_get_wheel_variation g_call_vehicle_get_wheel_variation;
capi_vehicle_get_rear_wheel_variation g_call_vehicle_get_rear_wheel_variation;
capi_vehicle_get_custom_tires g_call_vehicle_get_custom_tires;
capi_vehicle_get_special_darkness g_call_vehicle_get_special_darkness;
capi_vehicle_get_numberplate_index g_call_vehicle_get_numberplate_index;
capi_vehicle_get_numberplate_text g_call_vehicle_get_numberplate_text;
capi_vehicle_get_window_tint g_call_vehicle_get_window_tint;
capi_vehicle_get_dirt_level g_call_vehicle_get_dirt_level;
capi_vehicle_is_extra_on g_call_vehicle_is_extra_on;
capi_vehicle_is_neon_active g_call_vehicle_is_neon_active;
capi_vehicle_get_neon_active g_call_vehicle_get_neon_active;
capi_vehicle_get_neon_color g_call_vehicle_get_neon_color;
capi_vehicle_get_livery g_call_vehicle_get_livery;
capi_vehicle_get_roof_livery g_call_vehicle_get_roof_livery;
capi_vehicle_is_engine_on g_call_vehicle_is_engine_on;
capi_vehicle_is_handbrake_active g_call_vehicle_is_handbrake_active;
capi_vehicle_get_headlight_color g_call_vehicle_get_headlight_color;
capi_vehicle_get_radio_station_index g_call_vehicle_get_radio_station_index;
capi_vehicle_is_siren_active g_call_vehicle_is_siren_active;
capi_vehicle_get_lock_state g_call_vehicle_get_lock_state;
capi_vehicle_get_door_state g_call_vehicle_get_door_state;
capi_vehicle_is_window_opened g_call_vehicle_is_window_opened;
capi_vehicle_is_daylight_on g_call_vehicle_is_daylight_on;
capi_vehicle_is_nightlight_on g_call_vehicle_is_nightlight_on;
capi_vehicle_get_roof_state g_call_vehicle_get_roof_state;
capi_vehicle_is_flamethrower_active g_call_vehicle_is_flamethrower_active;
capi_vehicle_get_lights_multiplier g_call_vehicle_get_lights_multiplier;
capi_vehicle_get_engine_health g_call_vehicle_get_engine_health;
capi_vehicle_get_petrol_tank_health g_call_vehicle_get_petrol_tank_health;
capi_vehicle_get_wheels_count g_call_vehicle_get_wheels_count;
capi_vehicle_is_wheel_burst g_call_vehicle_is_wheel_burst;
capi_vehicle_does_wheel_has_tire g_call_vehicle_does_wheel_has_tire;
capi_vehicle_is_wheel_detached g_call_vehicle_is_wheel_detached;
capi_vehicle_is_wheel_on_fire g_call_vehicle_is_wheel_on_fire;
capi_vehicle_get_wheel_health g_call_vehicle_get_wheel_health;
capi_vehicle_get_repairs_count g_call_vehicle_get_repairs_count;
capi_vehicle_get_body_health g_call_vehicle_get_body_health;
capi_vehicle_get_body_additional_health g_call_vehicle_get_body_additional_health;
capi_vehicle_get_part_damage_level g_call_vehicle_get_part_damage_level;
capi_vehicle_get_part_bullet_holes g_call_vehicle_get_part_bullet_holes;
capi_vehicle_is_light_damaged g_call_vehicle_is_light_damaged;
capi_vehicle_is_window_damaged g_call_vehicle_is_window_damaged;
capi_vehicle_is_special_light_damaged g_call_vehicle_is_special_light_damaged;
capi_vehicle_has_armored_windows g_call_vehicle_has_armored_windows;
capi_vehicle_get_armored_window_health g_call_vehicle_get_armored_window_health;
capi_vehicle_get_armored_window_shoot_count g_call_vehicle_get_armored_window_shoot_count;
capi_vehicle_get_bumper_damage_level g_call_vehicle_get_bumper_damage_level;
capi_vehicle_is_manual_engine_control g_call_vehicle_is_manual_engine_control;
capi_vehicle_toggle_extra g_call_vehicle_toggle_extra;
capi_vehicle_set_fixed g_call_vehicle_set_fixed;
capi_vehicle_set_mod g_call_vehicle_set_mod;
capi_vehicle_set_mod_kit g_call_vehicle_set_mod_kit;
capi_vehicle_set_primary_color g_call_vehicle_set_primary_color;
capi_vehicle_set_primary_color_r_g_b g_call_vehicle_set_primary_color_r_g_b;
capi_vehicle_set_secondary_color g_call_vehicle_set_secondary_color;
capi_vehicle_set_secondary_color_r_g_b g_call_vehicle_set_secondary_color_r_g_b;
capi_vehicle_set_pearl_color g_call_vehicle_set_pearl_color;
capi_vehicle_set_wheel_color g_call_vehicle_set_wheel_color;
capi_vehicle_set_interior_color g_call_vehicle_set_interior_color;
capi_vehicle_set_dashboard_color g_call_vehicle_set_dashboard_color;
capi_vehicle_set_tire_smoke_color g_call_vehicle_set_tire_smoke_color;
capi_vehicle_set_wheels g_call_vehicle_set_wheels;
capi_vehicle_set_rear_wheels g_call_vehicle_set_rear_wheels;
capi_vehicle_set_custom_tires g_call_vehicle_set_custom_tires;
capi_vehicle_set_special_darkness g_call_vehicle_set_special_darkness;
capi_vehicle_set_numberplate_index g_call_vehicle_set_numberplate_index;
capi_vehicle_set_numberplate_text g_call_vehicle_set_numberplate_text;
capi_vehicle_set_window_tint g_call_vehicle_set_window_tint;
capi_vehicle_set_dirt_level g_call_vehicle_set_dirt_level;
capi_vehicle_set_neon_active g_call_vehicle_set_neon_active;
capi_vehicle_set_neon_color g_call_vehicle_set_neon_color;
capi_vehicle_set_livery g_call_vehicle_set_livery;
capi_vehicle_set_roof_livery g_call_vehicle_set_roof_livery;
capi_vehicle_set_engine_on g_call_vehicle_set_engine_on;
capi_vehicle_set_headlight_color g_call_vehicle_set_headlight_color;
capi_vehicle_set_radio_station_index g_call_vehicle_set_radio_station_index;
capi_vehicle_set_siren_active g_call_vehicle_set_siren_active;
capi_vehicle_set_lock_state g_call_vehicle_set_lock_state;
capi_vehicle_set_door_state g_call_vehicle_set_door_state;
capi_vehicle_set_window_opened g_call_vehicle_set_window_opened;
capi_vehicle_set_roof_state g_call_vehicle_set_roof_state;
capi_vehicle_set_lights_multiplier g_call_vehicle_set_lights_multiplier;
capi_vehicle_set_engine_health g_call_vehicle_set_engine_health;
capi_vehicle_set_petrol_tank_health g_call_vehicle_set_petrol_tank_health;
capi_vehicle_set_wheel_burst g_call_vehicle_set_wheel_burst;
capi_vehicle_set_wheel_has_tire g_call_vehicle_set_wheel_has_tire;
capi_vehicle_set_wheel_detached g_call_vehicle_set_wheel_detached;
capi_vehicle_set_wheel_on_fire g_call_vehicle_set_wheel_on_fire;
capi_vehicle_set_wheel_health g_call_vehicle_set_wheel_health;
capi_vehicle_set_wheel_fixed g_call_vehicle_set_wheel_fixed;
capi_vehicle_set_body_health g_call_vehicle_set_body_health;
capi_vehicle_set_body_additional_health g_call_vehicle_set_body_additional_health;
capi_vehicle_set_part_damage_level g_call_vehicle_set_part_damage_level;
capi_vehicle_set_part_bullet_holes g_call_vehicle_set_part_bullet_holes;
capi_vehicle_set_light_damaged g_call_vehicle_set_light_damaged;
capi_vehicle_set_window_damaged g_call_vehicle_set_window_damaged;
capi_vehicle_set_special_light_damaged g_call_vehicle_set_special_light_damaged;
capi_vehicle_set_armored_window_health g_call_vehicle_set_armored_window_health;
capi_vehicle_set_armored_window_shoot_count g_call_vehicle_set_armored_window_shoot_count;
capi_vehicle_set_bumper_damage_level g_call_vehicle_set_bumper_damage_level;
capi_vehicle_set_manual_engine_control g_call_vehicle_set_manual_engine_control;
capi_vehicle_get_attached g_call_vehicle_get_attached;
capi_vehicle_get_attached_to g_call_vehicle_get_attached_to;

capi_core_hash g_call_core_hash;
capi_core_file_exists g_call_core_file_exists;
capi_core_read_file g_call_core_read_file;
capi_core_get_entity_by_id g_call_core_get_entity_by_id;
capi_core_has_meta_data g_call_core_has_meta_data;
capi_core_get_meta_data g_call_core_get_meta_data;
capi_core_set_meta_data g_call_core_set_meta_data;
capi_core_delete_meta_data g_call_core_delete_meta_data;
capi_core_has_synced_meta_data g_call_core_has_synced_meta_data;
capi_core_get_synced_meta_data g_call_core_get_synced_meta_data;
capi_core_destroy_base_object g_call_core_destroy_base_object;
capi_core_start_resource g_call_core_start_resource;
capi_core_stop_resource g_call_core_stop_resource;
capi_core_restart_resource g_call_core_restart_resource;
capi_core_set_synced_meta_data g_call_core_set_synced_meta_data;
capi_core_delete_synced_meta_data g_call_core_delete_synced_meta_data;
capi_core_get_players_by_name g_call_core_get_players_by_name;
capi_core_set_password g_call_core_set_password;

// Colshape
capi_col_shape_get_type g_call_col_shape_get_type;
capi_col_shape_has_meta_data g_call_col_shape_has_meta_data;
capi_col_shape_get_meta_data g_call_col_shape_get_meta_data;
capi_col_shape_set_meta_data g_call_col_shape_set_meta_data;
capi_col_shape_delete_meta_data g_call_col_shape_delete_meta_data;
capi_col_shape_get_position g_call_col_shape_get_position;
capi_col_shape_set_position g_call_col_shape_set_position;
capi_col_shape_get_dimension g_call_col_shape_get_dimension;
capi_col_shape_set_dimension g_call_col_shape_set_dimension;
capi_col_shape_get_col_shape_type g_call_col_shape_get_col_shape_type;
capi_col_shape_is_entity_in g_call_col_shape_is_entity_in;
capi_col_shape_is_point_in g_call_col_shape_is_point_in;
capi_col_shape_set_players_only g_call_col_shape_set_players_only;
capi_col_shape_is_players_only g_call_col_shape_is_players_only;

// Checkpoint
capi_checkpoint_get_type g_call_checkpoint_get_type;
capi_checkpoint_has_meta_data g_call_checkpoint_has_meta_data;
capi_checkpoint_get_meta_data g_call_checkpoint_get_meta_data;
capi_checkpoint_set_meta_data g_call_checkpoint_set_meta_data;
capi_checkpoint_delete_meta_data g_call_checkpoint_delete_meta_data;
capi_checkpoint_get_position g_call_checkpoint_get_position;
capi_checkpoint_set_position g_call_checkpoint_set_position;
capi_checkpoint_get_dimension g_call_checkpoint_get_dimension;
capi_checkpoint_set_dimension g_call_checkpoint_set_dimension;
capi_checkpoint_get_col_shape_type g_call_checkpoint_get_col_shape_type;
capi_checkpoint_is_entity_in g_call_checkpoint_is_entity_in;
capi_checkpoint_is_point_in g_call_checkpoint_is_point_in;
capi_checkpoint_set_players_only g_call_checkpoint_set_players_only;
capi_checkpoint_is_players_only g_call_checkpoint_is_players_only;
capi_checkpoint_get_checkpoint_type g_call_checkpoint_get_checkpoint_type;
capi_checkpoint_get_height g_call_checkpoint_get_height;
capi_checkpoint_get_radius g_call_checkpoint_get_radius;
capi_checkpoint_get_color g_call_checkpoint_get_color;
capi_checkpoint_get_next_position g_call_checkpoint_get_next_position;
capi_checkpoint_set_checkpoint_type g_call_checkpoint_set_checkpoint_type;
capi_checkpoint_set_height g_call_checkpoint_set_height;
capi_checkpoint_set_radius g_call_checkpoint_set_radius;
capi_checkpoint_set_color g_call_checkpoint_set_color;
capi_checkpoint_set_next_position g_call_checkpoint_set_next_position;

// VoiceChannel
capi_channel_get_type g_call_channel_get_type;
capi_channel_has_meta_data g_call_channel_has_meta_data;
capi_channel_get_meta_data g_call_channel_get_meta_data;
capi_channel_set_meta_data g_call_channel_set_meta_data;
capi_channel_delete_meta_data g_call_channel_delete_meta_data;
capi_channel_is_spatial g_call_channel_is_spatial;
capi_channel_get_max_distance g_call_channel_get_max_distance;
capi_channel_has_player g_call_channel_has_player;
capi_channel_add_player g_call_channel_add_player;
capi_channel_remove_player g_call_channel_remove_player;
capi_channel_is_player_muted g_call_channel_is_player_muted;
capi_channel_mute_player g_call_channel_mute_player;
capi_channel_unmute_player g_call_channel_unmute_player;

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
    g_call_player_get_current_weapon_components = GET_FUNC(module, "Player_GetCurrentWeaponComponents", capi_player_get_current_weapon_components);
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
    g_call_player_get_clothes = GET_FUNC(module, "Player_GetClothes", capi_player_get_clothes);
    g_call_player_get_dlc_clothes = GET_FUNC(module, "Player_GetDlcClothes", capi_player_get_dlc_clothes);
    g_call_player_get_props = GET_FUNC(module, "Player_GetProps", capi_player_get_props);
    g_call_player_get_dlc_props = GET_FUNC(module, "Player_GetDlcProps", capi_player_get_dlc_props);
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

    // Vehicle
    g_call_vehicle_has_meta_data = GET_FUNC(module, "Vehicle_HasMetaData", capi_vehicle_has_meta_data);
    g_call_vehicle_get_meta_data = GET_FUNC(module, "Vehicle_GetMetaData", capi_vehicle_get_meta_data);
    g_call_vehicle_set_meta_data = GET_FUNC(module, "Vehicle_SetMetaData", capi_vehicle_set_meta_data);
    g_call_vehicle_delete_meta_data = GET_FUNC(module, "Vehicle_DeleteMetaData", capi_vehicle_delete_meta_data);
    g_call_vehicle_has_synced_meta_data = GET_FUNC(module, "Vehicle_HasSyncedMetaData", capi_vehicle_has_synced_meta_data);
    g_call_vehicle_get_synced_meta_data = GET_FUNC(module, "Vehicle_GetSyncedMetaData", capi_vehicle_get_synced_meta_data);
    g_call_vehicle_set_synced_meta_data = GET_FUNC(module, "Vehicle_SetSyncedMetaData", capi_vehicle_set_synced_meta_data);
    g_call_vehicle_delete_synced_meta_data = GET_FUNC(module, "Vehicle_DeleteSyncedMetaData", capi_vehicle_delete_synced_meta_data);
    g_call_vehicle_has_stream_synced_meta_data = GET_FUNC(module, "Vehicle_HasStreamSyncedMetaData", capi_vehicle_has_stream_synced_meta_data);
    g_call_vehicle_get_stream_synced_meta_data = GET_FUNC(module, "Vehicle_GetStreamSyncedMetaData", capi_vehicle_get_stream_synced_meta_data);
    g_call_vehicle_set_stream_synced_meta_data = GET_FUNC(module, "Vehicle_SetStreamSyncedMetaData", capi_vehicle_set_stream_synced_meta_data);
    g_call_vehicle_delete_stream_synced_meta_data = GET_FUNC(module, "Vehicle_DeleteStreamSyncedMetaData", capi_vehicle_delete_stream_synced_meta_data);
    g_call_vehicle_get_position = GET_FUNC(module, "Vehicle_GetPosition", capi_vehicle_get_position);
    g_call_vehicle_set_position = GET_FUNC(module, "Vehicle_SetPosition", capi_vehicle_set_position);
    g_call_vehicle_get_rotation = GET_FUNC(module, "Vehicle_GetRotation", capi_vehicle_get_rotation);
    g_call_vehicle_set_rotation = GET_FUNC(module, "Vehicle_SetRotation", capi_vehicle_set_rotation);
    g_call_vehicle_get_dimension = GET_FUNC(module, "Vehicle_GetDimension", capi_vehicle_get_dimension);
    g_call_vehicle_set_dimension = GET_FUNC(module, "Vehicle_SetDimension", capi_vehicle_set_dimension);
    g_call_vehicle_get_id = GET_FUNC(module, "Vehicle_GetID", capi_vehicle_get_id);
    g_call_vehicle_get_model = GET_FUNC(module, "Vehicle_GetModel", capi_vehicle_get_model);
    g_call_vehicle_detach = GET_FUNC(module, "Vehicle_Detach", capi_vehicle_detach);
    g_call_vehicle_attach_to_entity = GET_FUNC(module, "Vehicle_AttachToEntity", capi_vehicle_attach_to_entity);
    g_call_vehicle_set_visible = GET_FUNC(module, "Vehicle_SetVisible", capi_vehicle_set_visible);
    g_call_vehicle_get_visible = GET_FUNC(module, "Vehicle_GetVisible", capi_vehicle_get_visible);
    g_call_vehicle_get_network_owner = GET_FUNC(module, "Vehicle_GetNetworkOwner", capi_vehicle_get_network_owner);
    g_call_vehicle_set_network_owner = GET_FUNC(module, "Vehicle_SetNetworkOwner", capi_vehicle_set_network_owner);
    g_call_vehicle_get_driver = GET_FUNC(module, "Vehicle_GetDriver", capi_vehicle_get_driver);
    g_call_vehicle_is_destroyed = GET_FUNC(module, "Vehicle_IsDestroyed", capi_vehicle_is_destroyed);
    g_call_vehicle_get_mod = GET_FUNC(module, "Vehicle_GetMod", capi_vehicle_get_mod);
    g_call_vehicle_get_mods_count = GET_FUNC(module, "Vehicle_GetModsCount", capi_vehicle_get_mods_count);
    g_call_vehicle_get_mod_kits_count = GET_FUNC(module, "Vehicle_GetModKitsCount", capi_vehicle_get_mod_kits_count);
    g_call_vehicle_get_mod_kit = GET_FUNC(module, "Vehicle_GetModKit", capi_vehicle_get_mod_kit);
    g_call_vehicle_is_primary_color_r_g_b = GET_FUNC(module, "Vehicle_IsPrimaryColorRGB", capi_vehicle_is_primary_color_r_g_b);
    g_call_vehicle_get_primary_color = GET_FUNC(module, "Vehicle_GetPrimaryColor", capi_vehicle_get_primary_color);
    g_call_vehicle_get_primary_color_r_g_b = GET_FUNC(module, "Vehicle_GetPrimaryColorRGB", capi_vehicle_get_primary_color_r_g_b);
    g_call_vehicle_is_secondary_color_r_g_b = GET_FUNC(module, "Vehicle_IsSecondaryColorRGB", capi_vehicle_is_secondary_color_r_g_b);
    g_call_vehicle_get_secondary_color = GET_FUNC(module, "Vehicle_GetSecondaryColor", capi_vehicle_get_secondary_color);
    g_call_vehicle_get_secondary_color_r_g_b = GET_FUNC(module, "Vehicle_GetSecondaryColorRGB", capi_vehicle_get_secondary_color_r_g_b);
    g_call_vehicle_get_pearl_color = GET_FUNC(module, "Vehicle_GetPearlColor", capi_vehicle_get_pearl_color);
    g_call_vehicle_get_wheel_color = GET_FUNC(module, "Vehicle_GetWheelColor", capi_vehicle_get_wheel_color);
    g_call_vehicle_get_interior_color = GET_FUNC(module, "Vehicle_GetInteriorColor", capi_vehicle_get_interior_color);
    g_call_vehicle_get_dashboard_color = GET_FUNC(module, "Vehicle_GetDashboardColor", capi_vehicle_get_dashboard_color);
    g_call_vehicle_is_tire_smoke_color_custom = GET_FUNC(module, "Vehicle_IsTireSmokeColorCustom", capi_vehicle_is_tire_smoke_color_custom);
    g_call_vehicle_get_tire_smoke_color = GET_FUNC(module, "Vehicle_GetTireSmokeColor", capi_vehicle_get_tire_smoke_color);
    g_call_vehicle_get_wheel_type = GET_FUNC(module, "Vehicle_GetWheelType", capi_vehicle_get_wheel_type);
    g_call_vehicle_get_wheel_variation = GET_FUNC(module, "Vehicle_GetWheelVariation", capi_vehicle_get_wheel_variation);
    g_call_vehicle_get_rear_wheel_variation = GET_FUNC(module, "Vehicle_GetRearWheelVariation", capi_vehicle_get_rear_wheel_variation);
    g_call_vehicle_get_custom_tires = GET_FUNC(module, "Vehicle_GetCustomTires", capi_vehicle_get_custom_tires);
    g_call_vehicle_get_special_darkness = GET_FUNC(module, "Vehicle_GetSpecialDarkness", capi_vehicle_get_special_darkness);
    g_call_vehicle_get_numberplate_index = GET_FUNC(module, "Vehicle_GetNumberplateIndex", capi_vehicle_get_numberplate_index);
    g_call_vehicle_get_numberplate_text = GET_FUNC(module, "Vehicle_GetNumberplateText", capi_vehicle_get_numberplate_text);
    g_call_vehicle_get_window_tint = GET_FUNC(module, "Vehicle_GetWindowTint", capi_vehicle_get_window_tint);
    g_call_vehicle_get_dirt_level = GET_FUNC(module, "Vehicle_GetDirtLevel", capi_vehicle_get_dirt_level);
    g_call_vehicle_is_extra_on = GET_FUNC(module, "Vehicle_IsExtraOn", capi_vehicle_is_extra_on);
    g_call_vehicle_is_neon_active = GET_FUNC(module, "Vehicle_IsNeonActive", capi_vehicle_is_neon_active);
    g_call_vehicle_get_neon_active = GET_FUNC(module, "Vehicle_GetNeonActive", capi_vehicle_get_neon_active);
    g_call_vehicle_get_neon_color = GET_FUNC(module, "Vehicle_GetNeonColor", capi_vehicle_get_neon_color);
    g_call_vehicle_get_livery = GET_FUNC(module, "Vehicle_GetLivery", capi_vehicle_get_livery);
    g_call_vehicle_get_roof_livery = GET_FUNC(module, "Vehicle_GetRoofLivery", capi_vehicle_get_roof_livery);
    g_call_vehicle_is_engine_on = GET_FUNC(module, "Vehicle_IsEngineOn", capi_vehicle_is_engine_on);
    g_call_vehicle_is_handbrake_active = GET_FUNC(module, "Vehicle_IsHandbrakeActive", capi_vehicle_is_handbrake_active);
    g_call_vehicle_get_headlight_color = GET_FUNC(module, "Vehicle_GetHeadlightColor", capi_vehicle_get_headlight_color);
    g_call_vehicle_get_radio_station_index = GET_FUNC(module, "Vehicle_GetRadioStationIndex", capi_vehicle_get_radio_station_index);
    g_call_vehicle_is_siren_active = GET_FUNC(module, "Vehicle_IsSirenActive", capi_vehicle_is_siren_active);
    g_call_vehicle_get_lock_state = GET_FUNC(module, "Vehicle_GetLockState", capi_vehicle_get_lock_state);
    g_call_vehicle_get_door_state = GET_FUNC(module, "Vehicle_GetDoorState", capi_vehicle_get_door_state);
    g_call_vehicle_is_window_opened = GET_FUNC(module, "Vehicle_IsWindowOpened", capi_vehicle_is_window_opened);
    g_call_vehicle_is_daylight_on = GET_FUNC(module, "Vehicle_IsDaylightOn", capi_vehicle_is_daylight_on);
    g_call_vehicle_is_nightlight_on = GET_FUNC(module, "Vehicle_IsNightlightOn", capi_vehicle_is_nightlight_on);
    g_call_vehicle_get_roof_state = GET_FUNC(module, "Vehicle_GetRoofState", capi_vehicle_get_roof_state);
    g_call_vehicle_is_flamethrower_active = GET_FUNC(module, "Vehicle_IsFlamethrowerActive", capi_vehicle_is_flamethrower_active);
    g_call_vehicle_get_lights_multiplier = GET_FUNC(module, "Vehicle_GetLightsMultiplier", capi_vehicle_get_lights_multiplier);
    g_call_vehicle_get_engine_health = GET_FUNC(module, "Vehicle_GetEngineHealth", capi_vehicle_get_engine_health);
    g_call_vehicle_get_petrol_tank_health = GET_FUNC(module, "Vehicle_GetPetrolTankHealth", capi_vehicle_get_petrol_tank_health);
    g_call_vehicle_get_wheels_count = GET_FUNC(module, "Vehicle_GetWheelsCount", capi_vehicle_get_wheels_count);
    g_call_vehicle_is_wheel_burst = GET_FUNC(module, "Vehicle_IsWheelBurst", capi_vehicle_is_wheel_burst);
    g_call_vehicle_does_wheel_has_tire = GET_FUNC(module, "Vehicle_DoesWheelHasTire", capi_vehicle_does_wheel_has_tire);
    g_call_vehicle_is_wheel_detached = GET_FUNC(module, "Vehicle_IsWheelDetached", capi_vehicle_is_wheel_detached);
    g_call_vehicle_is_wheel_on_fire = GET_FUNC(module, "Vehicle_IsWheelOnFire", capi_vehicle_is_wheel_on_fire);
    g_call_vehicle_get_wheel_health = GET_FUNC(module, "Vehicle_GetWheelHealth", capi_vehicle_get_wheel_health);
    g_call_vehicle_get_repairs_count = GET_FUNC(module, "Vehicle_GetRepairsCount", capi_vehicle_get_repairs_count);
    g_call_vehicle_get_body_health = GET_FUNC(module, "Vehicle_GetBodyHealth", capi_vehicle_get_body_health);
    g_call_vehicle_get_body_additional_health = GET_FUNC(module, "Vehicle_GetBodyAdditionalHealth", capi_vehicle_get_body_additional_health);
    g_call_vehicle_get_part_damage_level = GET_FUNC(module, "Vehicle_GetPartDamageLevel", capi_vehicle_get_part_damage_level);
    g_call_vehicle_get_part_bullet_holes = GET_FUNC(module, "Vehicle_GetPartBulletHoles", capi_vehicle_get_part_bullet_holes);
    g_call_vehicle_is_light_damaged = GET_FUNC(module, "Vehicle_IsLightDamaged", capi_vehicle_is_light_damaged);
    g_call_vehicle_is_window_damaged = GET_FUNC(module, "Vehicle_IsWindowDamaged", capi_vehicle_is_window_damaged);
    g_call_vehicle_is_special_light_damaged = GET_FUNC(module, "Vehicle_IsSpecialLightDamaged", capi_vehicle_is_special_light_damaged);
    g_call_vehicle_has_armored_windows = GET_FUNC(module, "Vehicle_HasArmoredWindows", capi_vehicle_has_armored_windows);
    g_call_vehicle_get_armored_window_health = GET_FUNC(module, "Vehicle_GetArmoredWindowHealth", capi_vehicle_get_armored_window_health);
    g_call_vehicle_get_armored_window_shoot_count = GET_FUNC(module, "Vehicle_GetArmoredWindowShootCount", capi_vehicle_get_armored_window_shoot_count);
    g_call_vehicle_get_bumper_damage_level = GET_FUNC(module, "Vehicle_GetBumperDamageLevel", capi_vehicle_get_bumper_damage_level);
    g_call_vehicle_is_manual_engine_control = GET_FUNC(module, "Vehicle_IsManualEngineControl", capi_vehicle_is_manual_engine_control);
    g_call_vehicle_toggle_extra = GET_FUNC(module, "Vehicle_ToggleExtra", capi_vehicle_toggle_extra);
    g_call_vehicle_set_fixed = GET_FUNC(module, "Vehicle_SetFixed", capi_vehicle_set_fixed);
    g_call_vehicle_set_mod = GET_FUNC(module, "Vehicle_SetMod", capi_vehicle_set_mod);
    g_call_vehicle_set_mod_kit = GET_FUNC(module, "Vehicle_SetModKit", capi_vehicle_set_mod_kit);
    g_call_vehicle_set_primary_color = GET_FUNC(module, "Vehicle_SetPrimaryColor", capi_vehicle_set_primary_color);
    g_call_vehicle_set_primary_color_r_g_b = GET_FUNC(module, "Vehicle_SetPrimaryColorRGB", capi_vehicle_set_primary_color_r_g_b);
    g_call_vehicle_set_secondary_color = GET_FUNC(module, "Vehicle_SetSecondaryColor", capi_vehicle_set_secondary_color);
    g_call_vehicle_set_secondary_color_r_g_b = GET_FUNC(module, "Vehicle_SetSecondaryColorRGB", capi_vehicle_set_secondary_color_r_g_b);
    g_call_vehicle_set_pearl_color = GET_FUNC(module, "Vehicle_SetPearlColor", capi_vehicle_set_pearl_color);
    g_call_vehicle_set_wheel_color = GET_FUNC(module, "Vehicle_SetWheelColor", capi_vehicle_set_wheel_color);
    g_call_vehicle_set_interior_color = GET_FUNC(module, "Vehicle_SetInteriorColor", capi_vehicle_set_interior_color);
    g_call_vehicle_set_dashboard_color = GET_FUNC(module, "Vehicle_SetDashboardColor", capi_vehicle_set_dashboard_color);
    g_call_vehicle_set_tire_smoke_color = GET_FUNC(module, "Vehicle_SetTireSmokeColor", capi_vehicle_set_tire_smoke_color);
    g_call_vehicle_set_wheels = GET_FUNC(module, "Vehicle_SetWheels", capi_vehicle_set_wheels);
    g_call_vehicle_set_rear_wheels = GET_FUNC(module, "Vehicle_SetRearWheels", capi_vehicle_set_rear_wheels);
    g_call_vehicle_set_custom_tires = GET_FUNC(module, "Vehicle_SetCustomTires", capi_vehicle_set_custom_tires);
    g_call_vehicle_set_special_darkness = GET_FUNC(module, "Vehicle_SetSpecialDarkness", capi_vehicle_set_special_darkness);
    g_call_vehicle_set_numberplate_index = GET_FUNC(module, "Vehicle_SetNumberplateIndex", capi_vehicle_set_numberplate_index);
    g_call_vehicle_set_numberplate_text = GET_FUNC(module, "Vehicle_SetNumberplateText", capi_vehicle_set_numberplate_text);
    g_call_vehicle_set_window_tint = GET_FUNC(module, "Vehicle_SetWindowTint", capi_vehicle_set_window_tint);
    g_call_vehicle_set_dirt_level = GET_FUNC(module, "Vehicle_SetDirtLevel", capi_vehicle_set_dirt_level);
    g_call_vehicle_set_neon_active = GET_FUNC(module, "Vehicle_SetNeonActive", capi_vehicle_set_neon_active);
    g_call_vehicle_set_neon_color = GET_FUNC(module, "Vehicle_SetNeonColor", capi_vehicle_set_neon_color);
    g_call_vehicle_set_livery = GET_FUNC(module, "Vehicle_SetLivery", capi_vehicle_set_livery);
    g_call_vehicle_set_roof_livery = GET_FUNC(module, "Vehicle_SetRoofLivery", capi_vehicle_set_roof_livery);
    g_call_vehicle_set_engine_on = GET_FUNC(module, "Vehicle_SetEngineOn", capi_vehicle_set_engine_on);
    g_call_vehicle_set_headlight_color = GET_FUNC(module, "Vehicle_SetHeadlightColor", capi_vehicle_set_headlight_color);
    g_call_vehicle_set_radio_station_index = GET_FUNC(module, "Vehicle_SetRadioStationIndex", capi_vehicle_set_radio_station_index);
    g_call_vehicle_set_siren_active = GET_FUNC(module, "Vehicle_SetSirenActive", capi_vehicle_set_siren_active);
    g_call_vehicle_set_lock_state = GET_FUNC(module, "Vehicle_SetLockState", capi_vehicle_set_lock_state);
    g_call_vehicle_set_door_state = GET_FUNC(module, "Vehicle_SetDoorState", capi_vehicle_set_door_state);
    g_call_vehicle_set_window_opened = GET_FUNC(module, "Vehicle_SetWindowOpened", capi_vehicle_set_window_opened);
    g_call_vehicle_set_roof_state = GET_FUNC(module, "Vehicle_SetRoofState", capi_vehicle_set_roof_state);
    g_call_vehicle_set_lights_multiplier = GET_FUNC(module, "Vehicle_SetLightsMultiplier", capi_vehicle_set_lights_multiplier);
    g_call_vehicle_set_engine_health = GET_FUNC(module, "Vehicle_SetEngineHealth", capi_vehicle_set_engine_health);
    g_call_vehicle_set_petrol_tank_health = GET_FUNC(module, "Vehicle_SetPetrolTankHealth", capi_vehicle_set_petrol_tank_health);
    g_call_vehicle_set_wheel_burst = GET_FUNC(module, "Vehicle_SetWheelBurst", capi_vehicle_set_wheel_burst);
    g_call_vehicle_set_wheel_has_tire = GET_FUNC(module, "Vehicle_SetWheelHasTire", capi_vehicle_set_wheel_has_tire);
    g_call_vehicle_set_wheel_detached = GET_FUNC(module, "Vehicle_SetWheelDetached", capi_vehicle_set_wheel_detached);
    g_call_vehicle_set_wheel_on_fire = GET_FUNC(module, "Vehicle_SetWheelOnFire", capi_vehicle_set_wheel_on_fire);
    g_call_vehicle_set_wheel_health = GET_FUNC(module, "Vehicle_SetWheelHealth", capi_vehicle_set_wheel_health);
    g_call_vehicle_set_wheel_fixed = GET_FUNC(module, "Vehicle_SetWheelFixed", capi_vehicle_set_wheel_fixed);
    g_call_vehicle_set_body_health = GET_FUNC(module, "Vehicle_SetBodyHealth", capi_vehicle_set_body_health);
    g_call_vehicle_set_body_additional_health = GET_FUNC(module, "Vehicle_SetBodyAdditionalHealth", capi_vehicle_set_body_additional_health);
    g_call_vehicle_set_part_damage_level = GET_FUNC(module, "Vehicle_SetPartDamageLevel", capi_vehicle_set_part_damage_level);
    g_call_vehicle_set_part_bullet_holes = GET_FUNC(module, "Vehicle_SetPartBulletHoles", capi_vehicle_set_part_bullet_holes);
    g_call_vehicle_set_light_damaged = GET_FUNC(module, "Vehicle_SetLightDamaged", capi_vehicle_set_light_damaged);
    g_call_vehicle_set_window_damaged = GET_FUNC(module, "Vehicle_SetWindowDamaged", capi_vehicle_set_window_damaged);
    g_call_vehicle_set_special_light_damaged = GET_FUNC(module, "Vehicle_SetSpecialLightDamaged", capi_vehicle_set_special_light_damaged);
    g_call_vehicle_set_armored_window_health = GET_FUNC(module, "Vehicle_SetArmoredWindowHealth", capi_vehicle_set_armored_window_health);
    g_call_vehicle_set_armored_window_shoot_count = GET_FUNC(module, "Vehicle_SetArmoredWindowShootCount", capi_vehicle_set_armored_window_shoot_count);
    g_call_vehicle_set_bumper_damage_level = GET_FUNC(module, "Vehicle_SetBumperDamageLevel", capi_vehicle_set_bumper_damage_level);
    g_call_vehicle_set_manual_engine_control = GET_FUNC(module, "Vehicle_SetManualEngineControl", capi_vehicle_set_manual_engine_control);
    g_call_vehicle_get_attached = GET_FUNC(module, "Vehicle_GetAttached", capi_vehicle_get_attached);
    g_call_vehicle_get_attached_to = GET_FUNC(module, "Vehicle_GetAttachedTo", capi_vehicle_get_attached_to);

    // Core
    g_call_core_hash = GET_FUNC(module, "Core_Hash", capi_core_hash);
    g_call_core_file_exists = GET_FUNC(module, "Core_FileExists", capi_core_file_exists);
    g_call_core_read_file = GET_FUNC(module, "Core_ReadFile", capi_core_read_file);
    g_call_core_get_entity_by_id = GET_FUNC(module, "Core_GetEntityByID", capi_core_get_entity_by_id);
    g_call_core_has_meta_data = GET_FUNC(module, "Core_HasMetaData", capi_core_has_meta_data);
    g_call_core_get_meta_data = GET_FUNC(module, "Core_GetMetaData", capi_core_get_meta_data);
    g_call_core_set_meta_data = GET_FUNC(module, "Core_SetMetaData", capi_core_set_meta_data);
    g_call_core_delete_meta_data = GET_FUNC(module, "Core_DeleteMetaData", capi_core_delete_meta_data);
    g_call_core_has_synced_meta_data = GET_FUNC(module, "Core_HasSyncedMetaData", capi_core_has_synced_meta_data);
    g_call_core_get_synced_meta_data = GET_FUNC(module, "Core_GetSyncedMetaData", capi_core_get_synced_meta_data);
    g_call_core_destroy_base_object = GET_FUNC(module, "Core_DestroyBaseObject", capi_core_destroy_base_object);
    g_call_core_start_resource = GET_FUNC(module, "Core_StartResource", capi_core_start_resource);
    g_call_core_stop_resource = GET_FUNC(module, "Core_StopResource", capi_core_stop_resource);
    g_call_core_restart_resource = GET_FUNC(module, "Core_RestartResource", capi_core_restart_resource);
    g_call_core_set_synced_meta_data = GET_FUNC(module, "Core_SetSyncedMetaData", capi_core_set_synced_meta_data);
    g_call_core_delete_synced_meta_data = GET_FUNC(module, "Core_DeleteSyncedMetaData", capi_core_delete_synced_meta_data);
    g_call_core_get_players_by_name = GET_FUNC(module, "Core_GetPlayersByName", capi_core_get_players_by_name);
    g_call_core_set_password = GET_FUNC(module, "Core_SetPassword", capi_core_set_password);

    // ColShape
    g_call_col_shape_get_type = GET_FUNC(module, "ColShape_GetType", capi_col_shape_get_type);
    g_call_col_shape_has_meta_data = GET_FUNC(module, "ColShape_HasMetaData", capi_col_shape_has_meta_data);
    g_call_col_shape_get_meta_data = GET_FUNC(module, "ColShape_GetMetaData", capi_col_shape_get_meta_data);
    g_call_col_shape_set_meta_data = GET_FUNC(module, "ColShape_SetMetaData", capi_col_shape_set_meta_data);
    g_call_col_shape_delete_meta_data = GET_FUNC(module, "ColShape_DeleteMetaData", capi_col_shape_delete_meta_data);
    g_call_col_shape_get_position = GET_FUNC(module, "ColShape_GetPosition", capi_col_shape_get_position);
    g_call_col_shape_set_position = GET_FUNC(module, "ColShape_SetPosition", capi_col_shape_set_position);
    g_call_col_shape_get_dimension = GET_FUNC(module, "ColShape_GetDimension", capi_col_shape_get_dimension);
    g_call_col_shape_set_dimension = GET_FUNC(module, "ColShape_SetDimension", capi_col_shape_set_dimension);
    g_call_col_shape_get_col_shape_type = GET_FUNC(module, "ColShape_GetColShapeType", capi_col_shape_get_col_shape_type);
    g_call_col_shape_is_entity_in = GET_FUNC(module, "ColShape_IsEntityIn", capi_col_shape_is_entity_in);
    g_call_col_shape_is_point_in = GET_FUNC(module, "ColShape_IsPointIn", capi_col_shape_is_point_in);
    g_call_col_shape_set_players_only = GET_FUNC(module, "ColShape_SetPlayersOnly", capi_col_shape_set_players_only);
    g_call_col_shape_is_players_only = GET_FUNC(module, "ColShape_IsPlayersOnly", capi_col_shape_is_players_only);

    g_call_core_create_col_shape_cylinder = GET_FUNC(module, "Core_CreateColShapeCylinder", capi_core_create_col_shape_cylinder);
    g_call_core_create_col_shape_cube = GET_FUNC(module, "Core_CreateColShapeCube", capi_core_create_col_shape_cube);
    g_call_core_create_col_shape_rectangle = GET_FUNC(module, "Core_CreateColShapeRectangle", capi_core_create_col_shape_rectangle);
    g_call_core_create_col_shape_circle = GET_FUNC(module, "Core_CreateColShapeCircle", capi_core_create_col_shape_circle);
    g_call_core_create_col_shape_sphere = GET_FUNC(module, "Core_CreateColShapeSphere", capi_core_create_col_shape_sphere);
    g_call_core_create_checkpoint = GET_FUNC(module, "Core_CreateCheckpoint", capi_core_create_checkpoint);
    g_call_core_create_voice_channel = GET_FUNC(module, "Core_CreateVoiceChannel", capi_core_create_voice_channel);

    // Checkpoint
    g_call_checkpoint_get_type = GET_FUNC(module, "Checkpoint_GetType", capi_checkpoint_get_type);
    g_call_checkpoint_has_meta_data = GET_FUNC(module, "Checkpoint_HasMetaData", capi_checkpoint_has_meta_data);
    g_call_checkpoint_get_meta_data = GET_FUNC(module, "Checkpoint_GetMetaData", capi_checkpoint_get_meta_data);
    g_call_checkpoint_set_meta_data = GET_FUNC(module, "Checkpoint_SetMetaData", capi_checkpoint_set_meta_data);
    g_call_checkpoint_delete_meta_data = GET_FUNC(module, "Checkpoint_DeleteMetaData", capi_checkpoint_delete_meta_data);
    g_call_checkpoint_get_position = GET_FUNC(module, "Checkpoint_GetPosition", capi_checkpoint_get_position);
    g_call_checkpoint_set_position = GET_FUNC(module, "Checkpoint_SetPosition", capi_checkpoint_set_position);
    g_call_checkpoint_get_dimension = GET_FUNC(module, "Checkpoint_GetDimension", capi_checkpoint_get_dimension);
    g_call_checkpoint_set_dimension = GET_FUNC(module, "Checkpoint_SetDimension", capi_checkpoint_set_dimension);
    g_call_checkpoint_get_col_shape_type = GET_FUNC(module, "Checkpoint_GetColShapeType", capi_checkpoint_get_col_shape_type);
    g_call_checkpoint_is_entity_in = GET_FUNC(module, "Checkpoint_IsEntityIn", capi_checkpoint_is_entity_in);
    g_call_checkpoint_is_point_in = GET_FUNC(module, "Checkpoint_IsPointIn", capi_checkpoint_is_point_in);
    g_call_checkpoint_set_players_only = GET_FUNC(module, "Checkpoint_SetPlayersOnly", capi_checkpoint_set_players_only);
    g_call_checkpoint_is_players_only = GET_FUNC(module, "Checkpoint_IsPlayersOnly", capi_checkpoint_is_players_only);
    g_call_checkpoint_get_checkpoint_type = GET_FUNC(module, "Checkpoint_GetCheckpointType", capi_checkpoint_get_checkpoint_type);
    g_call_checkpoint_get_height = GET_FUNC(module, "Checkpoint_GetHeight", capi_checkpoint_get_height);
    g_call_checkpoint_get_radius = GET_FUNC(module, "Checkpoint_GetRadius", capi_checkpoint_get_radius);
    g_call_checkpoint_get_color = GET_FUNC(module, "Checkpoint_GetColor", capi_checkpoint_get_color);
    g_call_checkpoint_get_next_position = GET_FUNC(module, "Checkpoint_GetNextPosition", capi_checkpoint_get_next_position);
    g_call_checkpoint_set_checkpoint_type = GET_FUNC(module, "Checkpoint_SetCheckpointType", capi_checkpoint_set_checkpoint_type);
    g_call_checkpoint_set_height = GET_FUNC(module, "Checkpoint_SetHeight", capi_checkpoint_set_height);
    g_call_checkpoint_set_radius = GET_FUNC(module, "Checkpoint_SetRadius", capi_checkpoint_set_radius);
    g_call_checkpoint_set_color = GET_FUNC(module, "Checkpoint_SetColor", capi_checkpoint_set_color);
    g_call_checkpoint_set_next_position = GET_FUNC(module, "Checkpoint_SetNextPosition", capi_checkpoint_set_next_position);

    // VoiceChannel
    g_call_channel_get_type = GET_FUNC(module, "Channel_GetType", capi_channel_get_type);
    g_call_channel_has_meta_data = GET_FUNC(module, "Channel_HasMetaData", capi_channel_has_meta_data);
    g_call_channel_get_meta_data = GET_FUNC(module, "Channel_GetMetaData", capi_channel_get_meta_data);
    g_call_channel_set_meta_data = GET_FUNC(module, "Channel_SetMetaData", capi_channel_set_meta_data);
    g_call_channel_delete_meta_data = GET_FUNC(module, "Channel_DeleteMetaData", capi_channel_delete_meta_data);
    g_call_channel_is_spatial = GET_FUNC(module, "Channel_IsSpatial", capi_channel_is_spatial);
    g_call_channel_get_max_distance = GET_FUNC(module, "Channel_GetMaxDistance", capi_channel_get_max_distance);
    g_call_channel_has_player = GET_FUNC(module, "Channel_HasPlayer", capi_channel_has_player);
    g_call_channel_add_player = GET_FUNC(module, "Channel_AddPlayer", capi_channel_add_player);
    g_call_channel_remove_player = GET_FUNC(module, "Channel_RemovePlayer", capi_channel_remove_player);
    g_call_channel_is_player_muted = GET_FUNC(module, "Channel_IsPlayerMuted", capi_channel_is_player_muted);
    g_call_channel_mute_player = GET_FUNC(module, "Channel_MutePlayer", capi_channel_mute_player);
    g_call_channel_unmute_player = GET_FUNC(module, "Channel_UnmutePlayer", capi_channel_unmute_player);

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

Entity core_get_entity_by_id(unsigned short id)
{
    return g_call_core_get_entity_by_id(id);
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

int core_has_synced_meta_data(const char *key)
{
    return g_call_core_has_synced_meta_data(key);
}

MetaData core_get_synced_meta_data(const char *key)
{
    return g_call_core_get_synced_meta_data(key);
}

void core_destroy_base_object(void *h)
{
    return g_call_core_destroy_base_object(h);
}

int core_start_resource(const char *name)
{
    return g_call_core_start_resource(name);
}

void core_stop_resource(const char *name)
{
    return g_call_core_stop_resource(name);
}

int core_restart_resource(const char *name)
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

void *core_create_col_shape_cylinder(float posX, float posY, float posZ, float radius, float height)
{
    g_call_core_create_col_shape_cylinder(posX, posY, posZ, radius, height);
}

void *core_create_col_shape_cube(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2)
{
    g_call_core_create_col_shape_cube(posX1, posY1, posZ1, posX2, posY2, posZ2);
}

void *core_create_col_shape_rectangle(float x1, float y1, float x2, float y2, float z)
{
    g_call_core_create_col_shape_rectangle(x1, y1, x2, y2, z);
}

void *core_create_col_shape_circle(float posX, float posY, float posZ, float radius)
{
    g_call_core_create_col_shape_circle(posX, posY, posZ, radius);
}

void *core_create_col_shape_sphere(float posX, float posY, float posZ, float radius)
{
    g_call_core_create_col_shape_sphere(posX, posY, posZ, radius);
}

void *core_create_checkpoint(unsigned char type, float x, float y, float z, float radius, float height, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    g_call_core_create_checkpoint(type, x, y, z, radius, height, r, g, b, a);
}

void *core_create_voice_channel(int spatial, float maxDistance)
{
    g_call_core_create_voice_channel(spatial, maxDistance);
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

int player_has_weapon_component(void *p, unsigned long weapon, unsigned long component)
{
    return g_call_player_has_weapon_component(p, weapon, component);
}

Array player_get_current_weapon_components(void *p)
{
    return g_call_player_get_current_weapon_components(p);
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

int player_is_dead(void *p)
{
    return g_call_player_is_dead(p);
}

int player_is_jumping(void *p)
{
    return g_call_player_is_jumping(p);
}

int player_is_in_ragdoll(void *p)
{
    return g_call_player_is_in_ragdoll(p);
}

int player_is_aiming(void *p)
{
    return g_call_player_is_aiming(p);
}

int player_is_shooting(void *p)
{
    return g_call_player_is_shooting(p);
}

int player_is_reloading(void *p)
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

int player_is_in_vehicle(void *p)
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

int player_is_flashlight_active(void *p)
{
    return g_call_player_is_flashlight_active(p);
}

int player_is_connected(void *p)
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

void player_give_weapon(void *p, unsigned long weapon, long ammo, int selectWeapon)
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

Cloth player_get_clothes(void *p, unsigned int component)
{
    return g_call_player_get_clothes(p, component);
}

DlcCloth player_get_dlc_clothes(void *p, unsigned int component)
{
    return g_call_player_get_dlc_clothes(p, component);
}

Prop player_get_props(void *p, unsigned int component)
{
    return g_call_player_get_props(p, component);
}

DlcProp player_get_dlc_props(void *p, unsigned int component)
{
    return g_call_player_get_dlc_props(p, component);
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

int player_is_entity_in_streaming_range(void *p, void *entity)
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

void player_attach_to_entity(void *p, void *e, int otherBoneIndex, int myBoneIndex, Position position, Rotation rotation, int collision, int noFixedRotation)
{
    return g_call_player_attach_to_entity(p, e, otherBoneIndex, myBoneIndex, position, rotation, collision, noFixedRotation);
}

void player_set_visible(void *p, int toggle)
{
    return g_call_player_set_visible(p, toggle);
}

int player_get_visible(void *p)
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

void player_set_network_owner(void *p, void *owner, int disableMigration)
{
    return g_call_player_set_network_owner(p, owner, disableMigration);
}

// Vehicle
int vehicle_has_meta_data(void* base, const char *key)
{
    return g_call_vehicle_has_meta_data(base, key);
}

MetaData vehicle_get_meta_data(void* base, const char *key)
{
    return g_call_vehicle_get_meta_data(base, key);
}

void vehicle_set_meta_data(void *base, const char *key, void *val)
{
    return g_call_vehicle_set_meta_data(base, key, val);
}

void vehicle_delete_meta_data(void *base, const char *key)
{
    return g_call_vehicle_delete_meta_data(base, key);
}

int vehicle_has_synced_meta_data(void* base, const char *key)
{
    return g_call_vehicle_has_synced_meta_data(base, key);
}

MetaData vehicle_get_synced_meta_data(void* base, const char *key)
{
    return g_call_vehicle_get_synced_meta_data(base, key);
}

void vehicle_set_synced_meta_data(void *base, const char *key, void *val)
{
    return g_call_vehicle_set_synced_meta_data(base, key, val);
}

void vehicle_delete_synced_meta_data(void *base, const char *key)
{
    return g_call_vehicle_delete_synced_meta_data(base, key);
}

int vehicle_has_stream_synced_meta_data(void* base, const char *key)
{
    return g_call_vehicle_has_stream_synced_meta_data(base, key);
}

MetaData vehicle_get_stream_synced_meta_data(void* base, const char *key)
{
    return g_call_vehicle_get_stream_synced_meta_data(base, key);
}

void vehicle_set_stream_synced_meta_data(void *base, const char *key, void *val)
{
    return g_call_vehicle_set_stream_synced_meta_data(base, key, val);
}

void vehicle_delete_stream_synced_meta_data(void *base, const char *key)
{
    return g_call_vehicle_delete_stream_synced_meta_data(base, key);
}

Position vehicle_get_position(void *v)
{
    return g_call_vehicle_get_position(v);
}

void vehicle_set_position(void *v, float x, float y, float z)
{
    return g_call_vehicle_set_position(v, x, y, z);
}

Rotation vehicle_get_rotation(void *v)
{
    return g_call_vehicle_get_rotation(v);
}

void vehicle_set_rotation(void *v, float roll, float pitch, float yaw)
{
    return g_call_vehicle_set_rotation(v, roll, pitch, yaw);
}

long vehicle_get_dimension(void *v)
{
    return g_call_vehicle_get_dimension(v);
}

void vehicle_set_dimension(void *v, long dimension)
{
    return g_call_vehicle_set_dimension(v, dimension);
}

unsigned long vehicle_get_id(void *v)
{
    return g_call_vehicle_get_id(v);
}

unsigned long vehicle_get_model(void *v)
{
    return g_call_vehicle_get_model(v);
}

void vehicle_detach(void *v)
{
    return g_call_vehicle_detach(v);
}

void vehicle_attach_to_entity(void *v, void *e, int otherBoneIndex, int myBoneIndex, Position position, Rotation rotation, int collision, int noFixedRotation)
{
    return g_call_vehicle_attach_to_entity(v, e, otherBoneIndex, myBoneIndex, position, rotation, collision, noFixedRotation);
}

void vehicle_set_visible(void *v, int toggle)
{
    return g_call_vehicle_set_visible(v, toggle);
}

int vehicle_get_visible(void *v)
{
    return g_call_vehicle_get_visible(v);
}

void * vehicle_get_network_owner(void *v)
{
    return g_call_vehicle_get_network_owner(v);
}

void vehicle_set_network_owner(void *v, void *owner, int disableMigration)
{
    return g_call_vehicle_set_network_owner(v, owner, disableMigration);
}

void * vehicle_get_driver(void *v)
{
    return g_call_vehicle_get_driver(v);
}

int vehicle_is_destroyed(void *v)
{
    return g_call_vehicle_is_destroyed(v);
}

unsigned long vehicle_get_mod(void *v, unsigned int category)
{
    return g_call_vehicle_get_mod(v, category);
}

unsigned long vehicle_get_mods_count(void *v, unsigned int category)
{
    return g_call_vehicle_get_mods_count(v, category);
}

unsigned long vehicle_get_mod_kits_count(void *v)
{
    return g_call_vehicle_get_mod_kits_count(v);
}

unsigned long vehicle_get_mod_kit(void *v)
{
    return g_call_vehicle_get_mod_kit(v);
}

int vehicle_is_primary_color_r_g_b(void *v)
{
    return g_call_vehicle_is_primary_color_r_g_b(v);
}

unsigned long vehicle_get_primary_color(void *v)
{
    return g_call_vehicle_get_primary_color(v);
}

RGBA vehicle_get_primary_color_r_g_b(void *v)
{
    return g_call_vehicle_get_primary_color_r_g_b(v);
}

int vehicle_is_secondary_color_r_g_b(void *v)
{
    return g_call_vehicle_is_secondary_color_r_g_b(v);
}

unsigned long vehicle_get_secondary_color(void *v)
{
    return g_call_vehicle_get_secondary_color(v);
}

RGBA vehicle_get_secondary_color_r_g_b(void *v)
{
    return g_call_vehicle_get_secondary_color_r_g_b(v);
}

unsigned long vehicle_get_pearl_color(void *v)
{
    return g_call_vehicle_get_pearl_color(v);
}

unsigned long vehicle_get_wheel_color(void *v)
{
    return g_call_vehicle_get_wheel_color(v);
}

unsigned long vehicle_get_interior_color(void *v)
{
    return g_call_vehicle_get_interior_color(v);
}

unsigned long vehicle_get_dashboard_color(void *v)
{
    return g_call_vehicle_get_dashboard_color(v);
}

int vehicle_is_tire_smoke_color_custom(void *v)
{
    return g_call_vehicle_is_tire_smoke_color_custom(v);
}

RGBA vehicle_get_tire_smoke_color(void *v)
{
    return g_call_vehicle_get_tire_smoke_color(v);
}

unsigned long vehicle_get_wheel_type(void *v)
{
    return g_call_vehicle_get_wheel_type(v);
}

unsigned long vehicle_get_wheel_variation(void *v)
{
    return g_call_vehicle_get_wheel_variation(v);
}

unsigned long vehicle_get_rear_wheel_variation(void *v)
{
    return g_call_vehicle_get_rear_wheel_variation(v);
}

int vehicle_get_custom_tires(void *v)
{
    return g_call_vehicle_get_custom_tires(v);
}

unsigned long vehicle_get_special_darkness(void *v)
{
    return g_call_vehicle_get_special_darkness(v);
}

unsigned long vehicle_get_numberplate_index(void *v)
{
    return g_call_vehicle_get_numberplate_index(v);
}

const char* vehicle_get_numberplate_text(void *v)
{
    return g_call_vehicle_get_numberplate_text(v);
}

unsigned long vehicle_get_window_tint(void *v)
{
    return g_call_vehicle_get_window_tint(v);
}

unsigned long vehicle_get_dirt_level(void *v)
{
    return g_call_vehicle_get_dirt_level(v);
}

int vehicle_is_extra_on(void *v, unsigned int extraID)
{
    return g_call_vehicle_is_extra_on(v, extraID);
}

int vehicle_is_neon_active(void *v)
{
    return g_call_vehicle_is_neon_active(v);
}

void vehicle_get_neon_active(void *v, int *left, int *right, int *front, int *back)
{
    return g_call_vehicle_get_neon_active(v, left, right, front, back);
}

RGBA vehicle_get_neon_color(void *v)
{
    return g_call_vehicle_get_neon_color(v);
}

unsigned long vehicle_get_livery(void *v)
{
    return g_call_vehicle_get_livery(v);
}

unsigned long vehicle_get_roof_livery(void *v)
{
    return g_call_vehicle_get_roof_livery(v);
}

int vehicle_is_engine_on(void *v)
{
    return g_call_vehicle_is_engine_on(v);
}

int vehicle_is_handbrake_active(void *v)
{
    return g_call_vehicle_is_handbrake_active(v);
}

unsigned long vehicle_get_headlight_color(void *v)
{
    return g_call_vehicle_get_headlight_color(v);
}

unsigned long vehicle_get_radio_station_index(void *v)
{
    return g_call_vehicle_get_radio_station_index(v);
}

int vehicle_is_siren_active(void *v)
{
    return g_call_vehicle_is_siren_active(v);
}

unsigned long vehicle_get_lock_state(void *v)
{
    return g_call_vehicle_get_lock_state(v);
}

unsigned long vehicle_get_door_state(void *v, unsigned int doorId)
{
    return g_call_vehicle_get_door_state(v, doorId);
}

int vehicle_is_window_opened(void *v, unsigned int windowId)
{
    return g_call_vehicle_is_window_opened(v, windowId);
}

int vehicle_is_daylight_on(void *v)
{
    return g_call_vehicle_is_daylight_on(v);
}

int vehicle_is_nightlight_on(void *v)
{
    return g_call_vehicle_is_nightlight_on(v);
}

unsigned long vehicle_get_roof_state(void *v)
{
    return g_call_vehicle_get_roof_state(v);
}

int vehicle_is_flamethrower_active(void *v)
{
    return g_call_vehicle_is_flamethrower_active(v);
}

float vehicle_get_lights_multiplier(void *v)
{
    return g_call_vehicle_get_lights_multiplier(v);
}

unsigned long vehicle_get_engine_health(void *v)
{
    return g_call_vehicle_get_engine_health(v);
}

unsigned long vehicle_get_petrol_tank_health(void *v)
{
    return g_call_vehicle_get_petrol_tank_health(v);
}

unsigned long vehicle_get_wheels_count(void *v)
{
    return g_call_vehicle_get_wheels_count(v);
}

int vehicle_is_wheel_burst(void *v, unsigned int wheelId)
{
    return g_call_vehicle_is_wheel_burst(v, wheelId);
}

int vehicle_does_wheel_has_tire(void *v, unsigned int wheelId)
{
    return g_call_vehicle_does_wheel_has_tire(v, wheelId);
}

int vehicle_is_wheel_detached(void *v, unsigned int wheelId)
{
    return g_call_vehicle_is_wheel_detached(v, wheelId);
}

int vehicle_is_wheel_on_fire(void *v, unsigned int wheelId)
{
    return g_call_vehicle_is_wheel_on_fire(v, wheelId);
}

float vehicle_get_wheel_health(void *v, unsigned int wheelId)
{
    return g_call_vehicle_get_wheel_health(v, wheelId);
}

unsigned long vehicle_get_repairs_count(void *v)
{
    return g_call_vehicle_get_repairs_count(v);
}

unsigned long vehicle_get_body_health(void *v)
{
    return g_call_vehicle_get_body_health(v);
}

unsigned long vehicle_get_body_additional_health(void *v)
{
    return g_call_vehicle_get_body_additional_health(v);
}

unsigned long vehicle_get_part_damage_level(void *v, unsigned int partId)
{
    return g_call_vehicle_get_part_damage_level(v, partId);
}

unsigned long vehicle_get_part_bullet_holes(void *v, unsigned int partId)
{
    return g_call_vehicle_get_part_bullet_holes(v, partId);
}

int vehicle_is_light_damaged(void *v, unsigned int lightId)
{
    return g_call_vehicle_is_light_damaged(v, lightId);
}

int vehicle_is_window_damaged(void *v, unsigned int windowId)
{
    return g_call_vehicle_is_window_damaged(v, windowId);
}

int vehicle_is_special_light_damaged(void *v, unsigned int specialLightId)
{
    return g_call_vehicle_is_special_light_damaged(v, specialLightId);
}

int vehicle_has_armored_windows(void *v)
{
    return g_call_vehicle_has_armored_windows(v);
}

float vehicle_get_armored_window_health(void *v, unsigned int windowId)
{
    return g_call_vehicle_get_armored_window_health(v, windowId);
}

unsigned long vehicle_get_armored_window_shoot_count(void *v, unsigned int windowId)
{
    return g_call_vehicle_get_armored_window_shoot_count(v, windowId);
}

unsigned long vehicle_get_bumper_damage_level(void *v, unsigned int bumperId)
{
    return g_call_vehicle_get_bumper_damage_level(v, bumperId);
}

int vehicle_is_manual_engine_control(void *v)
{
    return g_call_vehicle_is_manual_engine_control(v);
}

void vehicle_toggle_extra(void *v, unsigned int extraID, int state)
{
    return g_call_vehicle_toggle_extra(v, extraID, state);
}

void vehicle_set_fixed(void *v)
{
    return g_call_vehicle_set_fixed(v);
}

int vehicle_set_mod(void *v, unsigned int category, unsigned int id)
{
    return g_call_vehicle_set_mod(v, category, id);
}

int vehicle_set_mod_kit(void *v, unsigned int id)
{
    return g_call_vehicle_set_mod_kit(v, id);
}

void vehicle_set_primary_color(void *v, unsigned int color)
{
    return g_call_vehicle_set_primary_color(v, color);
}

void vehicle_set_primary_color_r_g_b(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    return g_call_vehicle_set_primary_color_r_g_b(v, r, g, b, a);
}

void vehicle_set_secondary_color(void *v, unsigned int color)
{
    return g_call_vehicle_set_secondary_color(v, color);
}

void vehicle_set_secondary_color_r_g_b(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    return g_call_vehicle_set_secondary_color_r_g_b(v, r, g, b, a);
}

void vehicle_set_pearl_color(void *v, unsigned int color)
{
    return g_call_vehicle_set_pearl_color(v, color);
}

void vehicle_set_wheel_color(void *v, unsigned int color)
{
    return g_call_vehicle_set_wheel_color(v, color);
}

void vehicle_set_interior_color(void *v, unsigned int color)
{
    return g_call_vehicle_set_interior_color(v, color);
}

void vehicle_set_dashboard_color(void *v, unsigned int color)
{
    return g_call_vehicle_set_dashboard_color(v, color);
}

void vehicle_set_tire_smoke_color(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    return g_call_vehicle_set_tire_smoke_color(v, r, g, b, a);
}

void vehicle_set_wheels(void *v, unsigned int type, unsigned int variation)
{
    return g_call_vehicle_set_wheels(v, type, variation);
}

void vehicle_set_rear_wheels(void *v, unsigned int variation)
{
    return g_call_vehicle_set_rear_wheels(v, variation);
}

void vehicle_set_custom_tires(void *v, int state)
{
    return g_call_vehicle_set_custom_tires(v, state);
}

void vehicle_set_special_darkness(void *v, unsigned int value)
{
    return g_call_vehicle_set_special_darkness(v, value);
}

void vehicle_set_numberplate_index(void *v, unsigned int index)
{
    return g_call_vehicle_set_numberplate_index(v, index);
}

void vehicle_set_numberplate_text(void *v, const char* text)
{
    return g_call_vehicle_set_numberplate_text(v, text);
}

void vehicle_set_window_tint(void *v, unsigned int tint)
{
    return g_call_vehicle_set_window_tint(v, tint);
}

void vehicle_set_dirt_level(void *v, unsigned int level)
{
    return g_call_vehicle_set_dirt_level(v, level);
}

void vehicle_set_neon_active(void *v, int left, int right, int front, int back)
{
    return g_call_vehicle_set_neon_active(v, left, right, front, back);
}

void vehicle_set_neon_color(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    return g_call_vehicle_set_neon_color(v, r, g, b, a);
}

void vehicle_set_livery(void *v, unsigned int livery)
{
    return g_call_vehicle_set_livery(v, livery);
}

void vehicle_set_roof_livery(void *v, unsigned int roofLivery)
{
    return g_call_vehicle_set_roof_livery(v, roofLivery);
}

void vehicle_set_engine_on(void *v, int state)
{
    return g_call_vehicle_set_engine_on(v, state);
}

void vehicle_set_headlight_color(void *v, unsigned int color)
{
    return g_call_vehicle_set_headlight_color(v, color);
}

void vehicle_set_radio_station_index(void *v, unsigned int stationIndex)
{
    return g_call_vehicle_set_radio_station_index(v, stationIndex);
}

void vehicle_set_siren_active(void *v, int state)
{
    return g_call_vehicle_set_siren_active(v, state);
}

void vehicle_set_lock_state(void *v, unsigned int state)
{
    return g_call_vehicle_set_lock_state(v, state);
}

void vehicle_set_door_state(void *v, unsigned int doorId, unsigned int state)
{
    return g_call_vehicle_set_door_state(v, doorId, state);
}

void vehicle_set_window_opened(void *v, unsigned int windowId, int state)
{
    return g_call_vehicle_set_window_opened(v, windowId, state);
}

void vehicle_set_roof_state(void *v, unsigned int state)
{
    return g_call_vehicle_set_roof_state(v, state);
}

void vehicle_set_lights_multiplier(void *v, float multiplier)
{
    return g_call_vehicle_set_lights_multiplier(v, multiplier);
}

void vehicle_set_engine_health(void *v, unsigned long health)
{
    return g_call_vehicle_set_engine_health(v, health);
}

void vehicle_set_petrol_tank_health(void *v, unsigned long health)
{
    return g_call_vehicle_set_petrol_tank_health(v, health);
}

void vehicle_set_wheel_burst(void *v, unsigned int wheelId, int state)
{
    return g_call_vehicle_set_wheel_burst(v, wheelId, state);
}

void vehicle_set_wheel_has_tire(void *v, unsigned int wheelId, int state)
{
    return g_call_vehicle_set_wheel_has_tire(v, wheelId, state);
}

void vehicle_set_wheel_detached(void *v, unsigned int wheelId, int state)
{
    return g_call_vehicle_set_wheel_detached(v, wheelId, state);
}

void vehicle_set_wheel_on_fire(void *v, unsigned int wheelId, int state)
{
    return g_call_vehicle_set_wheel_on_fire(v, wheelId, state);
}

void vehicle_set_wheel_health(void *v, unsigned int wheelId, float health)
{
    return g_call_vehicle_set_wheel_health(v, wheelId, health);
}

void vehicle_set_wheel_fixed(void *v, unsigned int wheelId)
{
    return g_call_vehicle_set_wheel_fixed(v, wheelId);
}

void vehicle_set_body_health(void *v, unsigned long health)
{
    return g_call_vehicle_set_body_health(v, health);
}

void vehicle_set_body_additional_health(void *v, unsigned long health)
{
    return g_call_vehicle_set_body_additional_health(v, health);
}

void vehicle_set_part_damage_level(void *v, unsigned int partId, unsigned int damage)
{
    return g_call_vehicle_set_part_damage_level(v, partId, damage);
}

void vehicle_set_part_bullet_holes(void *v, unsigned int partId, unsigned int shootsCount)
{
    return g_call_vehicle_set_part_bullet_holes(v, partId, shootsCount);
}

void vehicle_set_light_damaged(void *v, unsigned int lightId, int isDamaged)
{
    return g_call_vehicle_set_light_damaged(v, lightId, isDamaged);
}

void vehicle_set_window_damaged(void *v, unsigned int windowId, int isDamaged)
{
    return g_call_vehicle_set_window_damaged(v, windowId, isDamaged);
}

void vehicle_set_special_light_damaged(void *v, unsigned int specialLightId, int isDamaged)
{
    return g_call_vehicle_set_special_light_damaged(v, specialLightId, isDamaged);
}

void vehicle_set_armored_window_health(void *v, unsigned int windowId, float health)
{
    return g_call_vehicle_set_armored_window_health(v, windowId, health);
}

void vehicle_set_armored_window_shoot_count(void *v, unsigned int windowId, unsigned int count)
{
    return g_call_vehicle_set_armored_window_shoot_count(v, windowId, count);
}

void vehicle_set_bumper_damage_level(void *v, unsigned int bumperId, unsigned int damageLevel)
{
    return g_call_vehicle_set_bumper_damage_level(v, bumperId, damageLevel);
}

void vehicle_set_manual_engine_control(void *v, int state)
{
    return g_call_vehicle_set_manual_engine_control(v, state);
}

void * vehicle_get_attached(void *v)
{
    return g_call_vehicle_get_attached(v);
}

void * vehicle_get_attached_to(void *v)
{
    return g_call_vehicle_get_attached_to(v);
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

// ColShape
int col_shape_get_type(void *c)
{
    return g_call_col_shape_get_type(c);
}

int col_shape_has_meta_data(void* base, const char *key)
{
    return g_call_col_shape_has_meta_data(base, key);
}

MetaData col_shape_get_meta_data(void* base, const char *key)
{
    return g_call_col_shape_get_meta_data(base, key);
}

void col_shape_set_meta_data(void *base, const char *key, void *val)
{
    return g_call_col_shape_set_meta_data(base, key, val);
}

void col_shape_delete_meta_data(void *base, const char *key)
{
    return g_call_col_shape_delete_meta_data(base, key);
}

Position col_shape_get_position(void *p)
{
    return g_call_col_shape_get_position(p);
}

void col_shape_set_position(void* p, float x, float y, float z)
{
    return g_call_col_shape_set_position(p, x, y, z);
}

long col_shape_get_dimension(void* p)
{
    return g_call_col_shape_get_dimension(p);
}

void col_shape_set_dimension(void* p, long dimension)
{
    return g_call_col_shape_set_dimension(p, dimension);
}

int col_shape_get_col_shape_type(void *c)
{
    return g_call_col_shape_get_col_shape_type(c);
}

int col_shape_is_entity_in(void *c, void *e)
{
    return g_call_col_shape_is_entity_in(c, e);
}

int col_shape_is_point_in(void *c, float x, float y, float z)
{
    return g_call_col_shape_is_point_in(c, x, y, z);
}

void col_shape_set_players_only(void *c, int state)
{
    return g_call_col_shape_set_players_only(c, state);
}

int col_shape_is_players_only(void *c)
{
    return g_call_col_shape_is_players_only(c);
}

// Checkpoint
int checkpoint_get_type(void *c)
{
    return g_call_checkpoint_get_type(c);
}

int checkpoint_has_meta_data(void* base, const char *key)
{
    return g_call_checkpoint_has_meta_data(base, key);
}

MetaData checkpoint_get_meta_data(void* base, const char *key)
{
    return g_call_checkpoint_get_meta_data(base, key);
}

void checkpoint_set_meta_data(void *base, const char *key, void *val)
{
    return g_call_checkpoint_set_meta_data(base, key, val);
}

void checkpoint_delete_meta_data(void *base, const char *key)
{
    return g_call_checkpoint_delete_meta_data(base, key);
}

Position checkpoint_get_position(void *p)
{
    return g_call_checkpoint_get_position(p);
}

void checkpoint_set_position(void* p, float x, float y, float z)
{
    return g_call_checkpoint_set_position(p, x, y, z);
}

long checkpoint_get_dimension(void* p)
{
    return g_call_checkpoint_get_dimension(p);
}

void checkpoint_set_dimension(void* p, long dimension)
{
    return g_call_checkpoint_set_dimension(p, dimension);
}

int checkpoint_get_col_shape_type(void *c)
{
    return g_call_checkpoint_get_col_shape_type(c);
}

int checkpoint_is_entity_in(void *c, void *e)
{
    return g_call_checkpoint_is_entity_in(c, e);
}

int checkpoint_is_point_in(void *c, float x, float y, float z)
{
    return g_call_checkpoint_is_point_in(c, x, y, z);
}

void checkpoint_set_players_only(void *c, int state)
{
    return g_call_checkpoint_set_players_only(c, state);
}

int checkpoint_is_players_only(void *c)
{
    return g_call_checkpoint_is_players_only(c);
}

unsigned char checkpoint_get_checkpoint_type(void *c)
{
    return g_call_checkpoint_get_checkpoint_type(c);
}

float checkpoint_get_height(void *c)
{
    return g_call_checkpoint_get_height(c);
}

float checkpoint_get_radius(void *c)
{
    return g_call_checkpoint_get_radius(c);
}

RGBA checkpoint_get_color(void *c)
{
    return g_call_checkpoint_get_color(c);
}

Position checkpoint_get_next_position(void *c)
{
    return g_call_checkpoint_get_next_position(c);
}

void checkpoint_set_checkpoint_type(void *c, unsigned char type)
{
    return g_call_checkpoint_set_checkpoint_type(c, type);
}

void checkpoint_set_height(void *c, float height)
{
    return g_call_checkpoint_set_height(c, height);
}

void checkpoint_set_radius(void *c, float radius)
{
    return g_call_checkpoint_set_radius(c, radius);
}

void checkpoint_set_color(void *c, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return g_call_checkpoint_set_color(c, r, g, b, a);
}

void checkpoint_set_next_position(void *c, float x, float y, float z)
{
    return g_call_checkpoint_set_next_position(c, x, y, z);
}

// VoiceChannel
int voice_channel_get_type(void *c)
{
    return g_call_channel_get_type(c);
}

int voice_channel_has_meta_data(void* base, const char *key)
{
    return g_call_channel_has_meta_data(base, key);
}

MetaData voice_channel_get_meta_data(void* base, const char *key)
{
    return g_call_channel_get_meta_data(base, key);
}

void voice_channel_set_meta_data(void *base, const char *key, void *val)
{
    return g_call_channel_set_meta_data(base, key, val);
}

void voice_channel_delete_meta_data(void *base, const char *key)
{
    return g_call_channel_delete_meta_data(base, key);
}

int voice_channel_is_spatial(void *v)
{
    return g_call_channel_is_spatial(v);
}

float voice_channel_get_max_distance(void *v)
{
    return g_call_channel_get_max_distance(v);
}

int voice_channel_has_player(void *v, void *p)
{
    return g_call_channel_has_player(v, p);
}

void voice_channel_add_player(void *v, void *p)
{
    return g_call_channel_add_player(v, p);
}

void voice_channel_remove_player(void *v, void *p)
{
    return g_call_channel_remove_player(v, p);
}

int voice_channel_is_player_muted(void *v, void *p)
{
    return g_call_channel_is_player_muted(v, p);
}

void voice_channel_mute_player(void *v, void *p)
{
    return g_call_channel_mute_player(v, p);
}

void voice_channel_unmute_player(void *v, void *p)
{
    return g_call_channel_unmute_player(v, p);
}
