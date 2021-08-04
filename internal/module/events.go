package module

import "C"
import (
	"github.com/shockdev04/altv-go-pkg/alt"
	"unsafe"
)

//export altPlayerConnectEvent
func altPlayerConnectEvent(player unsafe.Pointer) {
	for _, event := range alt.On.PlayerConnectEvents {
		player := NewPlayer(player)

		event(player)
	}
}