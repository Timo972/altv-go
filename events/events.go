package events

import (
	"unsafe"

	"github.com/timo972/altv-go"
)

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

	serverScriptEvents map[string][]serverEventListener
	clientScriptEvents map[string][]clientEventListener
	once               bool
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
	ServerEvent(eventName string, listener serverEventListener) int
	ClientEvent(eventName string, listener clientEventListener) int
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
}

var (
	on   *subscriber       = &subscriber{serverScriptEvents: make(map[string][]serverEventListener), clientScriptEvents: make(map[string][]clientEventListener)}
	once *subscriber       = &subscriber{once: true, serverScriptEvents: make(map[string][]serverEventListener), clientScriptEvents: make(map[string][]clientEventListener)}
	On   EventSubscriber   = on
	Once EventSubscriber   = once
	Off  EventUnsubscriber = &unsubscriber{sub: on}
)

func registerOnEvent(event uint16) {
	altv.WaitReady()

	cresource := C.CString(altv.CurrentResource.Name())
	defer C.free(unsafe.Pointer(cresource))

	C.runtime_register_alt_event(cresource, C.ushort(event))
}

func unregisterOnEvent(event uint16) {
	altv.WaitReady()

	cresource := C.CString(altv.CurrentResource.Name())
	defer C.free(unsafe.Pointer(cresource))

	C.runtime_unregister_alt_event(cresource, C.ushort(event))
}
