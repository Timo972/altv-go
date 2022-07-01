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

type VoiceChannel struct {
	BaseObject
}

func newVoiceChannel(v unsafe.Pointer) *VoiceChannel {
	voiceChannel := &VoiceChannel{}
	voiceChannel.ptr = v
	voiceChannel.Type = VoiceChannelObject
	return voiceChannel
}

func CreateVoiceChannel(spatial bool, maxDistance float32) *VoiceChannel {
	voiceChannel := &VoiceChannel{}
	voiceChannel.ptr = C.core_create_voice_channel(C.int(module.Bool2int(spatial)), C.float(maxDistance))
	voiceChannel.Type = VoiceChannelObject
	return voiceChannel
}

func (v VoiceChannel) String() string {
	return fmt.Sprintf("VoiceChannel{}")
}

func (v VoiceChannel) IsSpatial() bool {
	return int(C.voice_channel_is_spatial(v.ptr)) == 1
}

func (v VoiceChannel) MaxDistance() float32 {
	return float32(C.voice_channel_get_max_distance(v.ptr))
}

func (v VoiceChannel) HasPlayer(player *Player) bool {
	return int(C.voice_channel_has_player(v.ptr, player.ptr)) == 1
}

func (v VoiceChannel) AddPlayer(player *Player) {
	C.voice_channel_add_player(v.ptr, player.ptr)
}

func (v VoiceChannel) RemovePlayer(player *Player) {
	C.voice_channel_remove_player(v.ptr, player.ptr)
}

func (v VoiceChannel) IsPlayerMuted(player *Player) bool {
	return int(C.voice_channel_is_player_muted(v.ptr, player.ptr)) == 1
}

func (v VoiceChannel) MutePlayer(player *Player) {
	C.voice_channel_mute_player(v.ptr, player.ptr)
}

func (v VoiceChannel) UnmutePlayer(player *Player) {
	C.voice_channel_unmute_player(v.ptr, player.ptr)
}

func (v VoiceChannel) PlayerCount() uint64 {
	return uint64(C.voice_channel_get_player_count(v.ptr))
}

func (v VoiceChannel) Players() []*Player {
	arr := C.voice_channel_get_players(v.ptr)

	return newPlayerArray(arr)
}
