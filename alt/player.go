package alt

import (
	"unsafe"
)

type Player struct {
	Ptr		unsafe.Pointer
}

func (p Player) Name() string {
	return ""
}
