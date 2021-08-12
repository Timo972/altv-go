package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import "unsafe"

type Player struct {
	Entity
	model uint32
}

func NewPlayer(p unsafe.Pointer) *Player {
	player := &Player{}
	player.Ptr = p
	player.Type = PlayerObject

	return player
}

func (p Player) Name() string {
	return C.GoString(C.player_get_name(p.Ptr))
}

func (p Player) Model() uint32 {
	return p.model
}

func (p Player) SetModel(model uint32) {
	C.player_set_model(p.Ptr, C.ulong(model))
}

func (p Player) Spawn(pos Position, delayMs uint32) {
	C.player_spawn(p.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z), C.ulong(delayMs))
}
