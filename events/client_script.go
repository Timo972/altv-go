package events

import (
	"golang.org/x/exp/slices"
)

type clientEventListener func(ctx *ClientCtx)

func checkClientEvent(eventName string) {
	lisCount := len(on.clientScriptEvents[eventName]) + len(once.clientScriptEvents[eventName])
	if lisCount < 1 {
		go unregisterOnEvent(clientScriptEvent)
	}
}

func (s *subscriber) ClientEvent(eventName string, listener clientEventListener) int {
	listeners, ok := s.clientScriptEvents[eventName]
	if !ok {
		listeners = make([]clientEventListener, 1)
		listeners[0] = listener
	} else {
		listeners = append(listeners, listener)
	}

	s.clientScriptEvents[eventName] = listeners
	go registerOnEvent(clientScriptEvent)
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
