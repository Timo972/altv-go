package event

import (
	"fmt"

	"golang.org/x/exp/slices"
)
import "C"

type serverStartedListener func()

func (sub *subscriber) ServerStarted(listener serverStartedListener) int {
	fmt.Println("subscribing to serverStarted")
	sub.serverStartedEvents = append(sub.serverStartedEvents, listener)
	registerOnEvent(serverStarted)
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
		unregisterOnEvent(serverStarted)
	}
}

//export altServerStartedEvent
func altServerStartedEvent() {
	for _, event := range once.serverStartedEvents {
		event()
	}
	clear(once.serverStartedEvents)

	for _, event := range on.serverStartedEvents {
		event()
	}

	checkServerStarted()
}
