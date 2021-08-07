package alt

// #include "Module.h"
import "C"
import "unsafe"

type eventType = uint16
type playerConnectListener = func(p *Player)
type playerDisconnectListener = func(p *Player)

type eventManager struct {
	playerConnectEvents []playerConnectListener
}

type listener interface {
	PlayerConnect(listener playerConnectListener)
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

//export altPlayerConnectEvent
func altPlayerConnectEvent(player unsafe.Pointer) {
	for _, event := range On.playerConnectEvents {
		player := NewPlayer(player)

		event(player)
	}
}
