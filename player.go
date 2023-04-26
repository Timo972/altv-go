package altv

import "C"
import (
	"unsafe"
)

type Player interface {
	Entity
}

type player struct {
	entity
}

func NewPlayer(ptr unsafe.Pointer, id uint32) Player {
	p := &player{
		entity{
			worldObject{
				baseObject{
					ptr: ptr,
					id:  id,
					typ: BaseTypePlayer,
				},
			},
		},
	}

	return p
}

func PlayerByID(id uint32) (Player, error) {
	return GetBaseObject[Player](C.core_get_entity_by_i_d(C.uint(id)))
}
