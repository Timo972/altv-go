package events

import (
	"golang.org/x/exp/slices"
)

// #include "capi.h"
import "C"

type serverEventListener func(ctx *Ctx)

func checkServerEvent(eventName string) {
	lisCount := len(on.serverScriptEvents[eventName]) + len(once.serverScriptEvents[eventName])
	if lisCount < 1 {
		go unregisterOnEvent(serverScriptEvent)
	}
}

func (s *subscriber) ServerEvent(eventName string, listener serverEventListener) int {
	listeners, ok := s.serverScriptEvents[eventName]
	if !ok {
		listeners = make([]serverEventListener, 1)
		listeners[0] = listener
	} else {
		listeners = append(listeners, listener)
	}

	s.serverScriptEvents[eventName] = listeners
	go registerOnEvent(serverScriptEvent)
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
	ctx := getCtx()

	for _, event := range once.serverScriptEvents[evt] {
		event(ctx)
	}
	once.serverScriptEvents[evt] = make([]serverEventListener, 0)

	for _, event := range on.serverScriptEvents[evt] {
		event(ctx)
	}

	checkServerEvent(evt)
}
