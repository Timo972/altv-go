package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import "unsafe"

type Player struct {
	Entity
}

func NewPlayer(p unsafe.Pointer) *Player {
	player := &Player{}
	player.Ptr = p

	return player
}

func (p Player) Name() string {
	str := C.player_get_name(p.Ptr)

	return C.GoString(str)
}
