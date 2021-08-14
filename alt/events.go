package alt

// #include "Module.h"
import "C"
import (
	"unsafe"

	"github.com/shockdev04/altv-go-pkg/internal/module"
)

type eventType = uint16
type playerConnectListener = func(p *Player)
type playerDisconnectListener = func(p *Player)
type consoleCommandListener = func(command string, args []string)

type eventManager struct {
	playerConnectEvents  []playerConnectListener
	consoleCommandEvents []consoleCommandListener
}

type listener interface {
	PlayerConnect(listener playerConnectListener)
	ConsoleCommand(listener consoleCommandListener)
}

const (
	none eventType = iota
	playerConnect
	playerDisconnect
	resourceStart
	resourceStop
	resourceError
	serverScriptEvent
	clientScriptEvent
	metaChange
	syncedMetaChange
	streamSyncedMetaChange
	globalMetaChange
	globalSyncedMetaChange
	playerDamage
	playerDeath
	fireEvent
	explosionEvent
	startProjectileEvent
	weaponDamageEvent
	vehicleDestroy
	checkpointEvent
	colshapeEvent
	playerEnterVehicle
	playerEnteringVehicle
	playerLeaveVehicle
	playerChangeVehicleSeat
	playerWeaponChange
	vehicleAttach
	vehicleDetach
	netownerChange
	removeEntityEvent
	createBaseObjectEvent
	removeBaseObjectEvent
	dataNodeReceivedEvent
	consoleCommandEvent
)

var On = &eventManager{}

func registerOnEvent(resource string, event uint16) {
	cresource := C.CString(resource)
	defer C.free(unsafe.Pointer(cresource))

	C.register_alt_event(cresource, C.ushort(event))
}

func (e eventManager) PlayerConnect(listener playerConnectListener) {
	On.playerConnectEvents = append(On.playerConnectEvents, listener)
	registerOnEvent(Resource.Name, playerConnect)
}

func (e eventManager) ConsoleCommand(listener consoleCommandListener) {
	On.consoleCommandEvents = append(On.consoleCommandEvents, listener)
	registerOnEvent(Resource.Name, consoleCommandEvent)
}

//export altPlayerConnectEvent
func altPlayerConnectEvent(player unsafe.Pointer) {
	for _, event := range On.playerConnectEvents {
		player := NewPlayer(player)

		event(player)
	}
}

//export altConsoleCommandEvent
func altConsoleCommandEvent(cName *C.char, cArray **C.char, cSize C.ulonglong ) {
	name := C.GoString(cName)

	args := module.MakeStringArray(cSize, cArray)

	for _, event := range On.consoleCommandEvents {
		event(name, args)
	}
}
