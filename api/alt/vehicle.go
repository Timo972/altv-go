package alt

/*
#cgo windows CFLAGS: -I../../c-api/lib
#cgo windows LDFLAGS: -L../../c-api/lib/win32 -lcapi

#cgo linux CFLAGS: -I../../c-api/lib
#cgo linux LDFLAGS: -g -L../../c-api/lib/linux -lcapi  -ldl

#ifndef GOLANG_APP
#define GOLANG_APP

#include <stdlib.h>
#include "capi.h"

#endif
*/
import "C"
import (
	"context"
	"errors"
	"fmt"
	"github.com/timo972/altv-go/internal/pb"
	"unsafe"

	"github.com/timo972/altv-go/internal/module"
)

type VehicleModCategory = uint8
type VehicleLockState = uint8
type VehicleDoorState = uint8
type NumberPlateStyle = uint8
type RadioStation = uint8
type VehicleBumper = uint8
type VehicleBumperDamage = uint8
type VehicleDoor = uint8
type VehiclePart = uint8
type VehiclePartDamage = uint8
type WindowTint = uint8

const (
	TintDarkSmoke WindowTint = iota
	TintGreen
	TintLightSmoke
	TintLimo
	TintNone
	TintPureBlack
	TintStock
)

const (
	PartDamagedLevel1 VehiclePartDamage = iota
	PartDamagedLevel2
	PartDamagedLevel3
	PartNotDamaged
)

const (
	FrontLeft VehiclePart = iota
	FrontRight
	MiddleLeft
	MiddleRight
	RearLeft
	RearRight
)

const (
	DoorDriverFront VehicleDoor = iota
	DoorDriverRear
	DoorHood
	DoorPassengerFront
	DoorPassengerRear
	DoorTrunk
)

const (
	BumperDamaged VehicleBumperDamage = iota
	BumperNone
	BumperNotDamaged
)

const (
	Front VehicleBumper = iota
	Rear
)

const (
	BlaineCountyRadio RadioStation = iota
	ChannelX
	EastLosFm
	FlyloFm
	LosSantosRockRadio
	NonStopPopFm
	RadioLosSantos
	RadioMirrorPark
	RadioOff
	RebelRadio
	SelfRadio
	SoulwaxFm
	Space
	TheBlueArk
	TheLab
	TheLowdown
	VinewoodBoulevardRadio
	WestCoastClassics
	WestCoastTalkRadio
	WorldWideFm
)

const (
	BlueWhite NumberPlateStyle = iota
	BlueWhite2
	BlueWhite3
	Yankton
	YellowBlack
	YellowBlue
)

const (
	Closed VehicleDoorState = iota
	OpenedLevel1
	OpenedLevel2
	OpenedLevel3
	OpenedLevel4
	OpenedLevel5
	OpenedLevel6
	OpenedLevel7
	Unknown
)

const (
	ForceDoorsShut VehicleLockState = iota
	InitiallyLocked
	LockPlayerInside
	Locked
	LockedCanBeDamaged
	LockoutPlayerOnly
	None
	Unlocked
)

const (
	Aerials VehicleModCategory = iota
	AirFilter
	ArchCover
	Armor
	BackWheels
	Brakes
	ColumnShifterLeavers
	Dashboard
	Dial
	DoorSpeaker
	Engine
	EngineBlock
	Exhaust
	Fender
	Frame
	FrontBumper
	FrontWheels
	Grille
	Hood
	Horn
	Hydraulics
	Livery
	Ornaments
	Plaques
	Plateholder
	RearBumper
	RightFender
	Roof
	Seats
	SideSkirt
	Speakers
	Spoiler
	SteeringWheel
	Struts
	Suspension
	Tank
	TireSmoke
	Transmission
	Trim
	TrimDesign
	Trunk
	Turbo
	Unk1
	Unk2
	Unk3
	Unk4
	VanityPlates
	Windows
	XenonLights
)

type Vehicle struct {
	Entity
}

func newVehicle(p unsafe.Pointer) *Vehicle {
	vehicle := &Vehicle{}
	vehicle.ptr = p
	vehicle.Type = VehicleObject

	return vehicle
}

func newVehicleArray(arr C.struct_array) []*Vehicle {
	values, size := convertArray[unsafe.Pointer](arr)

	vehicles := make([]*Vehicle, size)

	if size == 0 {
		return vehicles
	}

	for i := 0; i < size; i++ {
		v := values[i]
		vehicles[i] = newVehicle(v)
	}

	return vehicles
}

func CreateVehicle(model uint32, pos Vector3, rot Vector3) (*Vehicle, error) {
	p, err := coreService.CreateVehicle(context.Background(), &pb.CreateVehicleRequest{
		Model: &model,
		Pos:   pos.pb(),
		Rot:   rot.pb(),
	})

	if err != nil {
		return nil, fmt.Errorf("failed to create vehicle: %v is not a proper model hash", model)
	}

	ptr, err := parsePointer(p.GetPtr())
	if err != nil {
		return nil, fmt.Errorf("failed to parse vehicle pointer: %v", err.Error())
	}

	veh := newVehicle(ptr)

	if !veh.Valid() {
		return nil, errors.New("could not create vehicle")
	}

	return veh, nil
}

func (v Vehicle) String() string {
	return fmt.Sprintf("Vehicle{}")
}

func (v Vehicle) Driver() *Player {
	cPtr := C.vehicle_get_driver(v.ptr)
	if cPtr == nil {
		return nil
	}
	player := newPlayer(unsafe.Pointer(cPtr))
	return player
}

func (v Vehicle) IsDestroyed() bool {
	return int(C.vehicle_is_destroyed(v.ptr)) == 1
}

func (v Vehicle) Mod(category VehicleModCategory) uint8 {
	return uint8(C.vehicle_get_mod(v.ptr, C.uint(category)))
}

func (v Vehicle) ModsCount(category VehicleModCategory) uint8 {
	return uint8(C.vehicle_get_mods_count(v.ptr, C.uint(category)))
}

func (v Vehicle) ModKit() uint8 {
	return uint8(C.vehicle_get_mod_kit(v.ptr))
}

func (v Vehicle) ModKitsCount() uint8 {
	return uint8(C.vehicle_get_mod_kits_count(v.ptr))
}

func (v Vehicle) IsPrimaryColorRGB() bool {
	return int(C.vehicle_is_primary_color_r_g_b(v.ptr)) == 1
}

func (v Vehicle) PrimaryColor() uint8 {
	return uint8(C.vehicle_get_primary_color(v.ptr))
}

func (v Vehicle) PrimaryColorRGB() RGBA {
	color := C.vehicle_get_primary_color_r_g_b(v.ptr)
	return RGBA{R: uint8(color.r), G: uint8(color.g), B: uint8(color.b), A: uint8(color.a)}
}

func (v Vehicle) IsSecondaryColorRGB() bool {
	return int(C.vehicle_is_secondary_color_r_g_b(v.ptr)) == 1
}

func (v Vehicle) SecondaryColor() uint8 {
	return uint8(C.vehicle_get_secondary_color(v.ptr))
}

func (v Vehicle) SecondaryColorRGB() RGBA {
	color := C.vehicle_get_secondary_color_r_g_b(v.ptr)
	return RGBA{R: uint8(color.r), G: uint8(color.g), B: uint8(color.b), A: uint8(color.a)}
}

func (v Vehicle) PearlColor() uint8 {
	return uint8(C.vehicle_get_pearl_color(v.ptr))
}

func (v Vehicle) WheelColor() uint8 {
	return uint8(C.vehicle_get_wheel_color(v.ptr))
}

func (v Vehicle) InteriorColor() uint8 {
	return uint8(C.vehicle_get_interior_color(v.ptr))
}

func (v Vehicle) DashboardColor() uint8 {
	return uint8(C.vehicle_get_dashboard_color(v.ptr))
}

func (v Vehicle) IsTireSmokeColorCustom() bool {
	return int(C.vehicle_is_tire_smoke_color_custom(v.ptr)) == 1
}

func (v Vehicle) TireSmokeColor() RGBA {
	color := C.vehicle_get_tire_smoke_color(v.ptr)
	return RGBA{R: uint8(color.r), G: uint8(color.g), B: uint8(color.b), A: uint8(color.a)}
}

func (v Vehicle) WheelType() uint8 {
	return uint8(C.vehicle_get_wheel_type(v.ptr))
}

func (v Vehicle) WheelVariation() uint8 {
	return uint8(C.vehicle_get_wheel_variation(v.ptr))
}

func (v Vehicle) RearWheelVariation() uint8 {
	return uint8(C.vehicle_get_rear_wheel_variation(v.ptr))
}

func (v Vehicle) CustomTires() bool {
	return int(C.vehicle_get_custom_tires(v.ptr)) == 1
}

func (v Vehicle) SpecialDarkness() uint8 {
	return uint8(C.vehicle_get_special_darkness(v.ptr))
}

func (v Vehicle) NumberPlateIndex() uint32 {
	return uint32(C.vehicle_get_numberplate_index(v.ptr))
}

func (v Vehicle) NumberPlateText() string {
	return C.GoString(C.vehicle_get_numberplate_text(v.ptr))
}

func (v Vehicle) WindowTint() uint8 {
	return uint8(C.vehicle_get_window_tint(v.ptr))
}

func (v Vehicle) DirtLevel() uint8 {
	return uint8(C.vehicle_get_dirt_level(v.ptr))
}

func (v Vehicle) IsExtraOn(id uint8) bool {
	return int(C.vehicle_is_extra_on(v.ptr, C.uint(id))) == 1
}

func (v Vehicle) IsNeonActive() bool {
	return int(C.vehicle_is_neon_active(v.ptr)) == 1
}

func (v Vehicle) NeonActive() (front bool, left bool, right bool, back bool) {
	neonState := C.vehicle_get_neon_active(v.ptr)

	front = uint8(neonState.front) == 1
	left = uint8(neonState.left) == 1
	right = uint8(neonState.right) == 1
	back = uint8(neonState.back) == 1

	return front, left, right, back
}

func (v Vehicle) NeonColor() RGBA {
	color := C.vehicle_get_neon_color(v.ptr)
	return RGBA{R: uint8(color.r), G: uint8(color.g), B: uint8(color.b), A: uint8(color.a)}
}

func (v Vehicle) Livery() uint8 {
	return uint8(C.vehicle_get_livery(v.ptr))
}

func (v Vehicle) RoofLivery() uint8 {
	return uint8(C.vehicle_get_roof_livery(v.ptr))
}

func (v Vehicle) AppearanceDataBase64() string {
	return C.GoString(C.vehicle_get_appearance_data_base64(v.ptr))
}

func (v Vehicle) IsEngineOn() bool {
	return int(C.vehicle_is_engine_on(v.ptr)) == 1
}

func (v Vehicle) IsHandbrakeActive() bool {
	return int(C.vehicle_is_handbrake_active(v.ptr)) == 1
}

func (v Vehicle) HeadlightColor() uint8 {
	return uint8(C.vehicle_get_headlight_color(v.ptr))
}

func (v Vehicle) RadioStationIndex() uint32 {
	return uint32(C.vehicle_get_radio_station_index(v.ptr))
}

func (v Vehicle) IsSirenActive() bool {
	return int(C.vehicle_is_siren_active(v.ptr)) == 1
}

func (v Vehicle) LockState() uint8 {
	return uint8(C.vehicle_get_lock_state(v.ptr))
}

func (v Vehicle) DoorState(door uint8) uint8 {
	return uint8(C.vehicle_get_door_state(v.ptr, C.uint(door)))
}

func (v Vehicle) IsWindowOpened(window uint8) bool {
	return int(C.vehicle_is_window_opened(v.ptr, C.uint(window))) == 1
}

func (v Vehicle) IsDaylightOn() bool {
	return int(C.vehicle_is_daylight_on(v.ptr)) == 1
}

func (v Vehicle) IsNightlightOn() bool {
	return int(C.vehicle_is_nightlight_on(v.ptr)) == 1
}

func (v Vehicle) RoofState() uint8 {
	return uint8(C.vehicle_get_roof_state(v.ptr))
}

func (v Vehicle) IsFlamethrowerActive() bool {
	return int(C.vehicle_is_flamethrower_active(v.ptr)) == 1
}

func (v Vehicle) LightsMultiplier() float32 {
	return float32(C.vehicle_get_lights_multiplier(v.ptr))
}

func (v Vehicle) EngineHealth() int32 {
	return int32(C.vehicle_get_engine_health(v.ptr))
}

func (v Vehicle) PetrolTankHealth() int32 {
	return int32(C.vehicle_get_petrol_tank_health(v.ptr))
}

func (v Vehicle) WheelsCount() uint8 {
	return uint8(C.vehicle_get_wheels_count(v.ptr))
}

func (v Vehicle) IsWheelBurst(wheel uint8) bool {
	return int(C.vehicle_is_wheel_burst(v.ptr, C.uint(wheel))) == 1
}

func (v Vehicle) DoesWheelHasTire(wheel uint8) bool {
	return int(C.vehicle_does_wheel_has_tire(v.ptr, C.uint(wheel))) == 1
}

func (v Vehicle) IsWheelDetached(wheel uint8) bool {
	return int(C.vehicle_is_wheel_detached(v.ptr, C.uint(wheel))) == 1
}

func (v Vehicle) IsWheelOnFire(wheel uint8) bool {
	return int(C.vehicle_is_wheel_on_fire(v.ptr, C.uint(wheel))) == 1
}

func (v Vehicle) WheelHealth(wheel uint8) float32 {
	return float32(C.vehicle_get_wheel_health(v.ptr, C.uint(wheel)))
}

func (v Vehicle) RepairsCount() uint8 {
	return uint8(C.vehicle_get_repairs_count(v.ptr))
}

func (v Vehicle) BodyHealth() uint32 {
	return uint32(C.vehicle_get_body_health(v.ptr))
}

func (v Vehicle) BodyAdditionalHealth() uint32 {
	return uint32(C.vehicle_get_body_additional_health(v.ptr))
}

func (v Vehicle) HealthDataBase64() string {
	return C.GoString(C.vehicle_get_health_data_base64(v.ptr))
}

func (v Vehicle) PartDamageLevel(part uint8) uint8 {
	return uint8(C.vehicle_get_part_damage_level(v.ptr, C.uint(part)))
}

func (v Vehicle) PartBulletHoles(part uint8) uint8 {
	return uint8(C.vehicle_get_part_bullet_holes(v.ptr, C.uint(part)))
}

func (v Vehicle) IsLightDamaged(light uint8) bool {
	return int(C.vehicle_is_light_damaged(v.ptr, C.uint(light))) == 1
}

func (v Vehicle) IsWindowDamaged(window uint8) bool {
	return int(C.vehicle_is_window_damaged(v.ptr, C.uint(window))) == 1
}

func (v Vehicle) IsSpecialLightDamaged(light uint8) bool {
	return int(C.vehicle_is_special_light_damaged(v.ptr, C.uint(light))) == 1
}

func (v Vehicle) HasArmoredWindows() bool {
	return int(C.vehicle_has_armored_windows(v.ptr)) == 1
}

func (v Vehicle) ArmoredWindowHealth(window uint8) float32 {
	return float32(C.vehicle_get_armored_window_health(v.ptr, C.uint(window)))
}

func (v Vehicle) ArmoredWindowShootCount(window uint8) uint8 {
	return uint8(C.vehicle_get_armored_window_shoot_count(v.ptr, C.uint(window)))
}

func (v Vehicle) BumperDamageLevel(bumper uint8) uint8 {
	return uint8(C.vehicle_get_armored_window_shoot_count(v.ptr, C.uint(bumper)))
}

func (v Vehicle) GameStateBase64() string {
	return C.GoString(C.vehicle_get_game_state_base64(v.ptr))
}

func (v Vehicle) ScriptDataBase64() string {
	return C.GoString(C.vehicle_get_script_data_base64(v.ptr))
}

func (v Vehicle) DamageDataBase64() string {
	return C.GoString(C.vehicle_get_damage_data_base64(v.ptr))
}

func (v Vehicle) IsManualEngineControl() bool {
	return int(C.vehicle_is_manual_engine_control(v.ptr)) == 1
}

func (v Vehicle) ToggleExtra(extra uint8, state bool) {
	C.vehicle_toggle_extra(v.ptr, C.uint(extra), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetFixed() {
	C.vehicle_set_fixed(v.ptr)
}

func (v Vehicle) SetMod(category uint8, id uint8) bool {
	return int(C.vehicle_set_mod(v.ptr, C.uint(category), C.uint(id))) == 1
}

func (v Vehicle) SetModKit(id uint8) bool {
	return int(C.vehicle_set_mod_kit(v.ptr, C.uint(id))) == 1
}

func (v Vehicle) SetPrimaryColor(color uint8) {
	C.vehicle_set_primary_color(v.ptr, C.uint(color))
}

func (v Vehicle) SetPrimaryColorRGB(color RGBA) {
	C.vehicle_set_primary_color_r_g_b(v.ptr, C.uint(color.R), C.uint(color.G), C.uint(color.B), C.uint(color.A))
}

func (v Vehicle) SetSecondaryColor(color uint8) {
	C.vehicle_set_secondary_color(v.ptr, C.uint(color))
}

func (v Vehicle) SetSecondaryColorRGB(color RGBA) {
	C.vehicle_set_secondary_color_r_g_b(v.ptr, C.uint(color.R), C.uint(color.G), C.uint(color.B), C.uint(color.A))
}

func (v Vehicle) SetPearlColor(color uint8) {
	C.vehicle_set_pearl_color(v.ptr, C.uint(color))
}

func (v Vehicle) SetWheelColor(color uint8) {
	C.vehicle_set_wheel_color(v.ptr, C.uint(color))
}

func (v Vehicle) SetInteriorColor(color uint8) {
	C.vehicle_set_interior_color(v.ptr, C.uint(color))
}

func (v Vehicle) SetDashboardColor(color uint8) {
	C.vehicle_set_dashboard_color(v.ptr, C.uint(color))
}

func (v Vehicle) SetTireSmokeColor(color RGBA) {
	C.vehicle_set_tire_smoke_color(v.ptr, C.uint(color.R), C.uint(color.G), C.uint(color.B), C.uint(color.A))
}

func (v Vehicle) SetWheels(wheelType uint8, variation uint8) {
	C.vehicle_set_wheels(v.ptr, C.uint(wheelType), C.uint(variation))
}

func (v Vehicle) SetRearWheels(variation uint8) {
	C.vehicle_set_rear_wheels(v.ptr, C.uint(variation))
}

func (v Vehicle) SetCustomTires(state bool) {
	C.vehicle_set_custom_tires(v.ptr, C.int(module.Bool2int(state)))
}

func (v Vehicle) SetSpecialDarkness(value uint8) {
	C.vehicle_set_special_darkness(v.ptr, C.uint(value))
}

func (v Vehicle) SetNumberplateIndex(index uint32) {
	C.vehicle_set_numberplate_index(v.ptr, C.uint(index))
}

func (v Vehicle) SetNumberplateText(text string) {
	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	C.vehicle_set_numberplate_text(v.ptr, cText)
}

func (v Vehicle) SetWindowTint(tint uint8) {
	C.vehicle_set_window_tint(v.ptr, C.uint(tint))
}

func (v Vehicle) SetDirtLevel(dirt uint8) {
	C.vehicle_set_dirt_level(v.ptr, C.uint(dirt))
}

func (v Vehicle) SetNeonActive(front bool, left bool, right bool, back bool) {
	C.vehicle_set_neon_active(v.ptr, C.int(module.Bool2int(front)), C.int(module.Bool2int(left)), C.int(module.Bool2int(right)), C.int(module.Bool2int(back)))
}

func (v Vehicle) SetNeonColor(color RGBA) {
	C.vehicle_set_neon_color(v.ptr, C.uint(color.R), C.uint(color.G), C.uint(color.B), C.uint(color.A))
}

func (v Vehicle) SetLivery(livery uint8) {
	C.vehicle_set_livery(v.ptr, C.uint(livery))
}

func (v Vehicle) SetRoofLivery(roofLivery uint8) {
	C.vehicle_set_roof_livery(v.ptr, C.uint(roofLivery))
}

func (v Vehicle) SetEngineOn(state bool) {
	C.vehicle_set_engine_on(v.ptr, C.int(module.Bool2int(state)))
}

func (v Vehicle) SetHeadlightColor(color uint8) {
	C.vehicle_set_headlight_color(v.ptr, C.uint(color))
}

func (v Vehicle) SetRadioStationIndex(stationIndex uint32) {
	C.vehicle_set_radio_station_index(v.ptr, C.uint(stationIndex))
}

func (v Vehicle) SetSirenActive(state bool) {
	C.vehicle_set_siren_active(v.ptr, C.int(module.Bool2int(state)))
}

func (v Vehicle) SetLockState(state uint8) {
	C.vehicle_set_lock_state(v.ptr, C.uint(state))
}

func (v Vehicle) SetDoorState(doorId uint8, state uint8) {
	C.vehicle_set_door_state(v.ptr, C.uint(doorId), C.uint(state))
}

func (v Vehicle) SetWindowOpened(windowId uint8, state bool) {
	C.vehicle_set_window_opened(v.ptr, C.uint(windowId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetRoofState(state uint8) {
	C.vehicle_set_roof_state(v.ptr, C.uint(state))
}

func (v Vehicle) SetLightsMultiplier(multiplier float32) {
	C.vehicle_set_lights_multiplier(v.ptr, C.float(multiplier))
}

func (v Vehicle) SetEngineHealth(health int32) {
	C.vehicle_set_engine_health(v.ptr, C.ulong(health))
}

func (v Vehicle) SetPetrolTankHealth(health int32) {
	C.vehicle_set_petrol_tank_health(v.ptr, C.ulong(health))
}

func (v Vehicle) SetWheelBurst(wheelId uint8, state bool) {
	C.vehicle_set_wheel_burst(v.ptr, C.uint(wheelId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetWheelHasTire(wheelId uint8, state bool) {
	C.vehicle_set_wheel_has_tire(v.ptr, C.uint(wheelId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetWheelDetached(wheelId uint8, state bool) {
	C.vehicle_set_wheel_detached(v.ptr, C.uint(wheelId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetWheelOnFire(wheelId uint8, state bool) {
	C.vehicle_set_wheel_on_fire(v.ptr, C.uint(wheelId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetWheelHealth(wheelId uint8, health float32) {
	C.vehicle_set_wheel_health(v.ptr, C.uint(wheelId), C.float(health))
}

func (v Vehicle) SetWheelFixed(wheelId uint8) {
	C.vehicle_set_wheel_fixed(v.ptr, C.uint(wheelId))
}

func (v Vehicle) SetBodyHealth(health uint32) {
	C.vehicle_set_body_health(v.ptr, C.ulong(health))
}

func (v Vehicle) SetBodyAdditionalHealth(health uint32) {
	C.vehicle_set_body_additional_health(v.ptr, C.ulong(health))
}

func (v Vehicle) SetPartDamageLevel(partId uint8, damage uint8) {
	C.vehicle_set_part_damage_level(v.ptr, C.uint(partId), C.uint(damage))
}

func (v Vehicle) SetPartBulletHoles(partId uint8, shootsCount uint8) {
	C.vehicle_set_part_bullet_holes(v.ptr, C.uint(partId), C.uint(shootsCount))
}

func (v Vehicle) SetLightDamaged(lightId uint8, isDamaged bool) {
	C.vehicle_set_light_damaged(v.ptr, C.uint(lightId), C.int(module.Bool2int(isDamaged)))
}

func (v Vehicle) SetWindowDamaged(windowId uint8, isDamaged bool) {
	C.vehicle_set_window_damaged(v.ptr, C.uint(windowId), C.int(module.Bool2int(isDamaged)))
}

func (v Vehicle) SetSpecialLightDamaged(specialLightId uint8, isDamaged bool) {
	C.vehicle_set_special_light_damaged(v.ptr, C.uint(specialLightId), C.int(module.Bool2int(isDamaged)))
}

func (v Vehicle) SetArmoredWindowHealth(windowId uint8, health float32) {
	C.vehicle_set_armored_window_health(v.ptr, C.uint(windowId), C.float(health))
}

func (v Vehicle) SetArmoredWindowShootCount(windowId uint8, count uint8) {
	C.vehicle_set_armored_window_shoot_count(v.ptr, C.uint(windowId), C.uint(count))
}

func (v Vehicle) SetBumperDamageLevel(bumperId uint8, damageLevel uint8) {
	C.vehicle_set_bumper_damage_level(v.ptr, C.uint(bumperId), C.uint(damageLevel))
}

func (v Vehicle) SetManualEngineControl(state bool) {
	C.vehicle_set_manual_engine_control(v.ptr, C.int(module.Bool2int(state)))
}

func (v Vehicle) Attached() *Vehicle {
	ptr := C.vehicle_get_attached(v.ptr)
	if ptr == nil {
		return nil
	}
	return newVehicle(ptr)
}

func (v Vehicle) AttachedTo() *Vehicle {
	ptr := C.vehicle_get_attached_to(v.ptr)
	if ptr == nil {
		return nil
	}
	return newVehicle(ptr)
}

func (v Vehicle) LoadDamageDataFromBase64(base64 string) {
	data := C.CString(base64)
	defer C.free(unsafe.Pointer(data))

	C.vehicle_load_damage_data_from_base64(v.ptr, data)
}

func (v Vehicle) LoadScriptDataFromBase64(base64 string) {
	data := C.CString(base64)
	defer C.free(unsafe.Pointer(data))

	C.vehicle_load_script_data_from_base64(v.ptr, data)
}

func (v Vehicle) LoadGameStateFromBase64(base64 string) {
	data := C.CString(base64)
	defer C.free(unsafe.Pointer(data))

	C.vehicle_load_game_state_from_base64(v.ptr, data)
}

func (v Vehicle) LoadHealthDataFromBase64(base64 string) {
	data := C.CString(base64)
	defer C.free(unsafe.Pointer(data))

	C.vehicle_load_health_data_from_base64(v.ptr, data)
}

func (v Vehicle) DriftMode() bool {
	return int(C.vehicle_is_drift_mode(v.ptr)) == 1
}

func (v Vehicle) SetDriftMode(enabled bool) {
	C.vehicle_set_drift_mode(v.ptr, C.int(module.Bool2int(enabled)))
}

func (v Vehicle) MissionTrain() bool {
	return int(C.vehicle_is_train_mission_train(v.ptr)) == 1
}

func (v Vehicle) SetMissionTrain(enabled bool) {
	C.vehicle_set_train_mission_train(v.ptr, C.int(module.Bool2int(enabled)))
}

func (v Vehicle) TrainTrackId() int8 {
	return int8(C.vehicle_get_train_track_id(v.ptr))
}

func (v Vehicle) SetTrainTrackId(trackId int8) {
	C.vehicle_set_train_track_id(v.ptr, C.char(trackId))
}

func (v Vehicle) TrainEngine() *Vehicle {
	ptr := C.vehicle_get_train_engine_id(v.ptr)
	if ptr == nil {
		return nil
	}

	return newVehicle(ptr)
}

func (v Vehicle) SetTrainEngine(engine *Vehicle) {
	C.vehicle_set_train_engine_id(v.ptr, engine.ptr)
}

func (v Vehicle) TrainConfigIndex() int8 {
	return int8(C.vehicle_get_train_config_index(v.ptr))
}

func (v Vehicle) SetTrainConfigIndex(configIndex int8) {
	C.vehicle_set_train_config_index(v.ptr, C.char(configIndex))
}

func (v Vehicle) TrainDistanceFromEngine() float32 {
	return float32(C.vehicle_get_train_distance_from_engine(v.ptr))
}

func (v Vehicle) SetTrainDistanceFromEngine(distance float32) {
	C.vehicle_set_train_distance_from_engine(v.ptr, C.float(distance))
}

func (v Vehicle) IsTrainEngine() bool {
	return int(C.vehicle_is_train_engine(v.ptr)) == 1
}

func (v Vehicle) SetTrainIsEngine(isEngine bool) {
	C.vehicle_set_train_is_engine(v.ptr, C.int(module.Bool2int(isEngine)))
}

func (v Vehicle) IsTrainCaboose() bool {
	return int(C.vehicle_is_train_caboose(v.ptr)) == 1
}

func (v Vehicle) SetTrainIsCaboose(isCaboose bool) {
	C.vehicle_set_train_is_caboose(v.ptr, C.int(module.Bool2int(isCaboose)))
}

func (v Vehicle) TrainDirection() bool {
	return int(C.vehicle_get_train_direction(v.ptr)) == 1
}

func (v Vehicle) SetTrainDirection(direction bool) {
	C.vehicle_set_train_direction(v.ptr, C.int(module.Bool2int(direction)))
}

func (v Vehicle) HasTrainPassengerCarriages() bool {
	return int(C.vehicle_has_train_passenger_carriages(v.ptr)) == 1
}

func (v Vehicle) SetTrainHasPassengerCarriages(hasPassengerCarriages bool) {
	C.vehicle_set_train_has_passenger_carriages(v.ptr, C.int(module.Bool2int(hasPassengerCarriages)))
}

func (v Vehicle) TrainRenderDerailed() bool {
	return int(C.vehicle_get_train_render_derailed(v.ptr)) == 1
}

func (v Vehicle) SetTrainRenderDerailed(renderDerailed bool) {
	C.vehicle_set_train_render_derailed(v.ptr, C.int(module.Bool2int(renderDerailed)))
}

func (v Vehicle) TrainForceDoorsOpen() bool {
	return int(C.vehicle_get_train_force_doors_open(v.ptr)) == 1
}

func (v Vehicle) SetTrainForceDoorsOpen(forceDoorsOpen bool) {
	C.vehicle_set_train_force_doors_open(v.ptr, C.int(module.Bool2int(forceDoorsOpen)))
}

func (v Vehicle) TrainCruiseSpeed() float32 {
	return float32(C.vehicle_get_train_cruise_speed(v.ptr))
}

func (v Vehicle) SetTrainCruiseSpeed(speed float32) {
	C.vehicle_set_train_cruise_speed(v.ptr, C.float(speed))
}

func (v Vehicle) TrainCarriageConfigIndex() int8 {
	return int8(C.vehicle_get_train_carriage_config_index(v.ptr))
}

func (v Vehicle) SetTrainCarriageConfigIndex(configIndex int8) {
	C.vehicle_set_train_carriage_config_index(v.ptr, C.char(configIndex))
}

func (v Vehicle) TrainLinkedToBackward() *Vehicle {
	ptr := C.vehicle_get_train_linked_to_backward_id(v.ptr)
	if ptr == nil {
		return nil
	}

	return newVehicle(ptr)
}

func (v Vehicle) SetTrainLinkedToBackward(linkedToBackward *Vehicle) {
	C.vehicle_set_train_linked_to_backward_id(v.ptr, linkedToBackward.ptr)
}

func (v Vehicle) TrainLinkedToForward() *Vehicle {
	ptr := C.vehicle_get_train_linked_to_forward_id(v.ptr)
	if ptr == nil {
		return nil
	}

	return newVehicle(ptr)
}

func (v Vehicle) SetTrainLinkedToForward(linkedToForward *Vehicle) {
	C.vehicle_set_train_linked_to_forward_id(v.ptr, linkedToForward.ptr)
}

func (v Vehicle) SetTrainUnk1(unk1 bool) {
	C.vehicle_set_train_unk1(v.ptr, C.int(module.Bool2int(unk1)))
}

func (v Vehicle) SetTrainUnk2(unk2 bool) {
	C.vehicle_set_train_unk2(v.ptr, C.int(module.Bool2int(unk2)))
}

func (v Vehicle) SetTrainUnk3(unk3 bool) {
	C.vehicle_set_train_unk3(v.ptr, C.int(module.Bool2int(unk3)))
}

func (v Vehicle) TrainUnk1() bool {
	return int(C.vehicle_get_train_unk1(v.ptr)) == 1
}

func (v Vehicle) TrainUnk2() bool {
	return int(C.vehicle_get_train_unk2(v.ptr)) == 1
}

func (v Vehicle) TrainUnk3() bool {
	return int(C.vehicle_get_train_unk3(v.ptr)) == 1
}

func (v Vehicle) BoatAnchorActive() bool {
	return int(C.vehicle_is_boat_anchor_active(v.ptr)) == 1
}

func (v Vehicle) SetBoatAnchorActive(active bool) {
	C.vehicle_set_boat_anchor_active(v.ptr, C.int(module.Bool2int(active)))
}

func (v Vehicle) SetSearchLight(state bool, entity *Entity) bool {
	return int(C.vehicle_set_search_light(v.ptr, C.int(module.Bool2int(state)), newCEntity(entity))) == 1
}

func (v Vehicle) LightState() uint8 {
	return uint8(C.vehicle_get_light_state(v.ptr))
}

func (v Vehicle) SetLightState(state uint8) {
	C.vehicle_set_light_state(v.ptr, C.uchar(state))
}

func (v Vehicle) HasTimedExplosion() bool {
	return uint8(C.vehicle_has_timed_explosion(v.ptr)) == 1
}

func (v Vehicle) TimedExplosionCulprit() *Player {
	p := C.vehicle_get_timed_explosion_culprit(v.ptr)
	return newPlayer(p)
}

func (v Vehicle) TimedExplosionTime() uint32 {
	return uint32(C.vehicle_get_timed_explosion_time(v.ptr))
}

func (v Vehicle) SetTimedExplosion(state bool, culprit *Player, time uint32) {
	C.vehicle_set_timed_explosion(v.ptr, C.uchar(module.Bool2int(state)), culprit.ptr, C.uint(time))
}

func (v Vehicle) IsTowingDisabled() bool {
	return byte(C.vehicle_is_towing_disabled(v.ptr)) == 1
}

func (v Vehicle) SetTowingDisabled(state bool) {
	C.vehicle_set_towing_disabled(v.ptr, C.uchar(module.Bool2int(state)))
}

func (v Vehicle) RocketRefuelSpeed() float32 {
	return float32(C.vehicle_get_rocket_refuel_speed(v.ptr))
}

func (v Vehicle) SetRocketRefuelSpeed(speed float32) {
	C.vehicle_set_rocket_refuel_speed(v.ptr, C.float(speed))
}

func (v Vehicle) BombCount() uint32 {
	return uint32(C.vehicle_get_bomb_count(v.ptr))
}

func (v Vehicle) SetBombCount(count uint32) {
	C.vehicle_set_bomb_count(v.ptr, C.uint(count))
}

func (v Vehicle) CounterMeasureCount() uint32 {
	return uint32(C.vehicle_get_counter_measure_count(v.ptr))
}

func (v Vehicle) SetCounterMeasureCount(count uint32) {
	C.vehicle_set_counter_measure_count(v.ptr, C.uint(count))
}

func (v Vehicle) ScriptMaxSpeed() float32 {
	return float32(C.vehicle_get_script_max_speed(v.ptr))
}

func (v Vehicle) SetScriptMaxSpeed(speed float32) {
	C.vehicle_set_script_max_speed(v.ptr, C.float(speed))
}

func (v Vehicle) WeaponsDisabled() bool {
	return byte(C.vehicle_get_weapons_disabled(v.ptr)) == 1
}

func (v Vehicle) SetWeaponsDisabled(state bool) {
	C.vehicle_set_weapons_disabled(v.ptr, C.uchar(module.Bool2int(state)))
}

func (v Vehicle) WeaponCapacity(index uint8) int32 {
	return int32(C.vehicle_get_weapon_capacity(v.ptr, C.uchar(index)))
}

func (v Vehicle) SetWeaponCapacity(index uint8, cap int32) {
	C.vehicle_set_weapon_capacity(v.ptr, C.uchar(index), C.int(cap))
}

func (v Vehicle) HybridExtraActive() bool {
	return byte(C.vehicle_get_hybrid_extra_active(v.ptr)) == 1
}

func (v Vehicle) SetHybridExtraActive(active bool) {
	C.vehicle_set_hybrid_extra_active(v.ptr, C.uchar(module.Bool2int(active)))
}

func (v Vehicle) HybridExtraState() uint8 {
	return uint8(C.vehicle_get_hybrid_extra_state(v.ptr))
}

func (v Vehicle) SetHybridExtraState(state uint8) {
	C.vehicle_set_hybrid_extra_state(v.ptr, C.uchar(state))
}

func (v Vehicle) DamageModifier() float32 {
	return float32(C.vehicle_get_damage_modifier(v.ptr))
}

func (v Vehicle) SetDamageModifier(modifier float32) {
	C.vehicle_set_damage_modifier(v.ptr, C.float(modifier))
}

func (v Vehicle) DamageMultiplier() float32 {
	return float32(C.vehicle_get_damage_multiplier(v.ptr))
}

func (v Vehicle) SetDamageMultiplier(multiplier float32) {
	C.vehicle_set_damage_multiplier(v.ptr, C.float(multiplier))
}
