package alt

import (
	"github.com/shockdev04/altv-go-pkg/internal/module"
	"unsafe"
)

type eventType = uint16
type playerConnectListener = func(p *Player)
type playerDisconnectListener = func(p *Player)

type eventManager struct {
	playerConnectEvents []playerConnectListener
}

type Listener interface {
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

func (e eventManager) PlayerConnect(listener playerConnectListener) {
	On.playerConnectEvents = append(On.playerConnectEvents, listener)
	module.RegisterAltEvent(Resource.Name, playerConnect)
}

//export altPlayerConnectEvent
func altPlayerConnectEvent(player unsafe.Pointer) {
	for _, event := range On.playerConnectEvents {
		player := NewPlayer(player)

		event(player)
	}
}