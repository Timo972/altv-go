package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import (
	"errors"
	"fmt"
	"unsafe"

	"github.com/shockdev04/altv-go-pkg/internal/module"
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

func NewVehicle(p unsafe.Pointer) *Vehicle {
	vehicle := &Vehicle{}
	vehicle.Ptr = p
	vehicle.Type = VehicleObject

	return vehicle
}

func CreateVehicle(model uint32, pos Vector3, rot Vector3) (*Vehicle, error) {
	vehicle := C.core_create_vehicle(C.ulong(model), C.float(pos.X), C.float(pos.Y), C.float(pos.Z),
		C.float(rot.X), C.float(rot.Y), C.float(rot.Z))

	if vehicle == nil {
		return nil, fmt.Errorf("failed to create vehicle: %v is not a proper model hash", model)
	}

	veh := NewVehicle(vehicle)

	if !veh.Valid() {
		return nil, errors.New("could not create vehicle")
	}

	return veh, nil
}

func (v Vehicle) Driver() *Player {
	cPtr := C.vehicle_get_driver(v.Ptr)
	if cPtr == nil {
		return nil
	}
	player := NewPlayer(unsafe.Pointer(cPtr))
	return player
}

func (v Vehicle) IsDestroyed() bool {
	return int(C.vehicle_is_destroyed(v.Ptr)) == 1
}

func (v Vehicle) Mod(category VehicleModCategory) uint8 {
	return uint8(C.vehicle_get_mod(v.Ptr, C.uint(category)))
}

func (v Vehicle) ModsCount(category VehicleModCategory) uint8 {
	return uint8(C.vehicle_get_mods_count(v.Ptr, C.uint(category)))
}

func (v Vehicle) ModKit() uint8 {
	return uint8(C.vehicle_get_mod_kit(v.Ptr))
}

func (v Vehicle) ModKitsCount() uint8 {
	return uint8(C.vehicle_get_mod_kits_count(v.Ptr))
}

func (v Vehicle) IsPrimaryColorRGB() bool {
	return int(C.vehicle_is_primary_color_r_g_b(v.Ptr)) == 1
}

func (v Vehicle) PrimaryColor() uint8 {
	return uint8(C.vehicle_get_primary_color(v.Ptr))
}

func (v Vehicle) PrimaryColorRGB() RGBA {
	color := C.vehicle_get_primary_color_r_g_b(v.Ptr)
	return RGBA{R: uint8(color.r), G: uint8(color.g), B: uint8(color.b), A: uint8(color.a)}
}

func (v Vehicle) IsSecondaryColorRGB() bool {
	return int(C.vehicle_is_secondary_color_r_g_b(v.Ptr)) == 1
}

func (v Vehicle) SecondaryColor() uint8 {
	return uint8(C.vehicle_get_secondary_color(v.Ptr))
}

func (v Vehicle) SecondaryColorRGB() RGBA {
	color := C.vehicle_get_secondary_color_r_g_b(v.Ptr)
	return RGBA{R: uint8(color.r), G: uint8(color.g), B: uint8(color.b), A: uint8(color.a)}
}

func (v Vehicle) PearlColor() uint8 {
	return uint8(C.vehicle_get_pearl_color(v.Ptr))
}

func (v Vehicle) WheelColor() uint8 {
	return uint8(C.vehicle_get_wheel_color(v.Ptr))
}

func (v Vehicle) InteriorColor() uint8 {
	return uint8(C.vehicle_get_interior_color(v.Ptr))
}

func (v Vehicle) DashboardColor() uint8 {
	return uint8(C.vehicle_get_dashboard_color(v.Ptr))
}

func (v Vehicle) IsTireSmokeColorCustom() bool {
	return int(C.vehicle_is_tire_smoke_color_custom(v.Ptr)) == 1
}

func (v Vehicle) TireSmokeColor() RGBA {
	color := C.vehicle_get_tire_smoke_color(v.Ptr)
	return RGBA{R: uint8(color.r), G: uint8(color.g), B: uint8(color.b), A: uint8(color.a)}
}

func (v Vehicle) WheelType() uint8 {
	return uint8(C.vehicle_get_wheel_type(v.Ptr))
}

func (v Vehicle) WheelVariation() uint8 {
	return uint8(C.vehicle_get_wheel_variation(v.Ptr))
}

func (v Vehicle) RearWheelVariation() uint8 {
	return uint8(C.vehicle_get_rear_wheel_variation(v.Ptr))
}

func (v Vehicle) CustomTires() bool {
	return int(C.vehicle_get_custom_tires(v.Ptr)) == 1
}

func (v Vehicle) SpecialDarkness() uint8 {
	return uint8(C.vehicle_get_special_darkness(v.Ptr))
}

func (v Vehicle) NumberPlateIndex() uint32 {
	return uint32(C.vehicle_get_numberplate_index(v.Ptr))
}

func (v Vehicle) NumberPlateText() string {
	return C.GoString(C.vehicle_get_numberplate_text(v.Ptr))
}

func (v Vehicle) WindowTint() uint8 {
	return uint8(C.vehicle_get_window_tint(v.Ptr))
}

func (v Vehicle) DirtLevel() uint8 {
	return uint8(C.vehicle_get_dirt_level(v.Ptr))
}

func (v Vehicle) IsExtraOn(id uint8) bool {
	return int(C.vehicle_is_extra_on(v.Ptr, C.uint(id))) == 1
}

func (v Vehicle) IsNeonActive() bool {
	return int(C.vehicle_is_neon_active(v.Ptr)) == 1
}

func (v Vehicle) NeonActive() (front bool, left bool, right bool, back bool) {
	neonState := C.vehicle_get_neon_active(v.Ptr)

	front = int(neonState.front) == 1
	left = int(neonState.left) == 1
	right = int(neonState.right) == 1
	back = int(neonState.back) == 1

	return front, left, right, back
}

func (v Vehicle) NeonColor() RGBA {
	color := C.vehicle_get_neon_color(v.Ptr)
	return RGBA{R: uint8(color.r), G: uint8(color.g), B: uint8(color.b), A: uint8(color.a)}
}

func (v Vehicle) Livery() uint8 {
	return uint8(C.vehicle_get_livery(v.Ptr))
}

func (v Vehicle) RoofLivery() uint8 {
	return uint8(C.vehicle_get_roof_livery(v.Ptr))
}

func (v Vehicle) AppearanceDataBase64() string {
	return C.GoString(C.vehicle_get_appearance_data_base64(v.Ptr))
}

func (v Vehicle) IsEngineOn() bool {
	return int(C.vehicle_is_engine_on(v.Ptr)) == 1
}

func (v Vehicle) IsHandbrakeActive() bool {
	return int(C.vehicle_is_handbrake_active(v.Ptr)) == 1
}

func (v Vehicle) HeadlightColor() uint8 {
	return uint8(C.vehicle_get_headlight_color(v.Ptr))
}

func (v Vehicle) RadioStationIndex() uint32 {
	return uint32(C.vehicle_get_radio_station_index(v.Ptr))
}

func (v Vehicle) IsSirenActive() bool {
	return int(C.vehicle_is_siren_active(v.Ptr)) == 1
}

func (v Vehicle) LockState() uint8 {
	return uint8(C.vehicle_get_lock_state(v.Ptr))
}

func (v Vehicle) DoorState(door uint8) uint8 {
	return uint8(C.vehicle_get_door_state(v.Ptr, C.uint(door)))
}

func (v Vehicle) IsWindowOpened(window uint8) bool {
	return int(C.vehicle_is_window_opened(v.Ptr, C.uint(window))) == 1
}

func (v Vehicle) IsDaylightOn() bool {
	return int(C.vehicle_is_daylight_on(v.Ptr)) == 1
}

func (v Vehicle) IsNightlightOn() bool {
	return int(C.vehicle_is_nightlight_on(v.Ptr)) == 1
}

func (v Vehicle) RoofState() uint8 {
	return uint8(C.vehicle_get_roof_state(v.Ptr))
}

func (v Vehicle) IsFlamethrowerActive() bool {
	return int(C.vehicle_is_flamethrower_active(v.Ptr)) == 1
}

func (v Vehicle) LightsMultiplier() float32 {
	return float32(C.vehicle_get_lights_multiplier(v.Ptr))
}

func (v Vehicle) EngineHealth() int32 {
	return int32(C.vehicle_get_engine_health(v.Ptr))
}

func (v Vehicle) PetrolTankHealth() int32 {
	return int32(C.vehicle_get_petrol_tank_health(v.Ptr))
}

func (v Vehicle) WheelsCount() uint8 {
	return uint8(C.vehicle_get_wheels_count(v.Ptr))
}

func (v Vehicle) IsWheelBurst(wheel uint8) bool {
	return int(C.vehicle_is_wheel_burst(v.Ptr, C.uint(wheel))) == 1
}

func (v Vehicle) DoesWheelHasTire(wheel uint8) bool {
	return int(C.vehicle_does_wheel_has_tire(v.Ptr, C.uint(wheel))) == 1
}

func (v Vehicle) IsWheelDetached(wheel uint8) bool {
	return int(C.vehicle_is_wheel_detached(v.Ptr, C.uint(wheel))) == 1
}

func (v Vehicle) IsWheelOnFire(wheel uint8) bool {
	return int(C.vehicle_is_wheel_on_fire(v.Ptr, C.uint(wheel))) == 1
}

func (v Vehicle) WheelHealth(wheel uint8) float32 {
	return float32(C.vehicle_get_wheel_health(v.Ptr, C.uint(wheel)))
}

func (v Vehicle) RepairsCount() uint8 {
	return uint8(C.vehicle_get_repairs_count(v.Ptr))
}

func (v Vehicle) BodyHealth() uint32 {
	return uint32(C.vehicle_get_body_health(v.Ptr))
}

func (v Vehicle) BodyAdditionalHealth() uint32 {
	return uint32(C.vehicle_get_body_additional_health(v.Ptr))
}

func (v Vehicle) HealthDataBase64() string {
	return C.GoString(C.vehicle_get_health_data_base64(v.Ptr))
}

func (v Vehicle) PartDamageLevel(part uint8) uint8 {
	return uint8(C.vehicle_get_part_damage_level(v.Ptr, C.uint(part)))
}

func (v Vehicle) PartBulletHoles(part uint8) uint8 {
	return uint8(C.vehicle_get_part_bullet_holes(v.Ptr, C.uint(part)))
}

func (v Vehicle) IsLightDamaged(light uint8) bool {
	return int(C.vehicle_is_light_damaged(v.Ptr, C.uint(light))) == 1
}

func (v Vehicle) IsWindowDamaged(window uint8) bool {
	return int(C.vehicle_is_window_damaged(v.Ptr, C.uint(window))) == 1
}

func (v Vehicle) IsSpecialLightDamaged(light uint8) bool {
	return int(C.vehicle_is_special_light_damaged(v.Ptr, C.uint(light))) == 1
}

func (v Vehicle) HasArmoredWindows() bool {
	return int(C.vehicle_has_armored_windows(v.Ptr)) == 1
}

func (v Vehicle) ArmoredWindowHealth(window uint8) float32 {
	return float32(C.vehicle_get_armored_window_health(v.Ptr, C.uint(window)))
}

func (v Vehicle) ArmoredWindowShootCount(window uint8) uint8 {
	return uint8(C.vehicle_get_armored_window_shoot_count(v.Ptr, C.uint(window)))
}

func (v Vehicle) BumperDamageLevel(bumper uint8) uint8 {
	return uint8(C.vehicle_get_armored_window_shoot_count(v.Ptr, C.uint(bumper)))
}

func (v Vehicle) GameStateBase64() string {
	return C.GoString(C.vehicle_get_game_state_base64(v.Ptr))
}

func (v Vehicle) ScriptDataBase64() string {
	return C.GoString(C.vehicle_get_script_data_base64(v.Ptr))
}

func (v Vehicle) DamageDataBase64() string {
	return C.GoString(C.vehicle_get_damage_data_base64(v.Ptr))
}

func (v Vehicle) IsManualEngineControl() bool {
	return int(C.vehicle_is_manual_engine_control(v.Ptr)) == 1
}

func (v Vehicle) ToggleExtra(extra uint8, state bool) {
	C.vehicle_toggle_extra(v.Ptr, C.uint(extra), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetFixed() {
	C.vehicle_set_fixed(v.Ptr)
}

func (v Vehicle) SetMod(category uint8, id uint8) bool {
	return int(C.vehicle_set_mod(v.Ptr, C.uint(category), C.uint(id))) == 1
}

func (v Vehicle) SetModKit(id uint8) bool {
	return int(C.vehicle_set_mod_kit(v.Ptr, C.uint(id))) == 1
}

func (v Vehicle) SetPrimaryColor(color uint8) {
	C.vehicle_set_primary_color(v.Ptr, C.uint(color))
}

func (v Vehicle) SetPrimaryColorRGB(color RGBA) {
	C.vehicle_set_primary_color_r_g_b(v.Ptr, C.uint(color.R), C.uint(color.G), C.uint(color.B), C.uint(color.A))
}

func (v Vehicle) SetSecondaryColor(color uint8) {
	C.vehicle_set_secondary_color(v.Ptr, C.uint(color))
}

func (v Vehicle) SetSecondaryColorRGB(color RGBA) {
	C.vehicle_set_secondary_color_r_g_b(v.Ptr, C.uint(color.R), C.uint(color.G), C.uint(color.B), C.uint(color.A))
}

func (v Vehicle) SetPearlColor(color uint8) {
	C.vehicle_set_pearl_color(v.Ptr, C.uint(color))
}

func (v Vehicle) SetWheelColor(color uint8) {
	C.vehicle_set_wheel_color(v.Ptr, C.uint(color))
}

func (v Vehicle) SetInteriorColor(color uint8) {
	C.vehicle_set_interior_color(v.Ptr, C.uint(color))
}

func (v Vehicle) SetDashboardColor(color uint8) {
	C.vehicle_set_dashboard_color(v.Ptr, C.uint(color))
}

func (v Vehicle) SetTireSmokeColor(color RGBA) {
	C.vehicle_set_tire_smoke_color(v.Ptr, C.uint(color.R), C.uint(color.G), C.uint(color.B), C.uint(color.A))
}

func (v Vehicle) SetWheels(wheelType uint8, variation uint8) {
	C.vehicle_set_wheels(v.Ptr, C.uint(wheelType), C.uint(variation))
}

func (v Vehicle) SetRearWheels(variation uint8) {
	C.vehicle_set_rear_wheels(v.Ptr, C.uint(variation))
}

func (v Vehicle) SetCustomTires(state bool) {
	C.vehicle_set_custom_tires(v.Ptr, C.int(module.Bool2int(state)))
}

func (v Vehicle) SetSpecialDarkness(value uint8) {
	C.vehicle_set_special_darkness(v.Ptr, C.uint(value))
}

func (v Vehicle) SetNumberplateIndex(index uint32) {
	C.vehicle_set_numberplate_index(v.Ptr, C.uint(index))
}

func (v Vehicle) SetNumberplateText(text string) {
	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	C.vehicle_set_numberplate_text(v.Ptr, cText)
}

func (v Vehicle) SetWindowTint(tint uint8) {
	C.vehicle_set_window_tint(v.Ptr, C.uint(tint))
}

func (v Vehicle) SetDirtLevel(dirt uint8) {
	C.vehicle_set_dirt_level(v.Ptr, C.uint(dirt))
}

func (v Vehicle) SetNeonActive(front bool, left bool, right bool, back bool) {
	C.vehicle_set_neon_active(v.Ptr, C.int(module.Bool2int(front)), C.int(module.Bool2int(left)), C.int(module.Bool2int(right)), C.int(module.Bool2int(back)))
}

func (v Vehicle) SetNeonColor(color RGBA) {
	C.vehicle_set_neon_color(v.Ptr, C.uint(color.R), C.uint(color.G), C.uint(color.B), C.uint(color.A))
}

func (v Vehicle) SetLivery(livery uint8) {
	C.vehicle_set_livery(v.Ptr, C.uint(livery))
}

func (v Vehicle) SetRoofLivery(roofLivery uint8) {
	C.vehicle_set_roof_livery(v.Ptr, C.uint(roofLivery))
}

func (v Vehicle) SetEngineOn(state bool) {
	C.vehicle_set_engine_on(v.Ptr, C.int(module.Bool2int(state)))
}

func (v Vehicle) SetHeadlightColor(color uint8) {
	C.vehicle_set_headlight_color(v.Ptr, C.uint(color))
}

func (v Vehicle) SetRadioStationIndex(stationIndex uint32) {
	C.vehicle_set_radio_station_index(v.Ptr, C.uint(stationIndex))
}

func (v Vehicle) SetSirenActive(state bool) {
	C.vehicle_set_siren_active(v.Ptr, C.int(module.Bool2int(state)))
}

func (v Vehicle) SetLockState(state uint8) {
	C.vehicle_set_lock_state(v.Ptr, C.uint(state))
}

func (v Vehicle) SetDoorState(doorId uint8, state uint8) {
	C.vehicle_set_door_state(v.Ptr, C.uint(doorId), C.uint(state))
}

func (v Vehicle) SetWindowOpened(windowId uint8, state bool) {
	C.vehicle_set_window_opened(v.Ptr, C.uint(windowId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetRoofState(state uint8) {
	C.vehicle_set_roof_state(v.Ptr, C.uint(state))
}

func (v Vehicle) SetLightsMultiplier(multiplier float32) {
	C.vehicle_set_lights_multiplier(v.Ptr, C.float(multiplier))
}

func (v Vehicle) SetEngineHealth(health int32) {
	C.vehicle_set_engine_health(v.Ptr, C.long(health))
}

func (v Vehicle) SetPetrolTankHealth(health int32) {
	C.vehicle_set_petrol_tank_health(v.Ptr, C.long(health))
}

func (v Vehicle) SetWheelBurst(wheelId uint8, state bool) {
	C.vehicle_set_wheel_burst(v.Ptr, C.uint(wheelId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetWheelHasTire(wheelId uint8, state bool) {
	C.vehicle_set_wheel_has_tire(v.Ptr, C.uint(wheelId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetWheelDetached(wheelId uint8, state bool) {
	C.vehicle_set_wheel_detached(v.Ptr, C.uint(wheelId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetWheelOnFire(wheelId uint8, state bool) {
	C.vehicle_set_wheel_on_fire(v.Ptr, C.uint(wheelId), C.int(module.Bool2int(state)))
}

func (v Vehicle) SetWheelHealth(wheelId uint8, health float32) {
	C.vehicle_set_wheel_health(v.Ptr, C.uint(wheelId), C.float(health))
}

func (v Vehicle) SetWheelFixed(wheelId uint8) {
	C.vehicle_set_wheel_fixed(v.Ptr, C.uint(wheelId))
}

func (v Vehicle) SetBodyHealth(health uint32) {
	C.vehicle_set_body_health(v.Ptr, C.ulong(health))
}

func (v Vehicle) SetBodyAdditionalHealth(health uint32) {
	C.vehicle_set_body_additional_health(v.Ptr, C.ulong(health))
}

func (v Vehicle) SetPartDamageLevel(partId uint8, damage uint8) {
	C.vehicle_set_part_damage_level(v.Ptr, C.uint(partId), C.uint(damage))
}

func (v Vehicle) SetPartBulletHoles(partId uint8, shootsCount uint8) {
	C.vehicle_set_part_bullet_holes(v.Ptr, C.uint(partId), C.uint(shootsCount))
}

func (v Vehicle) SetLightDamaged(lightId uint8, isDamaged bool) {
	C.vehicle_set_light_damaged(v.Ptr, C.uint(lightId), C.int(module.Bool2int(isDamaged)))
}

func (v Vehicle) SetWindowDamaged(windowId uint8, isDamaged bool) {
	C.vehicle_set_window_damaged(v.Ptr, C.uint(windowId), C.int(module.Bool2int(isDamaged)))
}

func (v Vehicle) SetSpecialLightDamaged(specialLightId uint8, isDamaged bool) {
	C.vehicle_set_special_light_damaged(v.Ptr, C.uint(specialLightId), C.int(module.Bool2int(isDamaged)))
}

func (v Vehicle) SetArmoredWindowHealth(windowId uint8, health float32) {
	C.vehicle_set_armored_window_health(v.Ptr, C.uint(windowId), C.float(health))
}

func (v Vehicle) SetArmoredWindowShootCount(windowId uint8, count uint8) {
	C.vehicle_set_armored_window_shoot_count(v.Ptr, C.uint(windowId), C.uint(count))
}

func (v Vehicle) SetBumperDamageLevel(bumperId uint8, damageLevel uint8) {
	C.vehicle_set_bumper_damage_level(v.Ptr, C.uint(bumperId), C.uint(damageLevel))
}

func (v Vehicle) SetManualEngineControl(state bool) {
	C.vehicle_set_manual_engine_control(v.Ptr, C.int(module.Bool2int(state)))
}

func (v Vehicle) Attached() *Vehicle {
	ptr := C.vehicle_get_attached(v.Ptr)
	if ptr == nil {
		return nil
	}
	return NewVehicle(ptr)
}

func (v Vehicle) AttachedTo() *Vehicle {
	ptr := C.vehicle_get_attached_to(v.Ptr)
	if ptr == nil {
		return nil
	}
	return NewVehicle(ptr)
}
