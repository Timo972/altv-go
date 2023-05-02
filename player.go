package altv

// #include "capi.h"
import "C"
import (
	"context"
	"unsafe"
)

type Player interface {
	Entity
	DiscordUserID() int64
	SocialID() uint64
}

type player struct {
	entity
}

func NewPlayer(ptr unsafe.Pointer, id uint32) Player {
	pContext, pCancel := context.WithCancelCause(context.Background())
	p := &player{
		entity{
			worldObject{
				baseObject{
					ptr:        ptr,
					id:         id,
					typ:        BaseTypePlayer,
					ctx:        pContext,
					cancelFunc: pCancel,
				},
			},
		},
	}

	return p
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
