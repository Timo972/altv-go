package alt

// #cgo windows CFLAGS: -I../../c-api/lib/win32
// #cgo windows LDFLAGS: -L../../c-api/lib/win32 -lcapi
// #cgo linux CFLAGS: -I../../c-api/lib/linux
// #cgo linux LDFLAGS: -L../../c-api/lib/linux -lcapi
// #include <stdlib.h>
// #include "../../c-api/build/out/capi.h"
import "C"
import (
	"fmt"
	"unsafe"

	"github.com/timo972/altv-go/internal/module"
)

type Player struct {
	Entity
}

func newPlayer(p unsafe.Pointer) *Player {
	player := &Player{}
	player.ptr = p
	player.Type = PlayerObject

	return player
}

func newPlayerArray(arr C.struct_array) []*Player {
	values, size := convertArray[unsafe.Pointer](arr)
	//defer C.free(unsafe.Pointer(arr.array))

	players := make([]*Player, size)

	if size == 0 {
		return players
	}

	for i := 0; i < size; i++ {
		p := values[i]
		players[i] = newPlayer(p)
	}

	return players
}

func (p Player) String() string {
	return fmt.Sprintf("Player{}")
}

func (p Player) Name() string {
	return C.GoString(C.player_get_name(p.ptr))
}

func (p Player) SetModel(model uint32) {
	C.player_set_model(p.ptr, C.ulong(model))
}

func (p Player) Spawn(pos Vector3, delayMs uint32) {
	C.player_spawn(p.ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z), C.ulong(delayMs))
}

func (p Player) Health() float32 {
	return float32(C.player_get_health(p.ptr))
}

func (p Player) SetHealth(health uint16) {
	C.player_set_health(p.ptr, C.uint(health))
}

func (p Player) HasWeaponComponent(weapon uint32, component uint32) bool {
	return int(C.player_has_weapon_component(p.ptr, C.ulong(weapon), C.ulong(component))) == 1
}

func (p Player) CurrentWeaponComponents() []uint32 {
	cComponentsStruct := C.player_get_current_weapon_components(p.ptr)
	cComponents, size := convertArray[C.uint](cComponentsStruct)

	comps := make([]uint32, size)
	for i, comp := range cComponents {
		comps[i] = uint32(comp)
	}

	return comps
}

func (p Player) WeaponTintIndex(weapon uint32) uint32 {
	return uint32(C.player_get_weapon_tint_index(p.ptr, C.ulong(weapon)))
}

func (p Player) CurrentWeaponTintIndex() uint32 {
	return uint32(C.player_get_current_weapon_tint_index(p.ptr))
}

func (p Player) CurrentWeapon() uint32 {
	return uint32(C.player_get_current_weapon(p.ptr))
}

func (p Player) IsDead() bool {
	return int(C.player_is_dead(p.ptr)) == 1
}

func (p Player) IsJumping() bool {
	return int(C.player_is_jumping(p.ptr)) == 1
}

func (p Player) IsInRagdoll() bool {
	return int(C.player_is_in_ragdoll(p.ptr)) == 1
}

func (p Player) IsAiming() bool {
	return int(C.player_is_aiming(p.ptr)) == 1
}

func (p Player) IsShooting() bool {
	return int(C.player_is_shooting(p.ptr)) == 1
}

func (p Player) IsReloading() bool {
	return int(C.player_is_reloading(p.ptr)) == 1
}

func (p Player) Armour() uint16 {
	return uint16(C.player_get_armour(p.ptr))
}

func (p Player) SetArmour(armour uint16) {
	C.player_set_armour(p.ptr, C.uint(armour))
}

func (p Player) MoveSpeed() float32 {
	return float32(C.player_get_move_speed(p.ptr))
}

func (p Player) AimPos() Vector3 {
	cPos := C.player_get_aim_pos(p.ptr)
	return Vector3{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
}

func (p Player) HeadRotation() Vector3 {
	cRot := C.player_get_head_rotation(p.ptr)
	return Vector3{X: float32(cRot.roll), Y: float32(cRot.pitch), Z: float32(cRot.yaw)}
}

func (p Player) IsInVehicle() bool {
	return int(C.player_is_in_vehicle(p.ptr)) == 1
}

func (p Player) Vehicle() *Vehicle {
	cPtr := C.player_get_vehicle(p.ptr)
	if cPtr == nil {
		return nil
	}
	veh := newVehicle(unsafe.Pointer(cPtr))
	return veh
}

func (p Player) Seat() uint8 {
	return uint8(C.player_get_seat(p.ptr))
}

func (p Player) EntityAimingAt() *Entity {
	return newEntity(C.player_get_entity_aiming_at(p.ptr))
}

func (p Player) EntityAimOffset() Vector3 {
	cPos := C.player_get_entity_aim_offset(p.ptr)
	return Vector3{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
}

func (p Player) IsFlashlightActive() bool {
	return int(C.player_is_flashlight_active(p.ptr)) == 1
}

func (p Player) IsConnected() bool {
	return int(C.player_is_connected(p.ptr)) == 1
}

func (p Player) Ping() uint32 {
	return uint32(C.player_get_ping(p.ptr))
}

func (p Player) IP() string {
	return C.GoString(C.player_get_i_p(p.ptr))
}

func (p Player) SocialID() uint64 {
	return uint64(C.player_get_social_i_d(p.ptr))
}

func (p Player) HwidHash() uint64 {
	return uint64(C.player_get_hwid_hash(p.ptr))
}

func (p Player) HwidExHash() uint64 {
	return uint64(C.player_get_hwid_ex_hash(p.ptr))
}

func (p Player) AuthToken() string {
	return C.GoString(C.player_get_auth_token(p.ptr))
}

func (p Player) SetMaxArmour(maxArmour uint16) {
	C.player_set_max_armour(p.ptr, C.uint(maxArmour))
}

func (p Player) SetCurrentWeapon(weapon uint32) {
	C.player_set_current_weapon(p.ptr, C.ulong(weapon))
}

func (p Player) SetWeaponTintIndex(weapon uint32, tintIndex uint8) {
	C.player_set_weapon_tint_index(p.ptr, C.ulong(weapon), C.uint(tintIndex))
}

func (p Player) AddWeaponComponent(weapon uint32, component uint32) {
	C.player_add_weapon_component(p.ptr, C.ulong(weapon), C.ulong(component))
}

func (p Player) RemoveWeaponComponent(weapon uint32, component uint32) {
	C.player_remove_weapon_component(p.ptr, C.ulong(weapon), C.ulong(component))
}

func (p Player) ClearBloodDamage() {
	C.player_clear_blood_damage(p.ptr)
}

func (p Player) SetMaxHealth(maxHealth uint16) {
	C.player_set_max_health(p.ptr, C.uint(maxHealth))
}

func (p Player) GiveWeapon(weapon uint32, ammo int64, selectWeapon bool) {
	C.player_give_weapon(p.ptr, C.ulong(weapon), C.long(ammo), C.int(module.Bool2int(selectWeapon)))
}

func (p Player) RemoveWeapon(weapon uint32) {
	C.player_remove_weapon(p.ptr, C.ulong(weapon))
}

func (p Player) RemoveAllWeapons() {
	C.player_remove_all_weapons(p.ptr)
}

func (p Player) SetDateTime(day int, month int, year int, hour int, minute int, second int) {
	C.player_set_date_time(p.ptr, C.int(day), C.int(month), C.int(year), C.int(hour), C.int(minute), C.int(second))
}

func (p Player) SetWeather(weather uint32) {
	C.player_set_weather(p.ptr, C.ulong(weather))
}

func (p Player) Kick(reason string) {
	cStr := C.CString(reason)
	defer C.free(unsafe.Pointer(cStr))
	C.player_kick(p.ptr, cStr)
}

func (p Player) Clothes(component uint8) Cloth {
	cCloth := C.player_get_clothes(p.ptr, C.uint(component))
	return Cloth{DrawableId: uint16(cCloth.drawableId), TextureId: uint8(cCloth.textureId), PaletteId: uint8(cCloth.paletteId)}
}

func (p Player) DlcClothes(component uint8) DlcCloth {
	cCloth := C.player_get_dlc_clothes(p.ptr, C.uint(component))
	return DlcCloth{DrawableId: uint16(cCloth.drawableId), TextureId: uint8(cCloth.textureId), PaletteId: uint8(cCloth.paletteId), Dlc: uint32(cCloth.dlc)}
}

func (p Player) Props(component uint8) Prop {
	cCloth := C.player_get_props(p.ptr, C.uint(component))
	return Prop{DrawableId: uint16(cCloth.drawableId), TextureId: uint8(cCloth.textureId)}
}

func (p Player) DlcProps(component uint8) DlcProp {
	cCloth := C.player_get_dlc_props(p.ptr, C.uint(component))
	return DlcProp{DrawableId: uint16(cCloth.drawableId), TextureId: uint8(cCloth.textureId), Dlc: uint32(cCloth.dlc)}
}

func (p Player) SetClothes(component uint8, drawable uint16, texture uint8, palette uint8) {
	C.player_set_clothes(p.ptr, C.uint(component), C.uint(drawable), C.uint(texture), C.uint(palette))
}

func (p Player) SetDlcClothes(component uint8, drawable uint16, texture uint8, palette uint8, dlc uint32) {
	C.player_set_dlc_clothes(p.ptr, C.uint(component), C.uint(drawable), C.uint(texture), C.uint(palette), C.ulong(dlc))
}

func (p Player) SetProps(component uint8, drawable uint16, texture uint8) {
	C.player_set_props(p.ptr, C.uint(component), C.uint(drawable), C.uint(texture))
}

func (p Player) SetDlcProps(component uint8, drawable uint16, texture uint8, dlc uint32) {
	C.player_set_dlc_props(p.ptr, C.uint(component), C.uint(drawable), C.uint(texture), C.ulong(dlc))
}

func (p Player) ClearProps(component uint8) {
	C.player_clear_props(p.ptr, C.uint(component))
}

func (p Player) IsEntityInStreamingRange(entity IEntity) bool {
	return int(C.player_is_entity_in_streaming_range(p.ptr, newCEntity(entity))) == 1
}

func (p Player) MaxHealth() uint16 {
	return uint16(C.player_get_max_health(p.ptr))
}

func (p Player) MaxArmour() uint16 {
	return uint16(C.player_get_max_armour(p.ptr))
}

func (p *Player) Emit(eventName string, args ...interface{}) {
	EmitClient(p, eventName, args...)
}

func (p Player) Invincible() bool {
	return int(C.player_get_invincible(p.ptr)) == 1
}

func (p Player) SetInvincible(toggle bool) {
	C.player_set_invincible(p.ptr, C.int(module.Bool2int(toggle)))
}

func (p Player) SetIntoVehicle(v *Vehicle, seat uint8) {
	C.player_set_into_vehicle(p.ptr, v.ptr, C.uchar(seat))
}

func (p Player) PlayAmbientSpeech(speechName string, speechParam string, speechDictHash uint32) {
	cSpeechName := C.CString(speechName)
	defer C.free(unsafe.Pointer(cSpeechName))

	cSpeechParam := C.CString(speechParam)
	defer C.free(unsafe.Pointer(cSpeechParam))

	C.player_play_ambient_speech(p.ptr, cSpeechName, cSpeechParam, C.uint(speechDictHash))
}

func (p Player) SetHeadOverlay(overlayID uint8, index uint8, opacity float32) bool {
	return int(C.player_set_head_overlay(p.ptr, C.uchar(overlayID), C.uchar(index), C.float(opacity))) == 1
}

func (p Player) RemoveHeadOverlay(overlayID uint8) bool {
	return int(C.player_remove_head_overlay(p.ptr, C.uchar(overlayID))) == 1
}

func (p Player) SetHeadOverlayColor(overlayID uint8, colorType uint8, colorIndex uint8, secondColorIndex uint8) bool {
	return int(C.player_set_head_overlay_color(p.ptr, C.uchar(overlayID), C.uchar(colorType), C.uchar(colorIndex), C.uchar(secondColorIndex))) == 1
}

func (p Player) HeadOverlay(overlayID uint8) HeadOverlay {
	return newHeadOverlay(C.player_get_head_overlay(p.ptr, C.uchar(overlayID)))
}

func (p Player) SetFaceFeature(index uint8, scale float32) bool {
	return int(C.player_set_face_feature(p.ptr, C.uchar(index), C.float(scale))) == 1
}

func (p Player) FaceFeatureScale(index uint8) float32 {
	return float32(C.player_get_face_feature_scale(p.ptr, C.uchar(index)))
}

func (p Player) RemoveFaceFeature(index uint8) bool {
	return int(C.player_remove_face_feature(p.ptr, C.uchar(index))) == 1
}

func (p Player) SetHeadBlendPaletteColor(id uint8, r uint8, g uint8, b uint8) bool {
	return int(C.player_set_head_blend_palette_color(p.ptr, C.uchar(id), C.uchar(r), C.uchar(g), C.uchar(b))) == 1
}

func (p Player) SetHeadBlendPaletteColorRGBA(id uint8, color RGBA) bool {
	return int(C.player_set_head_blend_palette_color(p.ptr, C.uchar(id), C.uchar(color.R), C.uchar(color.G), C.uchar(color.B))) == 1
}

func (p Player) HeadBlendPaletteColor(id uint8) RGBA {
	return newRGBA(C.player_get_head_blend_palette_color(p.ptr, C.uchar(id)))
}

func (p Player) SetHeadBlendData(shapeFirstID uint32, shapeSecondID uint32, shapeThirdID uint32, skinFirstID uint32, skinSecondID uint32, skinThirdID uint32, shapeMix float32, skinMix float32, thirdMix float32) {
	C.player_set_head_blend_data(p.ptr, C.uint(shapeFirstID), C.uint(shapeSecondID), C.uint(shapeThirdID), C.uint(skinFirstID), C.uint(skinSecondID), C.uint(skinThirdID), C.float(shapeMix), C.float(skinMix), C.float(thirdMix))
}

func (p Player) HeadBlendData() HeadBlendData {
	return newHeadBlendData(C.player_get_head_blend_data(p.ptr))
}

func (p Player) SetEyeColor(color int16) bool {
	return int(C.player_set_eye_color(p.ptr, C.short(color))) == 1
}

func (p Player) EyeColor() int16 {
	return int16(C.player_get_eye_color(p.ptr))
}

func (p Player) SetHairColor(color uint8) {
	C.player_set_hair_color(p.ptr, C.uchar(color))
}

func (p Player) HairColor() uint8 {
	return uint8(C.player_get_hair_color(p.ptr))
}

func (p Player) SetHairHighlightColor(color uint8) {
	C.player_set_hair_highlight_color(p.ptr, C.uchar(color))
}

func (p Player) HairHighlightColor() uint8 {
	return uint8(C.player_get_hair_highlight_color(p.ptr))
}

func (p Player) Weapons() []Weapon {
	cWeapons := C.player_get_weapons(p.ptr)
	values, size := convertArray[C.struct_weapon](cWeapons)

	weapons := make([]Weapon, size)

	for i := 0; i < size; i++ {
		weapon := newWeapon(values[i])
		weapons = append(weapons, weapon)
	}

	return weapons
}

func (p Player) HasLocalMetaData(key string) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))
	return int(C.player_has_local_meta_data(p.ptr, cKey)) == 1
}

func (p Player) SetLocalMetaData(key string, value interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	arr, err := encode(value)
	if err != nil {
		return false
	}
	defer C.free(arr.array)

	bytes := (*C.uchar)(arr.array)

	C.player_set_local_meta_data(p.ptr, cKey, bytes, arr.size)

	return true
}

func (p Player) LocalMetaData(key string, value interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	cMeta := C.player_get_local_meta_data(p.ptr, cKey)
	err := decode(cMeta, value)
	if err != nil {
		return false
	}

	return true
}

func (p Player) DeleteLocalMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	C.player_delete_local_meta_data(p.ptr, cKey)
}
