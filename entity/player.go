package entity

// #include "capi.h"
import "C"
import (
	"unsafe"
)

type Player interface {
	Entity
	DiscordUserID() int64
	SocialID() uint64
	Health() uint16
	Spawn(x float64, y float64, z float64, delayMs uint)
}

type AltPlayer struct {
	AltEntity
}

func NewPlayer(ptr unsafe.Pointer, id uint32) Player {
	return &AltPlayer{
		AltEntity{
			AltWorldObject{
				AltBaseObject: newBaseObject(TypePlayer, ptr, id),
			},
		},
	}
}

/*func EmptyPlayer() Player {
	return &player{}
}*/

func (p *AltPlayer) SocialID() uint64 {
	return uint64(C.player_get_social_i_d(p.ptr))
}

func (p *AltPlayer) DiscordUserID() int64 {
	return int64(C.player_get_discord_id(p.ptr))
}

func (p *AltPlayer) Health() uint16 {
	return uint16(C.player_get_health(p.ptr))
}

func (p *AltPlayer) Spawn(x float64, y float64, z float64, delayMs uint) {
	C.player_spawn(p.ptr, C.float(x), C.float(y), C.float(z), C.ulong(delayMs))
}
