package module

import (
	alt2 "github.com/shockdev04/altv-go-pkg/alt"
	"unsafe"
)

type internalObject struct {

}

func NewPlayer(p unsafe.Pointer) *alt2.Player {
	return &alt2.Player{ Ptr: p }
}