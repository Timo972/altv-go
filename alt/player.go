package alt

import (
	"unsafe"
)

type Player struct {
	Ptr		unsafe.Pointer
}

func NewPlayer(p unsafe.Pointer) *Player {
	return &Player{ Ptr: p }
}

func (p Player) Name() string {
	return ""
}
