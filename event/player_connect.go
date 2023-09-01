package event

// #include "capi.h"
import "C"
import (
	"fmt"
	"unsafe"

	"github.com/timo972/altv-go/altlog"
	"github.com/timo972/altv-go/entity"
	"github.com/timo972/altv-go/factory"
	"golang.org/x/exp/slices"
)

type playerConnectListener func(p entity.Player)

func (e *subscriber) PlayerConnect(listener playerConnectListener) int {
	e.playerConnectEvents = append(e.playerConnectEvents, listener)
	registerOnEvent(playerConnect)

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
		unregisterOnEvent(playerConnect)
	}
}

//export altPlayerConnectEvent
func altPlayerConnectEvent(e *C.struct_baseObject) {
	p, err := factory.GetBaseObject[entity.Player](entity.BaseObjectType(e.typ), unsafe.Pointer(e.ptr), uint32(e.id), 0)
	if err != nil {
		altlog.Errorln(fmt.Sprintf("[Go] PlayerConnect: %v", err))
		return
	}

	for _, event := range once.playerConnectEvents {
		event(p)
	}
	clear(once.playerConnectEvents)

	for _, event := range on.playerConnectEvents {
		event(p)
	}

	checkPlayerConnect()
}
