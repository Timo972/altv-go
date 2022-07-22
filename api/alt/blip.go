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
	"fmt"
	"unsafe"

	"github.com/timo972/altv-go/internal/module"
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
	blip.ptr = b
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
	return int(C.blip_is_global(b.ptr)) == 1
}

func (b Blip) Target() *Player {
	return newPlayer(C.blip_get_target(b.ptr))
}

func (b Blip) IsAttached() bool {
	return int(C.blip_is_attached(b.ptr)) == 1
}

func (b Blip) AttachedTo() *Entity {
	//return newEntity(C.blip_attached_to(b.ptr))
	return nil
}

func (b Blip) AttachTo(entity *Entity) {
	C.blip_attach_to(b.ptr, newCEntity(entity))
}

func (b Blip) BlipType() BlipType {
	return BlipType(C.blip_get_blip_type(b.ptr))
}

func (b Blip) Scale() Vector2 {
	return newVector2(C.blip_get_scale_x_y(b.ptr))
}

func (b Blip) SetScale(v Vector2) {
	C.blip_set_scale_x_y(b.ptr, newCVector2(v))
}

func (b Blip) Display() bool {
	return int(C.blip_get_display(b.ptr)) == 1
}

func (b Blip) SetDisplay(display bool) {
	C.blip_set_display(b.ptr, C.int(module.Bool2int(display)))
}

func (b Blip) Sprite() int32 {
	return int32(C.blip_get_sprite(b.ptr))
}

func (b Blip) SetSprite(sprite int32) {
	C.blip_set_sprite(b.ptr, C.int(sprite))
}

func (b Blip) Color() int32 {
	return int32(C.blip_get_color(b.ptr))
}

func (b Blip) SetColor(color int32) {
	C.blip_set_color(b.ptr, C.int(color))
}

func (b Blip) SecondaryColor() RGBA {
	return newRGBA(C.blip_get_secondary_color(b.ptr))
}

func (b Blip) Alpha() int32 {
	return int32(C.blip_get_alpha(b.ptr))
}

func (b Blip) FlashTimer() int32 {
	return int32(C.blip_get_flash_timer(b.ptr))
}

func (b Blip) FlashInterval() int32 {
	return int32(C.blip_get_flash_interval(b.ptr))
}

func (b Blip) Friendly() bool {
	return int(C.blip_get_as_friendly(b.ptr)) == 1
}

func (b Blip) Route() bool {
	return int(C.blip_get_route(b.ptr)) == 1
}

func (b Blip) Bright() bool {
	return int(C.blip_get_bright(b.ptr)) == 1
}

func (b Blip) Number() int32 {
	return int32(C.blip_get_number(b.ptr))
}

func (b Blip) ShowCone() bool {
	return int(C.blip_get_show_cone(b.ptr)) == 1
}

func (b Blip) Flashes() bool {
	return int(C.blip_get_flashes(b.ptr)) == 1
}

func (b Blip) FlashesAlternate() bool {
	return int(C.blip_get_flashes_alternate(b.ptr)) == 1
}

func (b Blip) ShortRange() bool {
	return int(C.blip_get_as_short_range(b.ptr)) == 1
}

func (b Blip) Priority() int32 {
	return int32(C.blip_get_priority(b.ptr))
}

func (b Blip) Rotation() float32 {
	return float32(C.blip_get_rotation(b.ptr))
}

func (b Blip) GxtName() string {
	return C.GoString(C.blip_get_gxt_name(b.ptr))
}

func (b Blip) Name() string {
	return C.GoString(C.blip_get_name(b.ptr))
}

func (b Blip) RouteColor() RGBA {
	return newRGBA(C.blip_get_route_color(b.ptr))
}

func (b Blip) Pulse() bool {
	return int(C.blip_get_pulse(b.ptr)) == 1
}

func (b Blip) MissionCreator() bool {
	return int(C.blip_get_as_mission_creator(b.ptr)) == 1
}

func (b Blip) TickVisible() bool {
	return int(C.blip_get_tick_visible(b.ptr)) == 1
}

func (b Blip) HeadingIndicatorVisible() bool {
	return int(C.blip_get_heading_indicator_visible(b.ptr)) == 1
}

func (b Blip) OutlineIndicatorVisible() bool {
	return int(C.blip_get_outline_indicator_visible(b.ptr)) == 1
}

func (b Blip) FriendIndicatorVisible() bool {
	return int(C.blip_get_friend_indicator_visible(b.ptr)) == 1
}

func (b Blip) CrewIndicatorVisible() bool {
	return int(C.blip_get_crew_indicator_visible(b.ptr)) == 1
}

func (b Blip) Category() int32 {
	return int32(C.blip_get_category(b.ptr))
}

func (b Blip) HighDetail() bool {
	return int(C.blip_get_as_high_detail(b.ptr)) == 1
}

func (b Blip) Shrinked() bool {
	return int(C.blip_get_shrinked(b.ptr)) == 1
}

func (b Blip) SetRoute(state bool) {
	C.blip_set_route(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetRouteColor(color RGBA) {
	C.blip_set_route_color(b.ptr, newCRGBA(color))
}

func (b Blip) SetSecondaryColor(color RGBA) {
	C.blip_set_secondary_color(b.ptr, newCRGBA(color))
}

func (b Blip) SetAlpha(color int32) {
	C.blip_set_alpha(b.ptr, C.int(color))
}

func (b Blip) SetFlashTimer(timer int32) {
	C.blip_set_flash_timer(b.ptr, C.int(timer))
}

func (b Blip) SetFlashInterval(interval int32) {
	C.blip_set_flash_interval(b.ptr, C.int(interval))
}

func (b Blip) SetFriendly(state bool) {
	C.blip_set_as_friendly(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetBright(state bool) {
	C.blip_set_bright(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetNumber(number int32) {
	C.blip_set_number(b.ptr, C.int(number))
}

func (b Blip) SetShowCone(state bool) {
	C.blip_set_show_cone(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetFlashes(state bool) {
	C.blip_set_flashes(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetFlashesAlternate(state bool) {
	C.blip_set_flashes_alternate(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetShortRange(state bool) {
	C.blip_set_as_short_range(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetPriority(priority int32) {
	C.blip_set_priority(b.ptr, C.int(priority))
}

func (b Blip) SetRotation(rot float32) {
	C.blip_set_rotation(b.ptr, C.float(rot))
}

func (b Blip) SetGxtName(name string) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	C.blip_set_gxt_name(b.ptr, cName)
}

func (b Blip) SetName(name string) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	C.blip_set_name(b.ptr, cName)
}

func (b Blip) SetPulse(state bool) {
	C.blip_set_pulse(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetMissionCreator(state bool) {
	C.blip_set_as_mission_creator(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetTickVisible(state bool) {
	C.blip_set_tick_visible(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetHeadingIndicatorVisible(state bool) {
	C.blip_set_heading_indicator_visible(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetOutlineIndicatorVisible(state bool) {
	C.blip_set_outline_indicator_visible(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetFriendIndicatorVisible(state bool) {
	C.blip_set_friend_indicator_visible(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetCrewIndicatorVisible(state bool) {
	C.blip_set_crew_indicator_visible(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetCategory(category int32) {
	C.blip_set_category(b.ptr, C.int(category))
}

func (b Blip) SetHighDetail(state bool) {
	C.blip_set_as_high_detail(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) SetShrinked(state bool) {
	C.blip_set_shrinked(b.ptr, C.int(module.Bool2int(state)))
}

func (b Blip) Fade(opacity uint32, duration uint32) {
	C.blip_fade(b.ptr, C.uint(opacity), C.uint(duration))
}
