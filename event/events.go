package event

// #cgo CFLAGS: -I../internal/c-api/lib
// #cgo linux LDFLAGS: -L../internal/c-api/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L../internal/c-api/lib/win32 -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
// #include <stdlib.h>
// #include "capi.h"
import "C"

type eventType = uint16

const (
	none eventType = iota

	serverStarted

	playerConnect
	playerDisconnect
	playerConnectDenied
	playerSpawn

	connectionQueueAdd
	connectionQueueRemove

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
	localSyncedMetaChange

	playerDamage
	playerDeath
	fireEvent
	explosionEvent
	startProjectileEvent
	weaponDamageEvent
	vehicleDestroy
	vehicleDamage

	checkpointEvent
	colshapeEvent
	playerEnterVehicle
	playerEnteringVehicle
	playerLeaveVehicle
	playerChangeVehicleSeat
	playerWeaponChange
	playerRequestControl

	vehicleAttach
	vehicleDetach
	vehicleHorn
	vehicleSiren
	netOwnerChange

	createBaseObjectEvent
	removeBaseObjectEvent

	dataNodeReceivedEvent

	consoleCommandEvent

	playerChangeAnimationEvent

	playerChangeInteriorEvent

	playerWeaponShootEvent

	playerDimensionChangeEvent
)

type subscriber struct {
	serverStartedEvents         []serverStartedListener
	playerConnectEvents         []playerConnectListener
	resourceErrorEvents         []resourceErrorListener
	connectionQueueAddEvents    []connectionQueueAddListener
	connectionQueueRemoveEvents []connectionQueueRemoveListener

	playerDamageEvents []playerDamageListener
	resourceStopEvents []resourceStopListener

	serverScriptEvents map[string][]ServerEventListener
	clientScriptEvents map[string][]ClientEventListener
	once               bool

	consoleCommandEvents []consoleCommandListener
}

type unsubscriber struct {
	sub *subscriber
}

type EventSubscriber interface {
	ServerStarted(serverStartedListener) int
	PlayerConnect(playerConnectListener) int
	ResourceError(resourceErrorListener) int
	ConnectionQueueAdd(connectionQueueAddListener) int
	ConnectionQueueRemove(connectionQueueRemoveListener) int
	PlayerDamage(playerDamageListener) int
	ResourceStop(resourceStopListener) int
	ServerEvent(eventName string, listener ServerEventListener) int
	ClientEvent(eventName string, listener ClientEventListener) int
	ConsoleCommand(consoleCommandListener) int
}

type EventUnsubscriber interface {
	ServerStarted(int) error
	PlayerConnect(int) error
	ResourceError(int) error
	ConnectionQueueAdd(int) error
	ConnectionQueueRemove(int) error
	PlayerDamage(int) error
	ResourceStop(int) error
	ServerEvent(eventName string, id int) error
	ClientEvent(eventName string, id int) error
	ConsoleCommand(int) error
}

var (
	on   *subscriber       = &subscriber{serverScriptEvents: make(map[string][]ServerEventListener), clientScriptEvents: make(map[string][]ClientEventListener)}
	once *subscriber       = &subscriber{once: true, serverScriptEvents: make(map[string][]ServerEventListener), clientScriptEvents: make(map[string][]ClientEventListener)}
	On   EventSubscriber   = on
	Once EventSubscriber   = once
	Off  EventUnsubscriber = &unsubscriber{sub: on}
)
