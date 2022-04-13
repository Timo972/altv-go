package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import (
	"fmt"
	"github.com/timo972/altv-go-pkg/internal/module"
	"unsafe"
)

type VoiceChannel struct {
	BaseObject
}

func newVoiceChannel(v unsafe.Pointer) *VoiceChannel {
	voiceChannel := &VoiceChannel{}
	voiceChannel.Ptr = v
	voiceChannel.Type = VoiceChannelObject
	return voiceChannel
}

func CreateVoiceChannel(spatial bool, maxDistance float32) *VoiceChannel {
	voiceChannel := &VoiceChannel{}
	voiceChannel.Ptr = C.core_create_voice_channel(C.int(module.Bool2int(spatial)), C.float(maxDistance))
	voiceChannel.Type = VoiceChannelObject
	return voiceChannel
}

func (v VoiceChannel) String() string {
	return fmt.Sprintf("VoiceChannel{}")
}

func (v VoiceChannel) IsSpatial() bool {
	return int(C.voice_channel_is_spatial(v.Ptr)) == 1
}

func (v VoiceChannel) MaxDistance() float32 {
	return float32(C.voice_channel_get_max_distance(v.Ptr))
}

func (v VoiceChannel) HasPlayer(player *Player) bool {
	return int(C.voice_channel_has_player(v.Ptr, player.Ptr)) == 1
}

func (v VoiceChannel) AddPlayer(player *Player) {
	C.voice_channel_add_player(v.Ptr, player.Ptr)
}

func (v VoiceChannel) RemovePlayer(player *Player) {
	C.voice_channel_remove_player(v.Ptr, player.Ptr)
}

func (v VoiceChannel) IsPlayerMuted(player *Player) bool {
	return int(C.voice_channel_is_player_muted(v.Ptr, player.Ptr)) == 1
}

func (v VoiceChannel) MutePlayer(player *Player) {
	C.voice_channel_mute_player(v.Ptr, player.Ptr)
}

func (v VoiceChannel) UnmutePlayer(player *Player) {
	C.voice_channel_unmute_player(v.Ptr, player.Ptr)
}

func (v VoiceChannel) PlayerCount() uint64 {
	return uint64(C.voice_channel_get_player_count(v.Ptr))
}

func (v VoiceChannel) Players() []*Player {
	arr := C.voice_channel_get_players(v.Ptr)

	return newPlayerArray(arr)
}
