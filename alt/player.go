package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import (
    "unsafe"

    "github.com/shockdev04/altv-go-pkg/internal/module"
)

type Player struct {
	Entity
	model uint32
}

func NewPlayer(p unsafe.Pointer) *Player {
	player := &Player{}
	player.Ptr = p
	player.Type = PlayerObject

	return player
}

func (p Player) Name() string {
	return C.GoString(C.player_get_name(p.Ptr))
}

func (p Player) Model() uint32 {
	return p.model
}

func (p Player) SetModel(model uint32) {
	C.player_set_model(p.Ptr, C.ulong(model))
	p.model = model
}

func (p Player) Spawn(pos Position, delayMs uint32) {
	C.player_spawn(p.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z), C.ulong(delayMs))
}

func (p Player) Health() float32 {
	return float32(C.player_get_health(p.Ptr))
}

func (p Player) SetHealth(health uint16) {
	C.player_set_health(p.Ptr, C.uint(health))
}

func (p Player) HasWeaponComponent(weapon uint32, component uint32) bool {
	return int(C.player_has_weapon_component(p.Ptr, C.ulong(weapon), C.ulong(component))) == 1
}

func (p Player) CurrentWeaponComponents() []uint32 {
    cArrStruct := C.player_get_current_weapon_components(p.Ptr)
    size := int(cArrStruct.size)

    if size == 0 {
    	return []uint32{}
	}

    var cArr unsafe.Pointer = cArrStruct.array
	cIntArray := (*[1 << 28]C.uint)(cArr)[:size:size]
	comps := make([]uint32, size)
	for i, cInt := range cIntArray {
		comps[i] = uint32(cInt)
	}
	return comps
}

func (p Player) WeaponTintIndex(weapon uint32) uint32 {
	return uint32(C.player_get_weapon_tint_index(p.Ptr, C.ulong(weapon)))
}

func (p Player) CurrentWeaponTintIndex() uint32 {
	return uint32(C.player_get_current_weapon_tint_index(p.Ptr))
}

func (p Player) CurrentWeapon() uint32 {
	return uint32(C.player_get_current_weapon(p.Ptr))
}

func (p Player) IsDead() bool {
	return int(C.player_is_dead(p.Ptr)) == 1
}

func (p Player) IsJumping() bool {
	return int(C.player_is_jumping(p.Ptr)) == 1
}

func (p Player) IsInRagdoll() bool {
	return int(C.player_is_in_ragdoll(p.Ptr)) == 1
}

func (p Player) IsAiming() bool {
	return int(C.player_is_aiming(p.Ptr)) == 1
}

func (p Player) IsShooting() bool {
	return int(C.player_is_shooting(p.Ptr)) == 1
}

func (p Player) IsReloading() bool {
	return int(C.player_is_reloading(p.Ptr)) == 1
}

func (p Player) Armour() uint16 {
	return uint16(C.player_get_armour(p.Ptr))
}

func (p Player) SetArmour(armour uint16) {
	C.player_set_armour(p.Ptr, C.uint(armour))
}

func (p Player) MoveSpeed() float32 {
	return float32(C.player_get_move_speed(p.Ptr))
}

func (p Player) AimPos() Position {
	cPos := C.player_get_aim_pos(p.Ptr)
	return Position{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
}

func (p Player) HeadRotation() Rotation {
	cRot := C.player_get_head_rotation(p.Ptr)
	return Rotation{X: float32(cRot.roll), Y: float32(cRot.pitch), Z: float32(cRot.yaw)}
}

func (p Player) IsInVehicle() bool {
	return int(C.player_is_in_vehicle(p.Ptr)) == 1
}

func (p Player) Vehicle() *Vehicle {
	cPtr := C.player_get_vehicle(p.Ptr)
	veh := NewVehicle(unsafe.Pointer(cPtr))
	return veh
}

func (p Player) Seat() uint8 {
	return uint8(C.player_get_seat(p.Ptr))
}

// TODO make proper entity struct
func (p Player) EntityAimingAt() *Entity {
	//cPtr := C.player_get_entity_aiming_at(p.Ptr)
	//entity := &Entity{Ptr:cPtr}
	return nil
}

func (p Player) EntityAimOffset() Position {
	cPos := C.player_get_entity_aim_offset(p.Ptr)
	return Position{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
}

func (p Player) IsFlashlightActive() bool {
	return int(C.player_is_flashlight_active(p.Ptr)) == 1
}

func (p Player) IsConnected() bool {
	return int(C.player_is_connected(p.Ptr)) == 1
}

func (p Player) Ping() uint32 {
	return uint32(C.player_get_ping(p.Ptr))
}

func (p Player) IP() string {
	return C.GoString(C.player_get_ip(p.Ptr))
}

func (p Player) SocialID() uint64 {
	return uint64(C.player_get_social_id(p.Ptr))
}

func (p Player) HwidHash() uint64 {
	return uint64(C.player_get_hwid_hash(p.Ptr))
}

func (p Player) HwidExHash() uint64 {
	return uint64(C.player_get_hwid_ex_hash(p.Ptr))
}

func (p Player) AuthToken() string {
	return C.GoString(C.player_get_auth_token(p.Ptr))
}

func (p Player) SetMaxArmour(maxArmour uint16) {
	C.player_set_max_armour(p.Ptr, C.uint(maxArmour))
}

func (p Player) SetCurrentWeapon(weapon uint32) {
	C.player_set_current_weapon(p.Ptr, C.ulong(weapon))
}

func (p Player) SetWeaponTintIndex(weapon uint32, tintIndex uint8) {
	C.player_set_weapon_tint_index(p.Ptr, C.ulong(weapon), C.uint(tintIndex))
}

func (p Player) AddWeaponComponent(weapon uint32, component uint32) {
	C.player_add_weapon_component(p.Ptr, C.ulong(weapon), C.ulong(component))
}

func (p Player) RemoveWeaponComponent(weapon uint32, component uint32) {
	C.player_remove_weapon_component(p.Ptr, C.ulong(weapon), C.ulong(component))
}

func (p Player) ClearBloodDamage() {
	C.player_clear_blood_damage(p.Ptr)
}

func (p Player) SetMaxHealth(maxHealth uint16) {
	C.player_set_max_health(p.Ptr, C.uint(maxHealth))
}

func (p Player) GiveWeapon(weapon uint32, ammo int64, selectWeapon bool) {
	C.player_give_weapon(p.Ptr, C.ulong(weapon), C.long(ammo), C.int(module.Bool2int(selectWeapon)))
}

func (p Player) RemoveWeapon(weapon uint32) {
	C.player_remove_weapon(p.Ptr, C.ulong(weapon))
}

func (p Player) RemoveAllWeapons() {
	C.player_remove_all_weapons(p.Ptr)
}

func (p Player) SetDateTime(day int, month int, year int, hour int, minute int, second int) {
	C.player_set_date_time(p.Ptr, C.int(day), C.int(month), C.int(year), C.int(hour), C.int(minute), C.int(second))
}

func (p Player) SetWeather(weather uint32) {
	C.player_set_weather(p.Ptr, C.ulong(weather))
}

func (p Player) Kick(reason string) {
	cStr := C.CString(reason)
	defer C.free(unsafe.Pointer(cStr))
	C.player_kick(p.Ptr, cStr)
}

func (p Player) Clothes(component uint8) Cloth {
	cCloth := C.player_get_clothes(p.Ptr, C.uint(component))
	return Cloth{DrawableId: uint16(cCloth.drawableId), TextureId: uint8(cCloth.textureId), PaletteId: uint8(cCloth.paletteId)}
}

func (p Player) DlcClothes(component uint8) DlcCloth {
	cCloth := C.player_get_dlc_clothes(p.Ptr, C.uint(component))
	return DlcCloth{DrawableId: uint16(cCloth.drawableId), TextureId: uint8(cCloth.textureId), PaletteId: uint8(cCloth.paletteId), Dlc: uint32(cCloth.dlc)}
}

func (p Player) Props(component uint8) Prop {
	cCloth := C.player_get_props(p.Ptr, C.uint(component))
	return Prop{DrawableId: uint16(cCloth.drawableId), TextureId: uint8(cCloth.textureId)}
}

func (p Player) DlcProps(component uint8) DlcProp {
	cCloth := C.player_get_dlc_props(p.Ptr, C.uint(component))
	return DlcProp{DrawableId: uint16(cCloth.drawableId), TextureId: uint8(cCloth.textureId), Dlc: uint32(cCloth.dlc)}
}

func (p Player) SetClothes(component uint8, drawable uint16, texture uint8, palette uint8) {
	C.player_set_clothes(p.Ptr, C.uint(component), C.uint(drawable), C.uint(texture), C.uint(palette))
}

func (p Player) SetDlcClothes(component uint8, drawable uint16, texture uint8, palette uint8, dlc uint32) {
	C.player_set_dlc_clothes(p.Ptr, C.uint(component), C.uint(drawable), C.uint(texture), C.uint(palette), C.ulong(dlc))
}

func (p Player) SetProps(component uint8, drawable uint16, texture uint8) {
	C.player_set_props(p.Ptr, C.uint(component), C.uint(drawable), C.uint(texture))
}

func (p Player) SetDlcProps(component uint8, drawable uint16, texture uint8, dlc uint32) {
	C.player_set_dlc_props(p.Ptr, C.uint(component), C.uint(drawable), C.uint(texture), C.ulong(dlc))
}

func (p Player) ClearProps(component uint8) {
	C.player_clear_props(p.Ptr, C.uint(component))
}

func (p Player) IsEntityInStreamingRange(entity Entity) bool {
	return int(C.player_is_entity_in_streaming_range(p.Ptr, entity.Ptr)) == 1
}

func (p Player) MaxHealth() uint16 {
	return uint16(C.player_get_max_health(p.Ptr))
}

func (p Player) MaxArmour() uint16 {
	return uint16(C.player_get_max_armour(p.Ptr))
}