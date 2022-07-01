package alt

/*
#cgo windows CFLAGS: -I../../c-api/lib
#cgo windows LDFLAGS: -L../../c-api/lib/win32 -lcapi

#cgo linux CFLAGS: -I../../c-api/lib
#cgo linux LDFLAGS: -g -L../../c-api/lib/linux -lcapi  -ldl

#ifndef GOLANG_APP
#define GOLANG_APP

#include <stdlib.h>
#include "capi.h"

#endif
*/
import "C"
import (
	"errors"
	"reflect"
	"unsafe"

	"github.com/timo972/altv-go/internal/module"
)

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
)

type serverStartedListener = func()

type playerConnectListener = func(p *Player)
type playerBeforeConnectListener = func(connectionInfo ConnectionInfo, reason string)
type playerDisconnectListener = func(p *Player, reason string)

type connectionQueueAddListener = func(connectionInfo ConnectionInfo)
type connectionQueueRemoveListener = func(connectionInfo ConnectionInfo)

type resourceStartListener = func(resourceName string)
type resourceStopListener = func(resourceName string)
type resourceErrorListener = func(resourceName string)

type metaDataChangeListener = func(key string, newValue interface{}, oldValue interface{})
type syncedMetaDataChangeListener = func(entity *Entity, key string, newValue interface{}, oldValue interface{})
type streamSyncedMetaDataChangeListener = func(entity *Entity, key string, newValue interface{}, oldValue interface{})
type globalMetaDataChangeListener = func(key string, newValue interface{}, oldValue interface{})
type globalSyncedMetaDataChangeListener func(key string, newValue interface{}, oldValue interface{})
type localSyncedMetaDataChangeListener = func(player *Player, key string, newValue interface{}, oldValue interface{})

type playerDamageListener = func(p *Player, attacker *Entity, healthDamage uint16, armourDamage uint16, weapon uint32)
type playerDeathListener = func(p *Player, killer *Entity, weapon uint32)
type fireListener = func(player *Player, fires []FireInfo) bool
type explosionListener = func(p *Player, target *Entity, pos Vector3, explosionType int16, explosionFX uint) bool
type startProjectileListener = func(player *Player, position Vector3, direction Vector3, ammoHash uint16, weaponHash uint32) bool

// TODO bodyPart ENUM
type weaponDamageListener = func(source *Player, target *Entity, weapon uint32, damage uint16, offset Vector3, bodyPart int8) bool
type vehicleDestroyListener = func(vehicle *Vehicle)
type vehicleDamageListener = func(vehicle *Vehicle, entity *Entity, bodyDamage uint32, additionalBodyDamage uint32, engineDamage uint32, petrolTankDamage uint32, damageWidth uint32)

type entityEnterColShapeListener = func(colShape *ColShape, entity *Entity)
type entityLeaveColShapeListener = func(colShape *ColShape, entity *Entity)
type playerEnterVehicleListener = func(p *Player, v *Vehicle, seat uint8)
type playerEnteringVehicleListener = func(p *Player, v *Vehicle, seat uint8)
type playerLeaveVehicleListener = func(p *Player, v *Vehicle, seat uint8)
type playerChangeVehicleSeatListener = func(p *Player, v *Vehicle, oldSeat uint8, newSeat uint8)
type playerWeaponChangeListener = func(player *Player, oldWeapon uint32, newWeapon uint32) bool
type playerRequestControlListener = func(player *Player, target *Entity) bool

type vehicleAttachListener = func(vehicle *Vehicle, attachedVehicle *Vehicle)
type vehicleDetachListener = func(vehicle *Vehicle, detachedVehicle *Vehicle)
type netOwnerChangeListener = func(entity *Entity, owner *Player, oldOwner *Player)

type removeEntityListener = func(entity *Entity)

type consoleCommandListener = func(command string, args []string)

// type allServerEventsListener = func(eventName string, args ...interface{})
// type serverEventListener = func(args ...interface{})
// type allClientEventsListener = func(player *Player, eventName string, args ...interface{})
// type clientEventListener = func(player *Player, args ...interface{})

type scriptEventListener = interface{}

type eventManager struct {
	serverStartedEvents              []serverStartedListener
	playerConnectEvents              []playerConnectListener
	playerBeforeConnectEvents        []playerBeforeConnectListener
	connectionQueueAddEvents         []connectionQueueAddListener
	connectionQueueRemoveEvents      []connectionQueueRemoveListener
	consoleCommandEvents             []consoleCommandListener
	playerDisconnectEvents           []playerDisconnectListener
	explosionEvents                  []explosionListener
	playerChangeVehicleSeatEvents    []playerChangeVehicleSeatListener
	playerDamageEvents               []playerDamageListener
	playerDeathEvents                []playerDeathListener
	playerEnterVehicleEvents         []playerEnterVehicleListener
	playerLeaveVehicleEvents         []playerLeaveVehicleListener
	removeEntityEvents               []removeEntityListener
	resourceStartEvents              []resourceStartListener
	weaponDamageEvents               []weaponDamageListener
	playerEnteringVehicleEvents      []playerEnteringVehicleListener
	entityEnterColShapeEvents        []entityEnterColShapeListener
	entityLeaveColShapeEvents        []entityLeaveColShapeListener
	fireEvents                       []fireListener
	globalMetaDataChangeEvents       []globalMetaDataChangeListener
	globalSyncedMetaDataChangeEvents []globalSyncedMetaDataChangeListener
	localSyncedMetaDataChangeEvents  []localSyncedMetaDataChangeListener
	metaDataChangeEvents             []metaDataChangeListener
	netOwnerChangeEvents             []netOwnerChangeListener
	playerWeaponChangeEvents         []playerWeaponChangeListener
	playerRequestControlEvents       []playerRequestControlListener
	resourceErrorEvents              []resourceErrorListener
	resourceStopEvents               []resourceStopListener
	startProjectileEvents            []startProjectileListener
	streamSyncedMetaDataChangeEvents []streamSyncedMetaDataChangeListener
	syncedMetaDataChangeEvents       []syncedMetaDataChangeListener
	vehicleAttachEvents              []vehicleAttachListener
	vehicleDetachEvents              []vehicleDetachListener
	vehicleDestroyEvents             []vehicleDestroyListener
	vehicleDamageEvents              []vehicleDamageListener
	serverScriptEvents               map[string][]reflect.Value
	clientScriptEvents               map[string][]reflect.Value
	allServerScriptEvents            []reflect.Value
	allClientScriptEvents            []reflect.Value
}

/*type listener interface {
	ServerStarted(listener serverStartedListener)
	PlayerConnect(listener playerConnectListener)
	PlayerBeforeConnect(listener playerBeforeConnectListener)
	ConnectionQueueAdd(listener connectionQueueAddListener)
	ConnectionQueueRemove(listener connectionQueueRemoveListener)
	ConsoleCommand(listener consoleCommandListener)
	PlayerDisconnect(listener playerDisconnectListener)
	Explosion(listener explosionListener)
	PlayerChangeVehicleSeat(listener playerChangeVehicleSeatListener)
	PlayerDamage(listener playerDamageListener)
	PlayerDeath(listener playerDeathListener)
	PlayerEnterVehicle(listener playerEnterVehicleListener)
	PlayerLeaveVehicle(listener playerLeaveVehicleListener)
	RemoveEntity(listener removeEntityListener)
	ResourceStart(listener resourceStartListener)
	WeaponDamage(listener weaponDamageListener)
	PlayerEnteringVehicle(listener playerEnteringVehicleListener)
	EntityEnterColShape(listener entityEnterColShapeListener)
	EntityLeaveColShape(listener entityLeaveColShapeListener)
	StartFire(listener fireListener)
	GlobalMetaChange(listener globalMetaDataChangeListener)
	GlobalSyncedMetaChange(listener globalSyncedMetaDataChangeListener)
	LocalSyncedMetaChange(listener localSyncedMetaDataChangeListener)
	MetaChange(listener metaDataChangeListener)
	NetOwnerChange(listener netOwnerChangeListener)
	PlayerWeaponChange(listener playerWeaponChangeListener)
	PlayerRequestControl(listener playerRequestControlListener)
	ResourceError(listener resourceErrorListener)
	ResourceStop(listener resourceStopListener)
	StartProjectile(listener startProjectileListener)
	StreamSyncedMetaChange(listener streamSyncedMetaDataChangeListener)
	SyncedMetaChange(listener syncedMetaDataChangeListener)
	VehicleAttach(listener vehicleAttachListener)
	VehicleDetach(listener vehicleDetachListener)
	VehicleDestroy(listener vehicleDestroyListener)
	VehicleDamage(listener vehicleDamageListener)
	AllServerEvents(listener scriptEventListener)
	ServerEvent(eventName string, listener scriptEventListener)
	AllClientEvents(listener scriptEventListener)
	ClientEvent(eventName string, listener scriptEventListener)
}*/

var On = &eventManager{}
var Once = &eventManager{}

func registerOnEvent(resource string, event uint16) {
	cresource := C.CString(resource)
	defer C.free(unsafe.Pointer(cresource))

	C.runtime_register_alt_event(cresource, C.ushort(event))
}

func unregisterOnEvent(resource string, event uint16) {
	cresource := C.CString(resource)
	defer C.free(unsafe.Pointer(cresource))

	C.runtime_unregister_alt_event(cresource, C.ushort(event))
}

func removeIndex[V any](slice []V, index int) []V {
	return append(slice[:index], slice[index+1:]...)
}

func (e *eventManager) ServerStarted(listener serverStartedListener) {
	e.serverStartedEvents = append(e.serverStartedEvents, listener)
	registerOnEvent(CurrentResource.Name(), serverStarted)
}

func (e *eventManager) PlayerConnect(listener playerConnectListener) {
	e.playerConnectEvents = append(e.playerConnectEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerConnect)
}

func (e *eventManager) PlayerBeforeConnect(listener playerBeforeConnectListener) {
	e.playerBeforeConnectEvents = append(e.playerBeforeConnectEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerBeforeConnect)
}

func (e *eventManager) ConnectionQueueAdd(listener connectionQueueAddListener) {
	e.connectionQueueAddEvents = append(e.connectionQueueAddEvents, listener)
	registerOnEvent(CurrentResource.Name(), connectionQueueAdd)
}

func (e *eventManager) ConnectionQueueRemove(listener connectionQueueRemoveListener) {
	e.connectionQueueRemoveEvents = append(e.connectionQueueRemoveEvents, listener)
	registerOnEvent(CurrentResource.Name(), connectionQueueRemove)
}

func (e *eventManager) ConsoleCommand(listener consoleCommandListener) {
	e.consoleCommandEvents = append(e.consoleCommandEvents, listener)
	registerOnEvent(CurrentResource.Name(), consoleCommandEvent)
}

func (e *eventManager) PlayerDisconnect(listener playerDisconnectListener) {
	e.playerDisconnectEvents = append(e.playerDisconnectEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerDisconnect)
}

func (e *eventManager) Explosion(listener explosionListener) {
	e.explosionEvents = append(e.explosionEvents, listener)
	registerOnEvent(CurrentResource.Name(), explosionEvent)
}

func (e *eventManager) PlayerChangeVehicleSeat(listener playerChangeVehicleSeatListener) {
	e.playerChangeVehicleSeatEvents = append(e.playerChangeVehicleSeatEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerChangeVehicleSeat)
}

func (e *eventManager) PlayerDamage(listener playerDamageListener) {
	e.playerDamageEvents = append(e.playerDamageEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerDamage)
}

func (e *eventManager) PlayerDeath(listener playerDeathListener) {
	e.playerDeathEvents = append(e.playerDeathEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerDeath)
}

func (e *eventManager) PlayerEnterVehicle(listener playerEnterVehicleListener) {
	e.playerEnterVehicleEvents = append(e.playerEnterVehicleEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerEnterVehicle)
}

func (e *eventManager) PlayerLeaveVehicle(listener playerLeaveVehicleListener) {
	e.playerLeaveVehicleEvents = append(e.playerLeaveVehicleEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerLeaveVehicle)
}

func (e *eventManager) RemoveEntity(listener removeEntityListener) {
	e.removeEntityEvents = append(e.removeEntityEvents, listener)
	registerOnEvent(CurrentResource.Name(), removeEntityEvent)
}

func (e *eventManager) ResourceStart(listener resourceStartListener) {
	e.resourceStartEvents = append(e.resourceStartEvents, listener)
	registerOnEvent(CurrentResource.Name(), resourceStart)
}

func (e *eventManager) WeaponDamage(listener weaponDamageListener) {
	e.weaponDamageEvents = append(e.weaponDamageEvents, listener)
	registerOnEvent(CurrentResource.Name(), weaponDamageEvent)
}

func (e *eventManager) PlayerEnteringVehicle(listener playerEnteringVehicleListener) {
	e.playerEnteringVehicleEvents = append(e.playerEnteringVehicleEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerEnteringVehicle)
}

func (e *eventManager) EntityEnterColShape(listener entityEnterColShapeListener) {
	e.entityEnterColShapeEvents = append(e.entityEnterColShapeEvents, listener)
	registerOnEvent(CurrentResource.Name(), colshapeEvent)
}

func (e *eventManager) EntityLeaveColShape(listener entityLeaveColShapeListener) {
	e.entityLeaveColShapeEvents = append(e.entityLeaveColShapeEvents, listener)
	registerOnEvent(CurrentResource.Name(), colshapeEvent)
}

func (e *eventManager) StartFire(listener fireListener) {
	e.fireEvents = append(e.fireEvents, listener)
	registerOnEvent(CurrentResource.Name(), fireEvent)
}

func (e *eventManager) GlobalMetaChange(listener globalMetaDataChangeListener) {
	e.globalMetaDataChangeEvents = append(e.globalMetaDataChangeEvents, listener)
	registerOnEvent(CurrentResource.Name(), globalMetaChange)
}

func (e *eventManager) GlobalSyncedMetaChange(listener globalSyncedMetaDataChangeListener) {
	e.globalSyncedMetaDataChangeEvents = append(e.globalSyncedMetaDataChangeEvents, listener)
	registerOnEvent(CurrentResource.Name(), globalSyncedMetaChange)
}

func (e *eventManager) MetaChange(listener metaDataChangeListener) {
	e.metaDataChangeEvents = append(e.metaDataChangeEvents, listener)
	registerOnEvent(CurrentResource.Name(), metaChange)
}

func (e *eventManager) LocalSyncedMetaChange(listener localSyncedMetaDataChangeListener) {
	e.localSyncedMetaDataChangeEvents = append(e.localSyncedMetaDataChangeEvents, listener)
	registerOnEvent(CurrentResource.Name(), localSyncedMetaChange)
}

func (e *eventManager) NetOwnerChange(listener netOwnerChangeListener) {
	e.netOwnerChangeEvents = append(e.netOwnerChangeEvents, listener)
	registerOnEvent(CurrentResource.Name(), netOwnerChange)
}

func (e *eventManager) PlayerWeaponChange(listener playerWeaponChangeListener) {
	e.playerWeaponChangeEvents = append(e.playerWeaponChangeEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerWeaponChange)
}

func (e *eventManager) PlayerRequestControl(listener playerRequestControlListener) {
	e.playerRequestControlEvents = append(e.playerRequestControlEvents, listener)
	registerOnEvent(CurrentResource.Name(), playerRequestControl)
}

func (e *eventManager) ResourceError(listener resourceErrorListener) {
	e.resourceErrorEvents = append(e.resourceErrorEvents, listener)
	registerOnEvent(CurrentResource.Name(), resourceError)
}

func (e *eventManager) ResourceStop(listener resourceStopListener) {
	e.resourceStopEvents = append(e.resourceStopEvents, listener)
	registerOnEvent(CurrentResource.Name(), resourceStop)
}

func (e *eventManager) StartProjectile(listener startProjectileListener) {
	e.startProjectileEvents = append(e.startProjectileEvents, listener)
	registerOnEvent(CurrentResource.Name(), startProjectileEvent)
}

func (e *eventManager) StreamSyncedMetaChange(listener streamSyncedMetaDataChangeListener) {
	e.streamSyncedMetaDataChangeEvents = append(e.streamSyncedMetaDataChangeEvents, listener)
	registerOnEvent(CurrentResource.Name(), streamSyncedMetaChange)
}

func (e *eventManager) SyncedMetaChange(listener syncedMetaDataChangeListener) {
	e.syncedMetaDataChangeEvents = append(e.syncedMetaDataChangeEvents, listener)
	registerOnEvent(CurrentResource.Name(), syncedMetaChange)
}

func (e *eventManager) VehicleAttach(listener vehicleAttachListener) {
	e.vehicleAttachEvents = append(e.vehicleAttachEvents, listener)
	registerOnEvent(CurrentResource.Name(), vehicleAttach)
}

func (e *eventManager) VehicleDetach(listener vehicleDetachListener) {
	e.vehicleDetachEvents = append(e.vehicleDetachEvents, listener)
	registerOnEvent(CurrentResource.Name(), vehicleDetach)
}

func (e *eventManager) VehicleDestroy(listener vehicleDestroyListener) {
	e.vehicleDestroyEvents = append(e.vehicleDestroyEvents, listener)
	registerOnEvent(CurrentResource.Name(), vehicleDestroy)
}

func (e *eventManager) VehicleDamage(listener vehicleDamageListener) {
	e.vehicleDamageEvents = append(e.vehicleDamageEvents, listener)
	registerOnEvent(CurrentResource.Name(), vehicleDamage)
}

func (e *eventManager) ServerEvent(eventName string, listener scriptEventListener) {
	if e.serverScriptEvents == nil {
		e.serverScriptEvents = make(map[string][]reflect.Value)
	}
	e.serverScriptEvents[eventName] = append(e.serverScriptEvents[eventName], reflect.ValueOf(listener))
	registerOnEvent(CurrentResource.Name(), serverScriptEvent)
}

func (e *eventManager) AllServerEvents(listener scriptEventListener) {
	e.allServerScriptEvents = append(e.allServerScriptEvents, reflect.ValueOf(listener))
	registerOnEvent(CurrentResource.Name(), serverScriptEvent)
}

func (e *eventManager) ClientEvent(eventName string, listener scriptEventListener) {
	if e.clientScriptEvents == nil {
		e.clientScriptEvents = make(map[string][]reflect.Value)
	}
	e.clientScriptEvents[eventName] = append(e.clientScriptEvents[eventName], reflect.ValueOf(listener))
	registerOnEvent(CurrentResource.Name(), clientScriptEvent)
}

func (e *eventManager) AllClientEvents(listener scriptEventListener) {
	e.allClientScriptEvents = append(e.allClientScriptEvents, reflect.ValueOf(listener))
	registerOnEvent(CurrentResource.Name(), clientScriptEvent)
}

func Emit(eventName string, args ...interface{}) error {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	arr, err := encodeArgs(args)
	// TODO: for C.free
	if err != nil {
		return err
	}

	C.core_trigger_local_event(cEvent, arr)

	return nil
}

func EmitClient(player *Player, eventName string, args ...interface{}) error {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	arr, err := encodeArgs(args)
	defer C.free(unsafe.Pointer(arr.array))
	if err != nil {
		return err
	}

	C.core_trigger_client_event(player.ptr, cEvent, arr)
	return nil
}

func EmitClients(players []*Player, eventName string, args ...interface{}) error {
	clientSize := uint64(len(players))

	if clientSize < 1 {
		return errors.New("no players to emit to")
	}

	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	arr, err := encodeArgs(args)
	defer C.free(unsafe.Pointer(arr.array))
	if err != nil {
		return err
	}

	clientArrayPtr := C.malloc(C.size_t(clientSize) * C.size_t(8))
	clientArray := (*[1 << 30]unsafe.Pointer)(clientArrayPtr)
	defer C.free(clientArrayPtr)

	for i := uint64(0); i < clientSize; i++ {
		clientArray[i] = players[i].ptr
	}

	C.core_trigger_client_event_for(C.struct_array{
		array: clientArrayPtr,
		size:  C.ulonglong(clientSize),
	}, cEvent, arr)

	return nil
}

func EmitAllClients(eventName string, args ...interface{}) error {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	arr, err := encodeArgs(args)
	defer C.free(unsafe.Pointer(arr.array))
	if err != nil {
		return err
	}

	C.core_trigger_client_event_for_all(cEvent, arr)
	return nil
}

//export altServerScriptEvent
func altServerScriptEvent(cName *C.char, arr C.struct_array) {
	name := C.GoString(cName)
	eventName := reflect.ValueOf(name)

	args, err := decodeArgs(arr)
	if err != nil {
		LogError("ServerScriptEvent error:", err.Error())
	}

	allArgs := append([]reflect.Value{eventName}, args...)

	for i, event := range Once.allServerScriptEvents {
		event.Call(allArgs)
		Once.allServerScriptEvents = removeIndex(Once.allServerScriptEvents, i)
	}

	for i, event := range Once.serverScriptEvents[name] {
		event.Call(args)
		Once.serverScriptEvents[name] = removeIndex(Once.serverScriptEvents[name], i)
	}

	for _, event := range On.allServerScriptEvents {
		event.Call(allArgs)
	}

	for _, event := range On.serverScriptEvents[name] {
		event.Call(args)
	}
}

//export altClientScriptEvent
func altClientScriptEvent(p unsafe.Pointer, cName *C.char, arr C.struct_array) {
	name := C.GoString(cName)
	eventName := reflect.ValueOf(name)
	target := reflect.ValueOf(newPlayer(p))

	args, err := decodeArgs(arr)
	if err != nil {
		LogError("ClientScriptEvent error:", err.Error())
	}

	allArgs := append([]reflect.Value{target, eventName}, args...)
	targetArgs := append([]reflect.Value{target}, args...)

	for i, event := range Once.allClientScriptEvents {
		event.Call(allArgs)
		Once.allClientScriptEvents = removeIndex(Once.allClientScriptEvents, i)
	}

	for i, event := range Once.clientScriptEvents[name] {
		event.Call(targetArgs)
		Once.clientScriptEvents[name] = removeIndex(Once.clientScriptEvents[name], i)
	}

	for _, event := range On.allClientScriptEvents {
		event.Call(allArgs)
	}

	for _, event := range On.clientScriptEvents[name] {
		event.Call(targetArgs)
	}
}

//export altServerStartedEvent
func altServerStartedEvent() {
	for i, event := range Once.serverStartedEvents {
		event()
		Once.serverStartedEvents = removeIndex(Once.serverStartedEvents, i)
	}

	for _, event := range On.serverStartedEvents {
		event()
	}

	re := len(Once.serverStartedEvents) + len(On.serverStartedEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), serverStarted)
	}
}

//export altPlayerConnectEvent
func altPlayerConnectEvent(p unsafe.Pointer) {
	player := newPlayer(p)

	for i, event := range Once.playerConnectEvents {
		event(player)
		Once.playerConnectEvents = removeIndex(Once.playerConnectEvents, i)
	}

	for _, event := range On.playerConnectEvents {
		event(player)
	}

	re := len(Once.playerConnectEvents) + len(On.playerConnectEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerConnect)
	}
}

//export altConsoleCommandEvent
func altConsoleCommandEvent(cName *C.char, cArray C.struct_array) {
	name := C.GoString(cName)
	array := newStringArray(cArray.array, int(cArray.size))

	for i, event := range Once.consoleCommandEvents {
		event(name, array)
		Once.consoleCommandEvents = removeIndex(Once.consoleCommandEvents, i)
	}

	for _, event := range On.consoleCommandEvents {
		event(name, array)
	}

	re := len(Once.consoleCommandEvents) + len(On.consoleCommandEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), consoleCommandEvent)
	}
}

//export altPlayerDisconnectEvent
func altPlayerDisconnectEvent(p unsafe.Pointer, cReason *C.char) {
	reason := C.GoString(cReason)
	player := newPlayer(p)

	for i, event := range Once.playerDisconnectEvents {
		event(player, reason)
		Once.playerDisconnectEvents = removeIndex(Once.playerDisconnectEvents, i)
	}

	for _, event := range On.playerDisconnectEvents {
		event(player, reason)
	}

	re := len(Once.playerDisconnectEvents) + len(On.playerDisconnectEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerDisconnect)
	}
}

//export altExplosionEvent
func altExplosionEvent(p unsafe.Pointer, e C.struct_entity, pos C.struct_pos, explosionType C.short, explosionFX C.uint) C.int {
	player := newPlayer(p)
	goPos := Vector3{X: float32(pos.x), Y: float32(pos.y), Z: float32(pos.z)}
	expType := int16(explosionType)
	expFX := uint(explosionFX)
	entity := newEntity(e)

	cont := true

	for i, event := range Once.explosionEvents {
		c := event(player, entity, goPos, expType, expFX)
		if !c {
			cont = c
		}
		Once.explosionEvents = removeIndex(Once.explosionEvents, i)
	}

	for _, event := range On.explosionEvents {
		c := event(player, entity, goPos, expType, expFX)
		if !c {
			cont = c
		}
	}

	re := len(Once.explosionEvents) + len(On.explosionEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), explosionEvent)
	}

	return C.int(module.Bool2int(cont))
}

//export altPlayerChangeVehicleSeatEvent
func altPlayerChangeVehicleSeatEvent(p unsafe.Pointer, v unsafe.Pointer, old C.uchar, new C.uchar) {
	player := newPlayer(p)
	vehicle := newVehicle(v)
	oSeat := uint8(old)
	nSeat := uint8(new)

	for i, event := range Once.playerChangeVehicleSeatEvents {
		event(player, vehicle, oSeat, nSeat)
		Once.playerChangeVehicleSeatEvents = removeIndex(Once.playerChangeVehicleSeatEvents, i)
	}

	for _, event := range On.playerChangeVehicleSeatEvents {
		event(player, vehicle, oSeat, nSeat)
	}

	re := len(Once.playerChangeVehicleSeatEvents) + len(On.playerChangeVehicleSeatEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerChangeVehicleSeat)
	}
}

//export altPlayerDamageEvent
func altPlayerDamageEvent(p unsafe.Pointer, e C.struct_entity, healthDmg C.ushort, armourDmg C.ushort, weap C.ulong) {
	player := newPlayer(p)
	healthDamage := uint16(healthDmg)
	armourDamage := uint16(armourDmg)
	weapon := uint32(weap)
	entity := newEntity(e)

	for i, event := range Once.playerDamageEvents {
		event(player, entity, healthDamage, armourDamage, weapon)
		Once.playerDamageEvents = removeIndex(Once.playerDamageEvents, i)
	}

	for _, event := range On.playerDamageEvents {
		event(player, entity, healthDamage, armourDamage, weapon)
	}

	re := len(Once.playerDamageEvents) + len(On.playerDamageEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerDamage)
	}
}

//export altPlayerDeathEvent
func altPlayerDeathEvent(p unsafe.Pointer, e C.struct_entity, weap C.ulong) {
	player := newPlayer(p)
	weapon := uint32(weap)
	entity := newEntity(e)

	for i, event := range Once.playerDeathEvents {
		event(player, entity, weapon)
		Once.playerDeathEvents = removeIndex(Once.playerDeathEvents, i)
	}

	for _, event := range On.playerDeathEvents {
		event(player, entity, weapon)
	}

	re := len(Once.playerDeathEvents) + len(On.playerDeathEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerDeath)
	}
}

//export altPlayerEnterVehicleEvent
func altPlayerEnterVehicleEvent(p unsafe.Pointer, v unsafe.Pointer, s C.uchar) {
	player := newPlayer(p)
	vehicle := newVehicle(v)
	seat := uint8(s)

	for i, event := range Once.playerEnterVehicleEvents {
		event(player, vehicle, seat)
		Once.playerEnterVehicleEvents = removeIndex(Once.playerEnterVehicleEvents, i)
	}

	for _, event := range On.playerEnterVehicleEvents {
		event(player, vehicle, seat)
	}

	re := len(Once.playerEnterVehicleEvents) + len(On.playerEnterVehicleEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerEnterVehicle)
	}
}

//export altPlayerLeaveVehicleEvent
func altPlayerLeaveVehicleEvent(p unsafe.Pointer, v unsafe.Pointer, s C.uchar) {
	player := newPlayer(p)
	vehicle := newVehicle(v)
	seat := uint8(s)

	for i, event := range Once.playerLeaveVehicleEvents {
		event(player, vehicle, seat)
		Once.playerLeaveVehicleEvents = removeIndex(Once.playerLeaveVehicleEvents, i)
	}

	for _, event := range On.playerLeaveVehicleEvents {
		event(player, vehicle, seat)
	}

	re := len(Once.playerLeaveVehicleEvents) + len(On.playerLeaveVehicleEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerLeaveVehicle)
	}
}

//export altRemoveEntityEvent
func altRemoveEntityEvent(e C.struct_entity) {
	entity := newEntity(e)

	for i, event := range Once.removeEntityEvents {
		event(entity)
		Once.removeEntityEvents = removeIndex(Once.removeEntityEvents, i)
	}

	for _, event := range On.removeEntityEvents {
		event(entity)
	}

	re := len(Once.removeEntityEvents) + len(On.removeEntityEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), removeEntityEvent)
	}
}

//export altResourceStartEvent
func altResourceStartEvent(n *C.char) {
	name := C.GoString(n)

	for i, event := range Once.resourceStartEvents {
		event(name)
		Once.resourceStartEvents = removeIndex(Once.resourceStartEvents, i)
	}

	for _, event := range On.resourceStartEvents {
		event(name)
	}

	re := len(Once.resourceStartEvents) + len(On.resourceStartEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), resourceStart)
	}
}

//export altResourceStopEvent
func altResourceStopEvent(n *C.char) {
	name := C.GoString(n)

	for i, event := range Once.resourceStopEvents {
		event(name)
		Once.resourceStopEvents = removeIndex(Once.resourceStopEvents, i)
	}

	for _, event := range On.resourceStopEvents {
		event(name)
	}

	re := len(Once.resourceStopEvents) + len(On.resourceStopEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), resourceStop)
	}
}

//export altResourceErrorEvent
func altResourceErrorEvent(n *C.char) {
	name := C.GoString(n)

	for i, event := range Once.resourceErrorEvents {
		event(name)
		Once.resourceErrorEvents = removeIndex(Once.resourceErrorEvents, i)
	}

	for _, event := range On.resourceErrorEvents {
		event(name)
	}

	re := len(Once.resourceErrorEvents) + len(On.resourceErrorEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), resourceError)
	}
}

//export altWeaponDamageEvent
func altWeaponDamageEvent(p unsafe.Pointer, e C.struct_entity, weap C.ulong, dmg C.ushort, ofs C.struct_pos, bPart C.short) C.int {
	player := newPlayer(p)
	weapon := uint32(weap)
	damage := uint16(dmg)
	offset := Vector3{X: float32(ofs.x), Y: float32(ofs.y), Z: float32(ofs.z)}
	bodyPart := int8(bPart)
	entity := newEntity(e)

	cont := false

	for i, event := range Once.weaponDamageEvents {
		c := event(player, entity, weapon, damage, offset, bodyPart)
		if !c {
			cont = c
		}
		Once.weaponDamageEvents = removeIndex(Once.weaponDamageEvents, i)
	}

	for _, event := range On.weaponDamageEvents {
		c := event(player, entity, weapon, damage, offset, bodyPart)
		if !c {
			cont = c
		}
	}

	re := len(Once.weaponDamageEvents) + len(On.weaponDamageEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), weaponDamageEvent)
	}

	return C.int(module.Bool2int(!cont))
}

//export altPlayerEnteringVehicleEvent
func altPlayerEnteringVehicleEvent(p unsafe.Pointer, v unsafe.Pointer, s C.ushort) {
	player := newPlayer(p)
	vehicle := newVehicle(v)
	seat := uint8(s)

	for i, event := range Once.playerEnteringVehicleEvents {
		event(player, vehicle, seat)
		Once.playerEnteringVehicleEvents = removeIndex(Once.playerEnteringVehicleEvents, i)
	}

	for _, event := range On.playerEnteringVehicleEvents {
		event(player, vehicle, seat)
	}

	re := len(Once.playerEnteringVehicleEvents) + len(On.playerEnteringVehicleEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerEnteringVehicle)
	}
}

//export altColShapeEvent
func altColShapeEvent(c unsafe.Pointer, e C.struct_entity, s C.int) {
	colShape := newColShape(c)
	state := int(s) == 1
	entity := newEntity(e)

	if state {
		for i, event := range Once.entityEnterColShapeEvents {
			event(colShape, entity)
			Once.entityEnterColShapeEvents = removeIndex(Once.entityEnterColShapeEvents, i)
		}

		for _, event := range On.entityEnterColShapeEvents {
			event(colShape, entity)
		}
	} else {
		for i, event := range Once.entityLeaveColShapeEvents {
			event(colShape, entity)
			Once.entityLeaveColShapeEvents = removeIndex(Once.entityLeaveColShapeEvents, i)
		}

		for _, event := range On.entityLeaveColShapeEvents {
			event(colShape, entity)
		}
	}

	re := len(Once.entityEnterColShapeEvents) + len(On.entityEnterColShapeEvents) + len(Once.entityLeaveColShapeEvents) + len(On.entityLeaveColShapeEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), colshapeEvent)
	}
}

//export altFireEvent
func altFireEvent(p unsafe.Pointer, f C.struct_array) C.int {
	player := newPlayer(p)

	cFireInfoStructs, size := convertArray[C.struct_fireInfo](f)

	array := make([]FireInfo, size)

	for i, fireStruct := range cFireInfoStructs {
		array[i] = FireInfo{WeaponHash: uint32(fireStruct.weaponHash), Position: Vector3{X: float32(fireStruct.position.x), Y: float32(fireStruct.position.y), Z: float32(fireStruct.position.z)}}
	}

	cont := true

	for i, event := range Once.fireEvents {
		c := event(player, array)
		if !c {
			cont = c
		}
		Once.fireEvents = removeIndex(Once.fireEvents, i)
	}

	for _, event := range On.fireEvents {
		c := event(player, array)
		if !c {
			cont = c
		}
	}

	re := len(Once.fireEvents) + len(On.fireEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), fireEvent)
	}

	return C.int(module.Bool2int(cont))
}

//export altGlobalMetaDataChangeEvent
func altGlobalMetaDataChangeEvent(k *C.char, nVal C.struct_array, oVal C.struct_array) {
	key := C.GoString(k)

	oldValue, err := decodeReflect(oVal)
	if err != nil {
		LogError(err.Error())
		return
	}

	newValue, err := decodeReflect(nVal)
	if err != nil {
		LogError(err.Error())
		return
	}

	for i, event := range Once.globalMetaDataChangeEvents {
		event(key, oldValue, newValue)
		Once.globalMetaDataChangeEvents = removeIndex(Once.globalMetaDataChangeEvents, i)
	}

	for _, event := range On.globalMetaDataChangeEvents {
		event(key, newValue, oldValue)
	}

	re := len(Once.globalMetaDataChangeEvents) + len(On.globalMetaDataChangeEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), globalMetaChange)
	}
}

//export altGlobalSyncedMetaDataChangeEvent
func altGlobalSyncedMetaDataChangeEvent(k *C.char, nVal C.struct_array, oVal C.struct_array) {
	key := C.GoString(k)

	// FIXME:
	var oldValue interface{}
	var newValue interface{}

	for i, event := range Once.globalSyncedMetaDataChangeEvents {
		event(key, oldValue, newValue)
		Once.globalSyncedMetaDataChangeEvents = removeIndex(Once.globalSyncedMetaDataChangeEvents, i)
	}

	for _, event := range On.globalSyncedMetaDataChangeEvents {
		event(key, newValue, oldValue)
	}

	re := len(Once.globalSyncedMetaDataChangeEvents) + len(On.globalSyncedMetaDataChangeEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), globalSyncedMetaChange)
	}
}

//export altLocalSyncedMetaDataChangeEvent
func altLocalSyncedMetaDataChangeEvent(p unsafe.Pointer, cKey *C.char, cNewValue C.struct_array, cOldValue C.struct_array) {
	player := newPlayer(p)
	key := C.GoString(cKey)

	// FIXME:
	var oldValue interface{}
	var newValue interface{}

	for i, event := range Once.localSyncedMetaDataChangeEvents {
		event(player, key, oldValue, newValue)
		Once.localSyncedMetaDataChangeEvents = removeIndex(Once.localSyncedMetaDataChangeEvents, i)
	}

	for _, event := range On.localSyncedMetaDataChangeEvents {
		event(player, key, newValue, oldValue)
	}

	re := len(Once.localSyncedMetaDataChangeEvents) + len(On.localSyncedMetaDataChangeEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), localSyncedMetaChange)
	}
}

//export altMetaDataChangeEvent
func altMetaDataChangeEvent(cKey *C.char, cNewValue C.struct_array, cOldValue C.struct_array) {
	key := C.GoString(cKey)

	// FIXME:
	var oldValue interface{}
	var newValue interface{}

	for i, event := range Once.metaDataChangeEvents {
		event(key, oldValue, newValue)
		Once.metaDataChangeEvents = removeIndex(Once.metaDataChangeEvents, i)
	}

	for _, event := range On.metaDataChangeEvents {
		event(key, newValue, oldValue)
	}

	re := len(Once.metaDataChangeEvents) + len(On.metaDataChangeEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), metaChange)
	}
}

//export altNetOwnerChangeEvent
func altNetOwnerChangeEvent(e C.struct_entity, o unsafe.Pointer, oo unsafe.Pointer) {
	owner := newPlayer(o)
	oldOwner := newPlayer(oo)
	entity := newEntity(e)

	for i, event := range Once.netOwnerChangeEvents {
		event(entity, oldOwner, owner)
		Once.netOwnerChangeEvents = removeIndex(Once.netOwnerChangeEvents, i)
	}

	for _, event := range On.netOwnerChangeEvents {
		event(entity, owner, oldOwner)
	}

	re := len(Once.netOwnerChangeEvents) + len(On.netOwnerChangeEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), netOwnerChange)
	}
}

//export altPlayerWeaponChangeEvent
func altPlayerWeaponChangeEvent(p unsafe.Pointer, oWeap C.ulong, nWeap C.ulong) C.int {
	player := newPlayer(p)
	oldWeapon := uint32(oWeap)
	newWeapon := uint32(nWeap)

	cont := true

	for i, event := range Once.playerWeaponChangeEvents {
		c := event(player, oldWeapon, newWeapon)
		if !c {
			cont = c
		}
		Once.playerWeaponChangeEvents = removeIndex(Once.playerWeaponChangeEvents, i)
	}

	for _, event := range On.playerWeaponChangeEvents {
		c := event(player, oldWeapon, newWeapon)
		if !c {
			cont = c
		}
	}

	re := len(Once.playerWeaponChangeEvents) + len(On.playerWeaponChangeEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerWeaponChange)
	}

	return C.int(module.Bool2int(cont))
}

//export altPlayerRequestControlEvent
func altPlayerRequestControlEvent(p unsafe.Pointer, e C.struct_entity) C.int {
	player := newPlayer(p)
	entity := newEntity(e)

	ok := true

	for i, event := range Once.playerRequestControlEvents {
		c := event(player, entity)
		if !c {
			ok = c
		}
		Once.playerRequestControlEvents = removeIndex(Once.playerRequestControlEvents, i)
	}

	for _, event := range On.playerRequestControlEvents {
		c := event(player, entity)
		if !c {
			ok = c
		}
	}

	re := len(Once.playerRequestControlEvents) + len(On.playerRequestControlEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerRequestControl)
	}

	return C.int(module.Bool2int(ok))
}

//export altPlayerBeforeConnectEvent
func altPlayerBeforeConnectEvent(cHandle unsafe.Pointer, cInfo C.struct_connectionInfo, cReason *C.char) {
	info := newConnectionInfo(cHandle, cInfo)
	reason := C.GoString(cReason)

	for i, event := range Once.playerBeforeConnectEvents {
		event(info, reason)
		Once.playerBeforeConnectEvents = removeIndex(Once.playerBeforeConnectEvents, i)
	}

	for _, event := range On.playerBeforeConnectEvents {
		event(info, reason)
	}

	re := len(Once.playerBeforeConnectEvents) + len(On.playerBeforeConnectEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), playerBeforeConnect)
	}
}

//export altConnectionQueueAddEvent
func altConnectionQueueAddEvent(cHandle unsafe.Pointer, cInfo C.struct_connectionInfo) {
	info := newConnectionInfo(cHandle, cInfo)

	for i, event := range Once.connectionQueueAddEvents {
		event(info)
		Once.connectionQueueAddEvents = removeIndex(Once.connectionQueueAddEvents, i)
	}

	for _, event := range On.connectionQueueAddEvents {
		event(info)
	}

	re := len(Once.connectionQueueAddEvents) + len(On.connectionQueueAddEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), connectionQueueAdd)
	}
}

//export altConnectionQueueRemoveEvent
func altConnectionQueueRemoveEvent(cHandle unsafe.Pointer, cInfo C.struct_connectionInfo) {
	info := newConnectionInfo(cHandle, cInfo)

	for i, event := range Once.connectionQueueRemoveEvents {
		event(info)
		Once.connectionQueueRemoveEvents = removeIndex(Once.connectionQueueRemoveEvents, i)
	}

	for _, event := range On.connectionQueueRemoveEvents {
		event(info)
	}

	re := len(Once.connectionQueueRemoveEvents) + len(On.connectionQueueRemoveEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), globalMetaChange)
	}
}

//export altStartProjectileEvent
func altStartProjectileEvent(p unsafe.Pointer, pos C.struct_pos, dir C.struct_pos, aHash C.uint, wHash C.ulong) C.int {
	player := newPlayer(p)
	position := Vector3{X: float32(pos.x), Y: float32(pos.y), Z: float32(pos.z)}
	direction := Vector3{X: float32(dir.x), Y: float32(dir.y), Z: float32(dir.z)}
	ammoHash := uint16(aHash)
	weaponHash := uint32(wHash)

	cont := true

	for i, event := range Once.startProjectileEvents {
		c := event(player, position, direction, ammoHash, weaponHash)
		if !c {
			cont = c
		}
		Once.startProjectileEvents = removeIndex(Once.startProjectileEvents, i)
	}

	for _, event := range On.startProjectileEvents {
		c := event(player, position, direction, ammoHash, weaponHash)
		if !c {
			cont = c
		}
	}

	re := len(Once.startProjectileEvents) + len(On.startProjectileEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), startProjectileEvent)
	}

	return C.int(module.Bool2int(cont))
}

//export altStreamSyncedMetaDataChangeEvent
func altStreamSyncedMetaDataChangeEvent(e C.struct_entity, k *C.char, nVal C.struct_array, oVal C.struct_array) {
	key := C.GoString(k)

	// FIXME:
	var oldValue interface{}
	var newValue interface{}

	entity := newEntity(e)

	for i, event := range Once.streamSyncedMetaDataChangeEvents {
		event(entity, key, newValue, oldValue)
		Once.streamSyncedMetaDataChangeEvents = removeIndex(Once.streamSyncedMetaDataChangeEvents, i)
	}

	for _, event := range On.streamSyncedMetaDataChangeEvents {
		event(entity, key, newValue, oldValue)
	}

	re := len(Once.streamSyncedMetaDataChangeEvents) + len(On.streamSyncedMetaDataChangeEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), streamSyncedMetaChange)
	}
}

//export altSyncedMetaDataChangeEvent
func altSyncedMetaDataChangeEvent(e C.struct_entity, k *C.char, nVal C.struct_array, oVal C.struct_array) {
	key := C.GoString(k)

	// FIXME:
	var oldValue interface{}
	var newValue interface{}

	entity := newEntity(e)

	for i, event := range Once.syncedMetaDataChangeEvents {
		event(entity, key, newValue, oldValue)
		Once.syncedMetaDataChangeEvents = removeIndex(Once.syncedMetaDataChangeEvents, i)
	}

	for _, event := range On.syncedMetaDataChangeEvents {
		event(entity, key, newValue, oldValue)
	}

	re := len(Once.syncedMetaDataChangeEvents) + len(On.syncedMetaDataChangeEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), syncedMetaChange)
	}
}

//export altVehicleAttachEvent
func altVehicleAttachEvent(v unsafe.Pointer, a unsafe.Pointer) {
	vehicle := newVehicle(v)
	attached := newVehicle(a)

	for i, event := range Once.vehicleAttachEvents {
		event(vehicle, attached)
		Once.vehicleAttachEvents = removeIndex(Once.vehicleAttachEvents, i)
	}

	for _, event := range On.vehicleAttachEvents {
		event(vehicle, attached)
	}

	re := len(Once.vehicleAttachEvents) + len(On.vehicleAttachEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), vehicleAttach)
	}
}

//export altVehicleDetachEvent
func altVehicleDetachEvent(v unsafe.Pointer, a unsafe.Pointer) {
	vehicle := newVehicle(v)
	attached := newVehicle(a)

	for i, event := range Once.vehicleDetachEvents {
		event(vehicle, attached)
		Once.vehicleDetachEvents = removeIndex(Once.vehicleDetachEvents, i)
	}

	for _, event := range On.vehicleDetachEvents {
		event(vehicle, attached)
	}

	re := len(Once.vehicleDetachEvents) + len(On.vehicleDetachEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), vehicleDetach)
	}
}

//export altVehicleDestroyEvent
func altVehicleDestroyEvent(v unsafe.Pointer) {
	vehicle := newVehicle(v)

	for i, event := range Once.vehicleDestroyEvents {
		event(vehicle)
		Once.vehicleDestroyEvents = removeIndex(Once.vehicleDestroyEvents, i)
	}

	for _, event := range On.vehicleDestroyEvents {
		event(vehicle)
	}

	re := len(Once.vehicleDestroyEvents) + len(On.vehicleDestroyEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), vehicleDestroy)
	}
}

//export altVehicleDamageEvent
func altVehicleDamageEvent(v unsafe.Pointer, e C.struct_entity, body C.uint, additional C.uint, engine C.uint, tank C.uint, width C.uint) {
	vehicle := newVehicle(v)
	entity := newEntity(e)
	bodyDamage := uint32(body)
	additionalBodyDamage := uint32(additional)
	engineDamage := uint32(engine)
	tankDamage := uint32(tank)
	damageWidth := uint32(width)

	for i, event := range Once.vehicleDamageEvents {
		event(vehicle, entity, bodyDamage, additionalBodyDamage, engineDamage, tankDamage, damageWidth)
		Once.vehicleDamageEvents = removeIndex(Once.vehicleDamageEvents, i)
	}

	for _, event := range On.vehicleDamageEvents {
		event(vehicle, entity, bodyDamage, additionalBodyDamage, engineDamage, tankDamage, damageWidth)
	}

	re := len(Once.vehicleDamageEvents) + len(On.vehicleDamageEvents)
	if re < 1 {
		unregisterOnEvent(CurrentResource.Name(), vehicleDamage)
	}
}
