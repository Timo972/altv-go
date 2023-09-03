package event

import (
	"slices"
)

// #include "capi.h"
import "C"

type ServerEventListener func(ctx *Ctx)

func numServerEventListeners(eventName string) int {
	count := 0
	if event, ok := on.serverScriptEvents[eventName]; ok {
		count += len(event)
	}
	if event, ok := once.serverScriptEvents[eventName]; ok {
		count += len(event)
	}

	return count
}

func checkServerEvent(eventName string) {
	lisCount := numServerEventListeners(eventName)
	if lisCount < 1 {
		unregisterOnEvent(serverScriptEvent)
	}
}

func (s *subscriber) ServerEvent(eventName string, listener ServerEventListener) int {
	listeners, ok := s.serverScriptEvents[eventName]
	if !ok {
		listeners = make([]ServerEventListener, 1)
		listeners[0] = listener
	} else {
		listeners = append(listeners, listener)
	}

	s.serverScriptEvents[eventName] = listeners
	registerOnEvent(serverScriptEvent)
	return len(listeners) - 1
}

func (unsub *unsubscriber) ServerEvent(eventName string, id int) error {
	listeners, ok := unsub.sub.serverScriptEvents[eventName]
	if !ok {
		return ErrInvalidEventName
	}

	if id < 0 || id >= len(listeners) {
		return ErrInvalidEventID
	}

	unsub.sub.serverScriptEvents[eventName] = slices.Delete(listeners, id, 1)
	checkServerEvent(eventName)
	return nil
}

//export altServerScriptEvent
func altServerScriptEvent(cName *C.char, arr C.struct_array) {
	evt := C.GoString(cName)

	if lisCount := numServerEventListeners(evt); lisCount < 1 {
		// TODO: free C.struct_array
		return
	}

	ctx := ctxPool.Get().(*Ctx)
	ctx.defaults()

	ctx.copyArgs(arr)

	if event, ok := once.serverScriptEvents[evt]; ok {
		for _, event := range event {
			event(ctx)
		}
		clear(once.serverScriptEvents[evt])
	}

	if event, ok := on.serverScriptEvents[evt]; ok {
		for _, event := range event {
			event(ctx)
		}
	}

	ctx.reset()
	ctxPool.Put(ctx)

	checkServerEvent(evt)
}
