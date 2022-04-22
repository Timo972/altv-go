package alt

// #cgo CFLAGS: -I../c-api/build/Release
// #cgo LDFLAGS: -L../c-api/build/Release -lcapi
// #include <stdlib.h>
// #include "../c-api/capi.h"
import "C"
import (
	"fmt"
	"unsafe"

	"github.com/timo972/altv-go-pkg/internal/module"
)

type Player struct {
	Entity
}

func newPlayer(p unsafe.Pointer) *Player {
	player := &Player{}
	player.Ptr = p
	player.Type = PlayerObject

	return player
}

func newPlayerArray(arr C.struct_array) []*Player {
	values, size := convertArray[unsafe.Pointer](arr)

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
	return C.GoString(C.player_get_name(p.Ptr))
}

func (p Player) SetModel(model uint32) {
	C.player_set_model(p.Ptr, C.ulong(model))
}

func (p Player) Spawn(pos Vector3, delayMs uint32) {
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
	cComponentsStruct := C.player_get_current_weapon_components(p.Ptr)
	cComponents, size := convertArray[C.uint](cComponentsStruct)

	comps := make([]uint32, size)
	for i, comp := range cComponents {
		comps[i] = uint32(comp)
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

func (p Player) AimPos() Vector3 {
	cPos := C.player_get_aim_pos(p.Ptr)
	return Vector3{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
}

func (p Player) HeadRotation() Vector3 {
	cRot := C.player_get_head_rotation(p.Ptr)
	return Vector3{X: float32(cRot.roll), Y: float32(cRot.pitch), Z: float32(cRot.yaw)}
}

func (p Player) IsInVehicle() bool {
	return int(C.player_is_in_vehicle(p.Ptr)) == 1
}

func (p Player) Vehicle() *Vehicle {
	cPtr := C.player_get_vehicle(p.Ptr)
	if cPtr == nil {
		return nil
	}
	veh := newVehicle(unsafe.Pointer(cPtr))
	return veh
}

func (p Player) Seat() uint8 {
	return uint8(C.player_get_seat(p.Ptr))
}

func (p Player) EntityAimingAt() *Entity {
	return newEntity(C.player_get_entity_aiming_at(p.Ptr))
}

func (p Player) EntityAimOffset() Vector3 {
	cPos := C.player_get_entity_aim_offset(p.Ptr)
	return Vector3{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
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
	return C.GoString(C.player_get_i_p(p.Ptr))
}

func (p Player) SocialID() uint64 {
	return uint64(C.player_get_social_i_d(p.Ptr))
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

func (p Player) IsEntityInStreamingRange(entity IEntity) bool {
	return int(C.player_is_entity_in_streaming_range(p.Ptr, newCEntity(entity))) == 1
}

func (p Player) MaxHealth() uint16 {
	return uint16(C.player_get_max_health(p.Ptr))
}

func (p Player) MaxArmour() uint16 {
	return uint16(C.player_get_max_armour(p.Ptr))
}

func (p *Player) Emit(eventName string, args ...interface{}) {
	EmitClient(p, eventName, args...)
}

func (p Player) Invincible() bool {
	return int(C.player_get_invincible(p.Ptr)) == 1
}

func (p Player) SetInvincible(toggle bool) {
	C.player_set_invincible(p.Ptr, C.int(module.Bool2int(toggle)))
}

func (p Player) SetIntoVehicle(v *Vehicle, seat uint8) {
	C.player_set_into_vehicle(p.Ptr, v.Ptr, C.uchar(seat))
}

func (p Player) PlayAmbientSpeech(speechName string, speechParam string, speechDictHash uint32) {
	cSpeechName := C.CString(speechName)
	defer C.free(unsafe.Pointer(cSpeechName))

	cSpeechParam := C.CString(speechParam)
	defer C.free(unsafe.Pointer(cSpeechParam))

	C.player_play_ambient_speech(p.Ptr, cSpeechName, cSpeechParam, C.uint(speechDictHash))
}

func (p Player) SetHeadOverlay(overlayID uint8, index uint8, opacity float32) bool {
	return int(C.player_set_head_overlay(p.Ptr, C.uchar(overlayID), C.uchar(index), C.float(opacity))) == 1
}

func (p Player) RemoveHeadOverlay(overlayID uint8) bool {
	return int(C.player_remove_head_overlay(p.Ptr, C.uchar(overlayID))) == 1
}

func (p Player) SetHeadOverlayColor(overlayID uint8, colorType uint8, colorIndex uint8, secondColorIndex uint8) bool {
	return int(C.player_set_head_overlay_color(p.Ptr, C.uchar(overlayID), C.uchar(colorType), C.uchar(colorIndex), C.uchar(secondColorIndex))) == 1
}

func (p Player) HeadOverlay(overlayID uint8) HeadOverlay {
	return newHeadOverlay(C.player_get_head_overlay(p.Ptr, C.uchar(overlayID)))
}

func (p Player) SetFaceFeature(index uint8, scale float32) bool {
	return int(C.player_set_face_feature(p.Ptr, C.uchar(index), C.float(scale))) == 1
}

func (p Player) FaceFeatureScale(index uint8) float32 {
	return float32(C.player_get_face_feature_scale(p.Ptr, C.uchar(index)))
}

func (p Player) RemoveFaceFeature(index uint8) bool {
	return int(C.player_remove_face_feature(p.Ptr, C.uchar(index))) == 1
}

func (p Player) SetHeadBlendPaletteColor(id uint8, r uint8, g uint8, b uint8) bool {
	return int(C.player_set_head_blend_palette_color(p.Ptr, C.uchar(id), C.uchar(r), C.uchar(g), C.uchar(b))) == 1
}

func (p Player) SetHeadBlendPaletteColorRGBA(id uint8, color RGBA) bool {
	return int(C.player_set_head_blend_palette_color(p.Ptr, C.uchar(id), C.uchar(color.R), C.uchar(color.G), C.uchar(color.B))) == 1
}

func (p Player) HeadBlendPaletteColor(id uint8) RGBA {
	return newRGBA(C.player_get_head_blend_palette_color(p.Ptr, C.uchar(id)))
}

func (p Player) SetHeadBlendData(shapeFirstID uint32, shapeSecondID uint32, shapeThirdID uint32, skinFirstID uint32, skinSecondID uint32, skinThirdID uint32, shapeMix float32, skinMix float32, thirdMix float32) {
	C.player_set_head_blend_data(p.Ptr, C.uint(shapeFirstID), C.uint(shapeSecondID), C.uint(shapeThirdID), C.uint(skinFirstID), C.uint(skinSecondID), C.uint(skinThirdID), C.float(shapeMix), C.float(skinMix), C.float(thirdMix))
}

func (p Player) HeadBlendData() HeadBlendData {
	return newHeadBlendData(C.player_get_head_blend_data(p.Ptr))
}

func (p Player) SetEyeColor(color int16) bool {
	return int(C.player_set_eye_color(p.Ptr, C.short(color))) == 1
}

func (p Player) EyeColor() int16 {
	return int16(C.player_get_eye_color(p.Ptr))
}

func (p Player) SetHairColor(color uint8) {
	C.player_set_hair_color(p.Ptr, C.uchar(color))
}

func (p Player) HairColor() uint8 {
	return uint8(C.player_get_hair_color(p.Ptr))
}

func (p Player) SetHairHighlightColor(color uint8) {
	C.player_set_hair_highlight_color(p.Ptr, C.uchar(color))
}

func (p Player) HairHighlightColor() uint8 {
	return uint8(C.player_get_hair_highlight_color(p.Ptr))
}

func (p Player) Weapons() []Weapon {
	cWeapons := C.player_get_weapons(p.Ptr)
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
	return int(C.player_has_local_meta_data(p.Ptr, cKey)) == 1
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

	C.player_set_local_meta_data(p.Ptr, cKey, bytes, arr.size)

	return true
}

func (p Player) LocalMetaData(key string, value interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	cMeta := C.player_get_local_meta_data(p.Ptr, cKey)
	err := decode(cMeta, value)
	if err != nil {
		return false
	}

	return true
}

func (p Player) DeleteLocalMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	C.player_delete_local_meta_data(p.Ptr, cKey)
}
