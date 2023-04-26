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
	playerBeforeConnect
	playerDisconnect

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
	netOwnerChange

	removeEntityEvent
	createBaseObjectEvent
	removeBaseObjectEvent
	dataNodeReceivedEvent

	consoleCommandEvent
	playerChangeAnimationEvent
	playerChangeInteriorEvent

	// is this client only?
	playerWeaponShoot
)

type subscriber struct {
	serverStartedEvents []serverStartedListener
	playerConnectEvents []playerConnectListener
	once                bool
}

type unsubscriber struct {
	sub *subscriber
}

type EventSubscriber interface {
	ServerStarted(serverStartedListener) int
	PlayerConnect(playerConnectListener) int
}

type EventUnsubscriber interface {
	ServerStarted(int) error
	PlayerConnect(int) error
}

var (
	on   *subscriber       = &subscriber{}
	once *subscriber       = &subscriber{once: true}
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
