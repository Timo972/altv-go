package event

import (
	"unsafe"

	"github.com/timo972/altv-go"
	"golang.org/x/exp/slices"
)

// #include "capi.h"
import "C"

type connectionQueueAddListener func(connectionInfo *altv.ConnectionInfo)
type connectionQueueRemoveListener func(connectionInfo *altv.ConnectionInfo)

func checkConnectionQueueAdd() {
	lisCount := len(on.connectionQueueAddEvents) + len(once.connectionQueueAddEvents)
	if lisCount < 1 {
		unregisterOnEvent(connectionQueueAdd)
	}
}

func checkConnectionQueueRemove() {
	lisCount := len(on.connectionQueueRemoveEvents) + len(once.connectionQueueRemoveEvents)
	if lisCount < 1 {
		unregisterOnEvent(connectionQueueRemove)
	}
}

func (sub *subscriber) ConnectionQueueAdd(listener connectionQueueAddListener) int {
	sub.connectionQueueAddEvents = append(sub.connectionQueueAddEvents, listener)
	registerOnEvent(connectionQueueAdd)
	return len(sub.connectionQueueAddEvents) - 1
}

func (unsub *unsubscriber) ConnectionQueueAdd(id int) error {
	if id < 0 || id >= len(unsub.sub.connectionQueueAddEvents) {
		return ErrInvalidEventID
	}

	unsub.sub.connectionQueueAddEvents = slices.Delete(unsub.sub.connectionQueueAddEvents, id, 1)
	checkConnectionQueueAdd()
	return nil
}

func (sub *subscriber) ConnectionQueueRemove(listener connectionQueueRemoveListener) int {
	sub.connectionQueueRemoveEvents = append(sub.connectionQueueRemoveEvents, listener)
	registerOnEvent(connectionQueueRemove)
	return len(sub.connectionQueueRemoveEvents) - 1
}

func (unsub *unsubscriber) ConnectionQueueRemove(id int) error {
	if id < 0 || id >= len(unsub.sub.connectionQueueRemoveEvents) {
		return ErrInvalidEventID
	}

	unsub.sub.connectionQueueRemoveEvents = slices.Delete(unsub.sub.connectionQueueRemoveEvents, id, 1)
	checkConnectionQueueRemove()
	return nil
}

//export altConnectionQueueAddEvent
func altConnectionQueueAddEvent(cHandle unsafe.Pointer, cInfo C.struct_connectionInfo) {
	info := altv.NewConnectionInfo(cHandle, uint32(cInfo.id), C.GoString(cInfo.name), uint64(cInfo.socialID), C.GoString(cInfo.socialName), uint64(cInfo.hwidHash), uint64(cInfo.hwidExHash), C.GoString(cInfo.authToken), uint8(cInfo.isDebug) == 1, C.GoString(cInfo.branch), uint32(cInfo.build), C.GoString(cInfo.cdnUrl), uint64(cInfo.passwordHash), C.GoString(cInfo.ip), int64(cInfo.discordUserID), C.GoString(cInfo.cloudAuthHash))

	for _, event := range once.connectionQueueAddEvents {
		event(info)
	}
	clear(once.connectionQueueAddEvents)

	for _, event := range on.connectionQueueAddEvents {
		event(info)
	}

	checkConnectionQueueAdd()
}

//export altConnectionQueueRemoveEvent
func altConnectionQueueRemoveEvent(cHandle unsafe.Pointer, cInfo C.struct_connectionInfo) {
	info := altv.NewConnectionInfo(cHandle, uint32(cInfo.id), C.GoString(cInfo.name), uint64(cInfo.socialID), C.GoString(cInfo.socialName), uint64(cInfo.hwidHash), uint64(cInfo.hwidExHash), C.GoString(cInfo.authToken), uint8(cInfo.isDebug) == 1, C.GoString(cInfo.branch), uint32(cInfo.build), C.GoString(cInfo.cdnUrl), uint64(cInfo.passwordHash), C.GoString(cInfo.ip), int64(cInfo.discordUserID), C.GoString(cInfo.cloudAuthHash))

	for _, event := range once.connectionQueueRemoveEvents {
		event(info)
	}
	clear(once.connectionQueueRemoveEvents)

	for _, event := range on.connectionQueueRemoveEvents {
		event(info)
	}

	checkConnectionQueueRemove()
}
