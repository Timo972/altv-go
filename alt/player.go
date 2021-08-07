package alt

// #cgo LDFLAGS: -ldl
// #include <stdlib.h>
// #include "Module.h"
import "C"
import "unsafe"

type Player struct {
	BaseObject
	WorldObject
	Ptr unsafe.Pointer
}

func NewPlayer(p unsafe.Pointer) *Player {
	return &Player{Ptr: p}
}

func (p Player) Name() string {
	str := C.player_get_name(p.Ptr)

	return C.GoString(str)
}
