package event

// #include "capi.h"
import "C"
import (
	"slices"
)

type resourceErrorListener = func(resourceName string)

func checkResourceError() {
	re := len(once.resourceErrorEvents) + len(on.resourceErrorEvents)
	if re < 1 {
		unregisterOnEvent(resourceError)
	}
}

func (e *subscriber) ResourceError(listener resourceErrorListener) int {
	e.resourceErrorEvents = append(e.resourceErrorEvents, listener)
	registerOnEvent(resourceError)
	return len(e.resourceErrorEvents) - 1
}

func (unsub *unsubscriber) ResourceError(id int) error {
	if id < 0 || id >= len(unsub.sub.resourceErrorEvents) {
		return ErrInvalidEventID
	}

	unsub.sub.resourceErrorEvents = slices.Delete(unsub.sub.resourceErrorEvents, id, 1)
	checkResourceError()
	return nil
}

//export altResourceErrorEvent
func altResourceErrorEvent(n *C.char) {
	name := C.GoString(n)

	for _, event := range once.resourceErrorEvents {
		event(name)
	}
	clear(once.resourceErrorEvents)

	for _, event := range on.resourceErrorEvents {
		event(name)
	}

	checkResourceError()
}
