package altv

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
}

type player struct {
	entity
}

func NewPlayer(ptr unsafe.Pointer, id uint32) Player {
	p := &player{
		entity{
			worldObject{
				baseObject: newBaseObject(BaseTypePlayer, ptr, id),
			},
		},
	}

	return p
}

/*func EmptyPlayer() Player {
	return &player{}
}*/

func Players() []Player {
	arr := C.core_get_players()
	return newBaseObjectArray[Player](arr)
}

func PlayerByID(id uint32) (Player, error) {
	return getBaseObject[Player](C.core_get_base_object_by_i_d(C.uchar(BaseTypePlayer), C.uint(id)))
}

func (p *player) SocialID() uint64 {
	return uint64(C.player_get_social_i_d(p.ptr))
}

func (p *player) DiscordUserID() int64 {
	return int64(C.player_get_discord_id(p.ptr))
}

func (p *player) Health() uint16 {
	return uint16(C.player_get_health(p.ptr))
}
