package events

// #include "capi.h"
import "C"
import (
	"fmt"
	"unsafe"

	"github.com/timo972/altv-go"
	"golang.org/x/exp/slices"
)

type playerConnectListener func(p altv.Player)

func (e *subscriber) PlayerConnect(listener playerConnectListener) int {
	e.playerConnectEvents = append(e.playerConnectEvents, listener)
	go registerOnEvent(playerConnect)

	return len(e.playerConnectEvents) - 1
}

func (unsub *unsubscriber) PlayerConnect(id int) error {
	if id < 0 || id >= len(unsub.sub.playerConnectEvents) {
		return ErrInvalidEventID
	}

	unsub.sub.playerConnectEvents = slices.Delete(unsub.sub.playerConnectEvents, id, 1)
	checkPlayerConnect()
	return nil
}

func checkPlayerConnect() {
	lisCount := len(on.playerConnectEvents) + len(once.playerConnectEvents)
	if lisCount < 1 {
		go unregisterOnEvent(playerConnect)
	}
}

//export altPlayerConnectEvent
func altPlayerConnectEvent(e C.struct_entity) {
	p, err := altv.GetBaseObject[altv.Player](altv.BaseObjectType(e.typ), unsafe.Pointer(e.ptr), uint32(e.id), 0)
	if err != nil {
		altv.LogError(fmt.Sprintf("[Go] PlayerConnect: %v", err))
		return
	}

	for i, event := range once.playerConnectEvents {
		event(p)
		once.playerConnectEvents = slices.Delete(once.playerConnectEvents, i, 1)
	}

	for _, event := range on.playerConnectEvents {
		event(p)
	}

	checkPlayerConnect()
}
