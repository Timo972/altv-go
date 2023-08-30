package events

// #include "capi.h"
import "C"
import (
	"github.com/timo972/altv-go/internal/cstrings"
	"golang.org/x/exp/slices"
)

type consoleCommandListener = func(cmd string, args []string)

func checkConsoleCommand() {
	re := len(once.consoleCommandEvents) + len(on.consoleCommandEvents)
	if re < 1 {
		go unregisterOnEvent(consoleCommandEvent)
	}
}

func (e *subscriber) ConsoleCommand(listener consoleCommandListener) int {
	e.consoleCommandEvents = append(e.consoleCommandEvents, listener)
	go registerOnEvent(consoleCommandEvent)
	return len(e.consoleCommandEvents) - 1
}

func (unsub *unsubscriber) ConsoleCommand(id int) error {
	if id < 0 || id >= len(unsub.sub.consoleCommandEvents) {
		return ErrInvalidEventID
	}

	unsub.sub.consoleCommandEvents = slices.Delete(unsub.sub.consoleCommandEvents, id, 1)
	checkConsoleCommand()
	return nil
}

//export altConsoleCommandEvent
func altConsoleCommandEvent(cname *C.char, cargs C.struct_array) {
	name := C.GoString(cname)
	args := cstrings.NewArray(cargs.array, int(cargs.size))

	for i, event := range once.consoleCommandEvents {
		event(name, args)
		once.consoleCommandEvents = slices.Delete(once.consoleCommandEvents, i, 1)
	}

	for _, event := range on.consoleCommandEvents {
		event(name, args)
	}

	checkConsoleCommand()
}
