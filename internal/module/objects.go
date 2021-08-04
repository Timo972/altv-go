package module

import (
	alt "github.com/shockdev04/altv-go-pkg/alt/objects"
	"unsafe"
)

type internalObject struct {

}

func NewPlayer(p unsafe.Pointer) *alt.Player {
	return &alt.Player{  }
}