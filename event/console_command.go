package event

// #include "capi.h"
import "C"
import (
	"github.com/timo972/altv-go/internal/cutil"
	"golang.org/x/exp/slices"
)

type consoleCommandListener = func(cmd string, args []string)

func checkConsoleCommand() {
	re := len(once.consoleCommandEvents) + len(on.consoleCommandEvents)
	if re < 1 {
		unregisterOnEvent(consoleCommandEvent)
	}
}

func (e *subscriber) ConsoleCommand(listener consoleCommandListener) int {
	e.consoleCommandEvents = append(e.consoleCommandEvents, listener)
	registerOnEvent(consoleCommandEvent)
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
	args := cutil.NewStringArray(cargs.ptr, int(cargs.size))

	for _, event := range once.consoleCommandEvents {
		event(name, args)
	}
	clear(once.consoleCommandEvents)

	for _, event := range on.consoleCommandEvents {
		event(name, args)
	}

	checkConsoleCommand()
}
