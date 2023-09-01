package event

// #include "capi.h"
import "C"
import (
	"golang.org/x/exp/slices"
)

type resourceStopListener = func(resourceName string)

func checkResourceStop() {
	re := len(once.resourceStopEvents) + len(on.resourceStopEvents)
	if re < 1 {
		unregisterOnEvent(resourceError)
	}
}

func (e *subscriber) ResourceStop(listener resourceErrorListener) int {
	e.resourceStopEvents = append(e.resourceStopEvents, listener)
	registerOnEvent(resourceError)
	return len(e.resourceStopEvents) - 1
}

func (unsub *unsubscriber) ResourceStop(id int) error {
	if id < 0 || id >= len(unsub.sub.resourceStopEvents) {
		return ErrInvalidEventID
	}

	unsub.sub.resourceStopEvents = slices.Delete(unsub.sub.resourceStopEvents, id, 1)
	checkResourceStop()
	return nil
}

//export altResourceStopEvent
func altResourceStopEvent(n *C.char) {
	name := C.GoString(n)

	for _, event := range once.resourceStopEvents {
		event(name)
	}
	clear(once.resourceStopEvents)

	for _, event := range on.resourceStopEvents {
		event(name)
	}

	checkResourceStop()
}
