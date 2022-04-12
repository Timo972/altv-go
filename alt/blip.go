package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import (
	"fmt"
	"unsafe"

	"github.com/shockdev04/altv-go-pkg/internal/module"
)

type BlipType uint8

const (
	VEHICLE       BlipType = 1
	PED           BlipType = 2
	OBJECT        BlipType = 3
	DESTINATION   BlipType = 4
	CONT          BlipType = 5
	PICKUP_UNK    BlipType = 6
	RADIUS        BlipType = 7
	PICKUP        BlipType = 8
	COP           BlipType = 9
	AREA          BlipType = 11
	GALLERY       BlipType = 12
	PICKUP_OBJECT BlipType = 13
)

type Blip struct {
	WorldObject
}

func newBlip(b unsafe.Pointer) *Blip {
	blip := &Blip{}
	blip.Ptr = b
	blip.Type = BlipObject
	return blip
}

func CreatePointBlip(x float32, y float32, z float32) *Blip {
	return newBlip(C.core_create_point_blip_position(C.float(x), C.float(y), C.float(z)))
}
func CreateEntityBlip(entity IEntity) *Blip {
	return newBlip(C.core_create_point_blip_entity(newCEntity(entity)))
}

func CreateRadiusBlip(x float32, y float32, z float32, radius float32) *Blip {
	return newBlip(C.core_create_radius_blip(C.float(x), C.float(y), C.float(z), C.float(radius)))
}

func CreateAreaBlip(x float32, y float32, z float32, width float32, height float32) *Blip {
	return newBlip(C.core_create_area_blip(C.float(x), C.float(y), C.float(z), C.float(width), C.float(height)))
}

func (b Blip) String() string {
	return fmt.Sprintf("Blip{}")
}

func (b Blip) IsGlobal() bool {
	return int(C.blip_is_global(b.Ptr)) == 1
}

func (b Blip) Target() *Player {
	return newPlayer(C.blip_get_target(b.Ptr))
}

func (b Blip) IsAttached() bool {
	return int(C.blip_is_attached(b.Ptr)) == 1
}

func (b Blip) AttachedTo() *Entity {
	return newEntity(C.blip_attached_to(b.Ptr))
}

func (b Blip) AttachTo(entity *Entity) {
	C.blip_attach_to(b.Ptr, newCEntity(entity))
}

func (b Blip) BlipType() BlipType {
	return BlipType(C.blip_get_blip_type(b.Ptr))
}

func (b Blip) Scale() Vector2 {
	return newVector2(C.blip_get_scale_xy(b.Ptr))
}

func (b Blip) SetScale(x float32, y float32) {
	C.blip_set_scale_xy(b.Ptr, C.float(x), C.float(y))
}

func (b Blip) Display() bool {
	return int(C.blip_get_display(b.Ptr)) == 1
}

func (b Blip) SetDisplay(display bool) {
	C.blip_set_display(b.Ptr, C.int(module.Bool2int(display)))
}

func (b Blip) Sprite() int32 {
	return int32(C.blip_get_sprite(b.Ptr))
}

func (b Blip) SetSprite(sprite int32) {
	C.blip_set_sprite(b.Ptr, C.int(sprite))
}

func (b Blip) Color() int32 {
	return int32(C.blip_get_color(b.Ptr))
}

func (b Blip) SetColor(color int32) {
	C.blip_set_color(b.Ptr, C.int(color))
}

func (b Blip) SecondaryColor() RGBA {
	return newRGBA(C.blip_get_secondary_color(b.Ptr))
}

func (b Blip) Alpha() int32 {
	return int32(C.blip_get_alpha(b.Ptr))
}

func (b Blip) FlashTimer() int32 {
	return int32(C.blip_get_flash_timer(b.Ptr))
}

func (b Blip) FlashInterval() int32 {
	return int32(C.blip_get_flash_interval(b.Ptr))
}

func (b Blip) Friendly() bool {
	return int(C.blip_get_as_friendly(b.Ptr)) == 1
}

func (b Blip) Route() bool {
	return int(C.blip_get_route(b.Ptr)) == 1
}

func (b Blip) Bright() bool {
	return int(C.blip_get_bright(b.Ptr)) == 1
}

func (b Blip) Number() int32 {
	return int32(C.blip_get_number(b.Ptr))
}

func (b Blip) ShowCone() bool {
	return int(C.blip_get_show_cone(b.Ptr)) == 1
}

func (b Blip) Flashes() bool {
	return int(C.blip_get_flashes(b.Ptr)) == 1
}

func (b Blip) FlashesAlternate() bool {
	return int(C.blip_get_flashes_alternate(b.Ptr)) == 1
}

func (b Blip) ShortRange() bool {
	return int(C.blip_get_as_short_range(b.Ptr)) == 1
}

func (b Blip) Priority() int32 {
	return int32(C.blip_get_priority(b.Ptr))
}

func (b Blip) Rotation() float32 {
	return float32(C.blip_get_rotation(b.Ptr))
}

func (b Blip) GxtName() string {
	return C.GoString(C.blip_get_gxt_name(b.Ptr))
}

func (b Blip) Name() string {
	return C.GoString(C.blip_get_name(b.Ptr))
}

func (b Blip) RouteColor() RGBA {
	return newRGBA(C.blip_get_route_color(b.Ptr))
}

func (b Blip) Pulse() bool {
	return int(C.blip_get_pulse(b.Ptr)) == 1
}

func (b Blip) MissionCreator() bool {
	return int(C.blip_get_as_mission_creator(b.Ptr)) == 1
}

func (b Blip) TickVisible() bool {
	return int(C.blip_get_tick_visible(b.Ptr)) == 1
}

func (b Blip) HeadingIndicatorVisible() bool {
	return int(C.blip_get_heading_indicator_visible(b.Ptr)) == 1
}

func (b Blip) OutlineIndicatorVisible() bool {
	return int(C.blip_get_outline_indicator_visible(b.Ptr)) == 1
}

func (b Blip) FriendIndicatorVisible() bool {
	return int(C.blip_get_friend_indicator_visible(b.Ptr)) == 1
}

func (b Blip) CrewIndicatorVisible() bool {
	return int(C.blip_get_crew_indicator_visible(b.Ptr)) == 1
}

func (b Blip) Category() int32 {
	return int32(C.blip_get_category(b.Ptr))
}

func (b Blip) HighDetail() bool {
	return int(C.blip_get_as_high_detail(b.Ptr)) == 1
}

func (b Blip) Shrinked() bool {
	return int(C.blip_get_shrinked(b.Ptr)) == 1
}

func (b Blip) SetRoute(state bool) {
	C.blip_set_route(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetRouteColor(color RGBA) {
	C.blip_set_route_color(b.Ptr, newCRGBA(color))
}

func (b Blip) SetSecondaryColor(color RGBA) {
	C.blip_set_secondary_color(b.Ptr, newCRGBA(color))
}

func (b Blip) SetAlpha(color int32) {
	C.blip_set_alpha(b.Ptr, C.int(color))
}

func (b Blip) SetFlashTimer(timer int32) {
	C.blip_set_flash_timer(b.Ptr, C.int(timer))
}

func (b Blip) SetFlashInterval(interval int32) {
	C.blip_set_flash_interval(b.Ptr, C.int(interval))
}

func (b Blip) SetFriendly(state bool) {
	C.blip_set_as_friendly(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetBright(state bool) {
	C.blip_set_bright(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetNumber(number int32) {
	C.blip_set_number(b.Ptr, C.int(number))
}

func (b Blip) SetShowCone(state bool) {
	C.blip_set_show_cone(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetFlashes(state bool) {
	C.blip_set_flashes(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetFlashesAlternate(state bool) {
	C.blip_set_flashes_alternate(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetShortRange(state bool) {
	C.blip_set_as_short_range(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetPriority(priority int32) {
	C.blip_set_priority(b.Ptr, C.int(priority))
}

func (b Blip) SetRotation(rot float32) {
	C.blip_set_rotation(b.Ptr, C.float(rot))
}

func (b Blip) SetGxtName(name string) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	C.blip_set_gxt_name(b.Ptr, cName)
}

func (b Blip) SetName(name string) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	C.blip_set_name(b.Ptr, cName)
}

func (b Blip) SetPulse(state bool) {
	C.blip_set_pulse(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetMissionCreator(state bool) {
	C.blip_set_as_mission_creator(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetTickVisible(state bool) {
	C.blip_set_tick_visible(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetHeadingIndicatorVisible(state bool) {
	C.blip_set_heading_indicator_visible(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetOutlineIndicatorVisible(state bool) {
	C.blip_set_outline_indicator_visible(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetFriendIndicatorVisible(state bool) {
	C.blip_set_friend_indicator_visible(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetCrewIndicatorVisible(state bool) {
	C.blip_set_crew_indicator_visible(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetCategory(category int32) {
	C.blip_set_category(b.Ptr, C.int(category))
}

func (b Blip) SetHighDetail(state bool) {
	C.blip_set_as_high_detail(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetShrinked(state bool) {
	C.blip_set_shrinked(b.Ptr, C.int(module.Bool2int(state)))
}

func (b Blip) Fade(opacity uint32, duration uint32) {
	C.blip_fade(b.Ptr, C.uint(opacity), C.uint(duration))
}
