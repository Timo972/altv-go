package alt

// #include <stdlib.h>
import "C"
import (
	"github.com/shockdev04/altv-go-pkg/internal/module"
	"golang.org/x/sys/windows"
	"unsafe"
)

type Player struct {
	Ptr		unsafe.Pointer
}

func NewPlayer(p unsafe.Pointer) *Player {
	return &Player{ Ptr: p }
}

func (p Player) Name() string {
	res, _ := module.GetFunc("Player_GetName")
	return windows.BytePtrToString((*byte)(unsafe.Pointer(res)))
}
