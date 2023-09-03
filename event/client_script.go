package event

import (
	"fmt"
	"unsafe"

	"slices"

	"github.com/timo972/altv-go/altlog"
	"github.com/timo972/altv-go/entity"
	"github.com/timo972/altv-go/factory"
)

// #include "capi.h"
import "C"

type ClientEventListener func(ctx *ClientCtx)

func numClientEventListeners(eventName string) int {
	count := 0
	if event, ok := on.clientScriptEvents[eventName]; ok {
		count += len(event)
	}
	if event, ok := once.clientScriptEvents[eventName]; ok {
		count += len(event)
	}

	return count
}

func checkClientEvent(eventName string) {
	lisCount := numClientEventListeners(eventName)
	if lisCount < 1 {
		unregisterOnEvent(clientScriptEvent)
	}
}

func (s *subscriber) ClientEvent(eventName string, listener ClientEventListener) int {
	listeners, ok := s.clientScriptEvents[eventName]
	if !ok {
		listeners = make([]ClientEventListener, 1)
		listeners[0] = listener
	} else {
		listeners = append(listeners, listener)
	}

	s.clientScriptEvents[eventName] = listeners
	registerOnEvent(clientScriptEvent)
	return len(listeners) - 1
}

func (unsub *unsubscriber) ClientEvent(eventName string, id int) error {
	listeners, ok := unsub.sub.clientScriptEvents[eventName]
	if !ok {
		return ErrInvalidEventName
	}

	if id < 0 || id >= len(listeners) {
		return ErrInvalidEventID
	}

	unsub.sub.clientScriptEvents[eventName] = slices.Delete(listeners, id, 1)
	checkClientEvent(eventName)
	return nil
}

//export altClientScriptEvent
func altClientScriptEvent(e *C.struct_baseObject, cName *C.char, arr C.struct_array) {
	evt := C.GoString(cName)

	if lisCount := numClientEventListeners(evt); lisCount < 1 {
		//TODO: free C.struct_array
		return
	}

	ctx := clientCtxPool.Get().(*ClientCtx)
	ctx.defaults()

	var err error
	ctx.p, err = factory.GetBaseObject[entity.Player](entity.BaseObjectType(e.typ), unsafe.Pointer(e.ptr), uint32(e.id), 0)
	if err != nil {
		altlog.Errorln(fmt.Sprintf("[Go] ClientScriptEvent: %v", err))
		return
	}

	ctx.copyArgs(arr)

	if event, ok := once.clientScriptEvents[evt]; ok {
		for _, event := range event {
			event(ctx)
		}
		clear(once.clientScriptEvents[evt])
	}

	if event, ok := on.clientScriptEvents[evt]; ok {
		for _, event := range event {
			event(ctx)
		}
	}

	ctx.reset()
	ctxPool.Put(ctx)

	checkClientEvent(evt)
}
