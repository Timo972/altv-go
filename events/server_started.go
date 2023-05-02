package events

import (
	"fmt"

	"golang.org/x/exp/slices"
)
import "C"

type serverStartedListener func()

func (sub *subscriber) ServerStarted(listener serverStartedListener) int {
	fmt.Println("subscribing to serverStarted")
	sub.serverStartedEvents = append(sub.serverStartedEvents, listener)
	go registerOnEvent(serverStarted)
	return len(sub.serverStartedEvents) - 1
}

func (unsub *unsubscriber) ServerStarted(id int) error {
	if id < 0 || id >= len(unsub.sub.serverStartedEvents) {
		return ErrInvalidEventID
	}

	unsub.sub.serverStartedEvents = slices.Delete(unsub.sub.serverStartedEvents, id, 1)
	checkServerStarted()
	return nil
}

func checkServerStarted() {
	lisCount := len(on.serverStartedEvents) + len(once.serverStartedEvents)
	if lisCount < 1 {
		go unregisterOnEvent(serverStarted)
	}
}

//export altServerStartedEvent
func altServerStartedEvent() {
	for i, event := range once.serverStartedEvents {
		event()
		once.serverStartedEvents = slices.Delete(once.serverStartedEvents, i, 1)
	}

	for _, event := range on.serverStartedEvents {
		event()
	}

	checkServerStarted()
}
