package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
import "C"
import (
	"unsafe"

	"github.com/timo972/altv-go-pkg/internal/module"
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
type playerBeforeConnectListener = func(connectionInfo ConnectionInfo, reason string) string
type playerDisconnectListener = func(p *Player, reason string)

type connectionQueueAddListener = func(connectionInfo ConnectionInfo) string
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

type vehicleAttachListener = func(vehicle *Vehicle, attachedVehicle *Vehicle)
type vehicleDetachListener = func(vehicle *Vehicle, detachedVehicle *Vehicle)
type netOwnerChangeListener = func(entity *Entity, owner *Player, oldOwner *Player)

type removeEntityListener = func(entity *Entity)

type consoleCommandListener = func(command string, args []string)

type allServerEventsListener = func(eventName string, args ...interface{})
type serverEventListener = func(args ...interface{})
type allClientEventsListener = func(player *Player, eventName string, args ...interface{})
type clientEventListener = func(player *Player, args ...interface{})

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
	resourceErrorEvents              []resourceErrorListener
	resourceStopEvents               []resourceStopListener
	startProjectileEvents            []startProjectileListener
	streamSyncedMetaDataChangeEvents []streamSyncedMetaDataChangeListener
	syncedMetaDataChangeEvents       []syncedMetaDataChangeListener
	vehicleAttachEvents              []vehicleAttachListener
	vehicleDetachEvents              []vehicleDetachListener
	vehicleDestroyEvents             []vehicleDestroyListener
	vehicleDamageEvents              []vehicleDamageListener
	serverScriptEvents               map[string][]serverEventListener
	clientScriptEvents               map[string][]clientEventListener
	allServerScriptEvents            []allServerEventsListener
	allClientScriptEvents            []allClientEventsListener
}

type listener interface {
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
	ResourceError(listener resourceErrorListener)
	ResourceStop(listener resourceStopListener)
	StartProjectile(listener startProjectileListener)
	StreamSyncedMetaChange(listener streamSyncedMetaDataChangeListener)
	SyncedMetaChange(listener syncedMetaDataChangeListener)
	VehicleAttach(listener vehicleAttachListener)
	VehicleDetach(listener vehicleDetachListener)
	VehicleDestroy(listener vehicleDestroyListener)
	VehicleDamage(listener vehicleDamageListener)
	AllServerEvents(listener allServerEventsListener)
	ServerEvent(eventName string, listener serverEventListener)
	AllClientEvents(listener allClientEventsListener)
	ClientEvent(eventName string, listener clientEventListener)
}

var On = &eventManager{}

func registerOnEvent(resource string, event uint16) {
	cresource := C.CString(resource)
	defer C.free(unsafe.Pointer(cresource))

	C.runtime_register_alt_event(cresource, C.ushort(event))
}

func (e eventManager) ServerStarted(listener serverStartedListener) {
	e.serverStartedEvents = append(e.serverStartedEvents, listener)
	registerOnEvent(Resource.Name, serverStarted)
}

func (e eventManager) PlayerConnect(listener playerConnectListener) {
	On.playerConnectEvents = append(On.playerConnectEvents, listener)
	registerOnEvent(Resource.Name, playerConnect)
}

func (e eventManager) PlayerBeforeConnect(listener playerBeforeConnectListener) {
	On.playerBeforeConnectEvents = append(On.playerBeforeConnectEvents, listener)
	registerOnEvent(Resource.Name, playerBeforeConnect)
}

func (e eventManager) ConnectionQueueAdd(listener connectionQueueAddListener) {
	On.connectionQueueAddEvents = append(On.connectionQueueAddEvents, listener)
	registerOnEvent(Resource.Name, connectionQueueAdd)
}

func (e eventManager) ConnectionQueueRemove(listener connectionQueueRemoveListener) {
	On.connectionQueueRemoveEvents = append(On.connectionQueueRemoveEvents, listener)
	registerOnEvent(Resource.Name, connectionQueueRemove)
}

func (e eventManager) ConsoleCommand(listener consoleCommandListener) {
	On.consoleCommandEvents = append(On.consoleCommandEvents, listener)
	registerOnEvent(Resource.Name, consoleCommandEvent)
}

func (e eventManager) PlayerDisconnect(listener playerDisconnectListener) {
	On.playerDisconnectEvents = append(On.playerDisconnectEvents, listener)
	registerOnEvent(Resource.Name, playerDisconnect)
}

func (e eventManager) Explosion(listener explosionListener) {
	On.explosionEvents = append(On.explosionEvents, listener)
	registerOnEvent(Resource.Name, explosionEvent)
}

func (e eventManager) PlayerChangeVehicleSeat(listener playerChangeVehicleSeatListener) {
	On.playerChangeVehicleSeatEvents = append(On.playerChangeVehicleSeatEvents, listener)
	registerOnEvent(Resource.Name, playerChangeVehicleSeat)
}

func (e eventManager) PlayerDamage(listener playerDamageListener) {
	On.playerDamageEvents = append(On.playerDamageEvents, listener)
	registerOnEvent(Resource.Name, playerDamage)
}

func (e eventManager) PlayerDeath(listener playerDeathListener) {
	On.playerDeathEvents = append(On.playerDeathEvents, listener)
	registerOnEvent(Resource.Name, playerDeath)
}

func (e eventManager) PlayerEnterVehicle(listener playerEnterVehicleListener) {
	On.playerEnterVehicleEvents = append(On.playerEnterVehicleEvents, listener)
	registerOnEvent(Resource.Name, playerEnterVehicle)
}

func (e eventManager) PlayerLeaveVehicle(listener playerLeaveVehicleListener) {
	On.playerLeaveVehicleEvents = append(On.playerLeaveVehicleEvents, listener)
	registerOnEvent(Resource.Name, playerLeaveVehicle)
}

func (e eventManager) RemoveEntity(listener removeEntityListener) {
	On.removeEntityEvents = append(On.removeEntityEvents, listener)
	registerOnEvent(Resource.Name, removeEntityEvent)
}

func (e eventManager) ResourceStart(listener resourceStartListener) {
	On.resourceStartEvents = append(On.resourceStartEvents, listener)
	registerOnEvent(Resource.Name, resourceStart)
}

func (e eventManager) WeaponDamage(listener weaponDamageListener) {
	On.weaponDamageEvents = append(On.weaponDamageEvents, listener)
	registerOnEvent(Resource.Name, weaponDamageEvent)
}

func (e eventManager) PlayerEnteringVehicle(listener playerEnteringVehicleListener) {
	On.playerEnteringVehicleEvents = append(On.playerEnteringVehicleEvents, listener)
	registerOnEvent(Resource.Name, playerEnteringVehicle)
}

func (e eventManager) EntityEnterColShape(listener entityEnterColShapeListener) {
	On.entityEnterColShapeEvents = append(On.entityEnterColShapeEvents, listener)
	registerOnEvent(Resource.Name, colshapeEvent)
}

func (e eventManager) EntityLeaveColShape(listener entityLeaveColShapeListener) {
	On.entityLeaveColShapeEvents = append(On.entityLeaveColShapeEvents, listener)
	registerOnEvent(Resource.Name, colshapeEvent)
}

func (e eventManager) StartFire(listener fireListener) {
	On.fireEvents = append(On.fireEvents, listener)
	registerOnEvent(Resource.Name, fireEvent)
}

func (e eventManager) GlobalMetaChange(listener globalMetaDataChangeListener) {
	On.globalMetaDataChangeEvents = append(On.globalMetaDataChangeEvents, listener)
	registerOnEvent(Resource.Name, globalMetaChange)
}

func (e eventManager) GlobalSyncedMetaChange(listener globalSyncedMetaDataChangeListener) {
	On.globalSyncedMetaDataChangeEvents = append(On.globalSyncedMetaDataChangeEvents, listener)
	registerOnEvent(Resource.Name, globalSyncedMetaChange)
}

func (e eventManager) MetaChange(listener metaDataChangeListener) {
	On.metaDataChangeEvents = append(On.metaDataChangeEvents, listener)
	registerOnEvent(Resource.Name, metaChange)
}

func (e eventManager) LocalSyncedMetaChange(listener localSyncedMetaDataChangeListener) {
	On.localSyncedMetaDataChangeEvents = append(On.localSyncedMetaDataChangeEvents, listener)
	registerOnEvent(Resource.Name, localSyncedMetaChange)
}

func (e eventManager) NetOwnerChange(listener netOwnerChangeListener) {
	On.netOwnerChangeEvents = append(On.netOwnerChangeEvents, listener)
	registerOnEvent(Resource.Name, netOwnerChange)
}

func (e eventManager) PlayerWeaponChange(listener playerWeaponChangeListener) {
	On.playerWeaponChangeEvents = append(On.playerWeaponChangeEvents, listener)
	registerOnEvent(Resource.Name, playerWeaponChange)
}

func (e eventManager) ResourceError(listener resourceErrorListener) {
	On.resourceErrorEvents = append(On.resourceErrorEvents, listener)
	registerOnEvent(Resource.Name, resourceError)
}

func (e eventManager) ResourceStop(listener resourceStopListener) {
	On.resourceStopEvents = append(On.resourceStopEvents, listener)
	registerOnEvent(Resource.Name, resourceStop)
}

func (e eventManager) StartProjectile(listener startProjectileListener) {
	On.startProjectileEvents = append(On.startProjectileEvents, listener)
	registerOnEvent(Resource.Name, startProjectileEvent)
}

func (e eventManager) StreamSyncedMetaChange(listener streamSyncedMetaDataChangeListener) {
	On.streamSyncedMetaDataChangeEvents = append(On.streamSyncedMetaDataChangeEvents, listener)
	registerOnEvent(Resource.Name, streamSyncedMetaChange)
}

func (e eventManager) SyncedMetaChange(listener syncedMetaDataChangeListener) {
	On.syncedMetaDataChangeEvents = append(On.syncedMetaDataChangeEvents, listener)
	registerOnEvent(Resource.Name, syncedMetaChange)
}

func (e eventManager) VehicleAttach(listener vehicleAttachListener) {
	On.vehicleAttachEvents = append(On.vehicleAttachEvents, listener)
	registerOnEvent(Resource.Name, vehicleAttach)
}

func (e eventManager) VehicleDetach(listener vehicleDetachListener) {
	On.vehicleDetachEvents = append(On.vehicleDetachEvents, listener)
	registerOnEvent(Resource.Name, vehicleDetach)
}

func (e eventManager) VehicleDestroy(listener vehicleDestroyListener) {
	On.vehicleDestroyEvents = append(On.vehicleDestroyEvents, listener)
	registerOnEvent(Resource.Name, vehicleDestroy)
}

func (e eventManager) VehicleDamage(listener vehicleDamageListener) {
	On.vehicleDamageEvents = append(On.vehicleDamageEvents, listener)
	registerOnEvent(Resource.Name, vehicleDamage)
}

func (e eventManager) ServerEvent(eventName string, listener serverEventListener) {
	if On.serverScriptEvents == nil {
		On.serverScriptEvents = make(map[string][]serverEventListener)
	}
	On.serverScriptEvents[eventName] = append(On.serverScriptEvents[eventName], listener)
	registerOnEvent(Resource.Name, serverScriptEvent)
}

func (e eventManager) AllServerEvents(listener allServerEventsListener) {
	On.allServerScriptEvents = append(On.allServerScriptEvents, listener)
	registerOnEvent(Resource.Name, serverScriptEvent)
}

func (e eventManager) ClientEvent(eventName string, listener clientEventListener) {
	if On.clientScriptEvents == nil {
		On.clientScriptEvents = make(map[string][]clientEventListener)
	}
	On.clientScriptEvents[eventName] = append(On.clientScriptEvents[eventName], listener)
	registerOnEvent(Resource.Name, clientScriptEvent)
}

func (e eventManager) AllClientEvents(listener allClientEventsListener) {
	On.allClientScriptEvents = append(On.allClientScriptEvents, listener)
	registerOnEvent(Resource.Name, clientScriptEvent)
}

func Emit(eventName string, args ...interface{}) {
	/*cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	argPtr, argSize := newMValueArray(args)
	defer C.free(unsafe.Pointer(argPtr))

	C.core_trigger_local_event(cEvent, argPtr, argSize)*/
}

func EmitClient(player *Player, eventName string, args ...interface{}) {
	/*cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	argPtr, argSize := newMValueArray(args)
	defer C.free(unsafe.Pointer(argPtr))

	C.core_trigger_client_event(player.Ptr, cEvent, argPtr, argSize)*/
}

func EmitClients(players []*Player, eventName string, args ...interface{}) {
	/*clientSize := uint64(len(players))

	if clientSize < 1 {
		return
	}

	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	argPtr, argSize := newMValueArray(args)
	defer C.free(unsafe.Pointer(argPtr))

	clientArrayPtr := C.malloc(C.size_t(clientSize) * C.size_t(8))
	clientArray := (*[1 << 30]unsafe.Pointer)(clientArrayPtr)
	defer C.free(clientArrayPtr)

	for i := uint64(0); i < clientSize; i++ {
		clientArray[i] = players[i].Ptr
	}

	C.core_trigger_client_event_for((*unsafe.Pointer)(clientArrayPtr), C.ulonglong(clientSize), cEvent, argPtr, argSize)*/
}

func EmitAllClients(eventName string, args ...interface{}) {
	/*cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	argPtr, argSize := newMValueArray(args)
	defer C.free(unsafe.Pointer(argPtr))

	C.core_trigger_client_event_for_all(cEvent, argPtr, argSize)*/
}

//export altServerScriptEvent
func altServerScriptEvent(cName *C.char, cMValues unsafe.Pointer, size C.ulonglong) {
	name := C.GoString(cName)

	args := convertMValueArray(cMValues, size)

	for _, event := range On.allServerScriptEvents {
		event(name, args...)
	}

	for _, event := range On.serverScriptEvents[name] {
		event(args...)
	}
}

//export altClientScriptEvent
func altClientScriptEvent(p unsafe.Pointer, cName *C.char, cMValues unsafe.Pointer, size C.ulonglong) {
	name := C.GoString(cName)
	player := newPlayer(p)

	args := convertMValueArray(cMValues, size)

	for _, event := range On.allClientScriptEvents {
		event(player, name, args...)
	}

	for _, event := range On.clientScriptEvents[name] {
		event(player, args...)
	}
}

//export altServerStartedEvent
func altServerStartedEvent() {
	for _, event := range On.serverStartedEvents {
		event()
	}
}

//export altPlayerConnectEvent
func altPlayerConnectEvent(p unsafe.Pointer) {
	player := newPlayer(p)
	for _, event := range On.playerConnectEvents {
		event(player)
	}
}

//export altConsoleCommandEvent
func altConsoleCommandEvent(cName *C.char, cArray C.struct_array) {
	name := C.GoString(cName)
	//cStrings, size := convertArray[*C.char](cArray)

	// array := make([]string, 0)

	//for i, cString := range cStrings {
	//	array[i] = C.GoString(cString)
	//}
	array := newStringArray(cArray.array, int(cArray.size))

	for _, event := range On.consoleCommandEvents {
		event(name, array)
	}
}

//export altPlayerDisconnectEvent
func altPlayerDisconnectEvent(p unsafe.Pointer, cReason *C.char) {
	reason := C.GoString(cReason)
	player := newPlayer(p)
	for _, event := range On.playerDisconnectEvents {
		event(player, reason)
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

	for _, event := range On.explosionEvents {
		c := event(player, entity, goPos, expType, expFX)
		if !c {
			cont = c
		}
	}

	return C.int(module.Bool2int(cont))
}

//export altPlayerChangeVehicleSeatEvent
func altPlayerChangeVehicleSeatEvent(p unsafe.Pointer, v unsafe.Pointer, old C.uchar, new C.uchar) {
	player := newPlayer(p)
	vehicle := newVehicle(v)
	oSeat := uint8(old)
	nSeat := uint8(new)

	for _, event := range On.playerChangeVehicleSeatEvents {
		event(player, vehicle, oSeat, nSeat)
	}
}

//export altPlayerDamageEvent
func altPlayerDamageEvent(p unsafe.Pointer, e C.struct_entity, healthDmg C.ushort, armourDmg C.ushort, weap C.ulong) {
	player := newPlayer(p)
	healthDamage := uint16(healthDmg)
	armourDamage := uint16(armourDmg)
	weapon := uint32(weap)
	entity := newEntity(e)

	for _, event := range On.playerDamageEvents {
		event(player, entity, healthDamage, armourDamage, weapon)
	}
}

//export altPlayerDeathEvent
func altPlayerDeathEvent(p unsafe.Pointer, e C.struct_entity, weap C.ulong) {
	player := newPlayer(p)
	weapon := uint32(weap)
	entity := newEntity(e)

	for _, event := range On.playerDeathEvents {
		event(player, entity, weapon)
	}
}

//export altPlayerEnterVehicleEvent
func altPlayerEnterVehicleEvent(p unsafe.Pointer, v unsafe.Pointer, s C.uchar) {
	player := newPlayer(p)
	vehicle := newVehicle(v)
	seat := uint8(s)

	for _, event := range On.playerEnterVehicleEvents {
		event(player, vehicle, seat)
	}
}

//export altPlayerLeaveVehicleEvent
func altPlayerLeaveVehicleEvent(p unsafe.Pointer, v unsafe.Pointer, s C.uchar) {
	player := newPlayer(p)
	vehicle := newVehicle(v)
	seat := uint8(s)

	for _, event := range On.playerLeaveVehicleEvents {
		event(player, vehicle, seat)
	}
}

//export altRemoveEntityEvent
func altRemoveEntityEvent(e C.struct_entity) {
	entity := newEntity(e)

	for _, event := range On.removeEntityEvents {
		event(entity)
	}
}

//export altResourceStartEvent
func altResourceStartEvent(n *C.char) {
	name := C.GoString(n)

	for _, event := range On.resourceStartEvents {
		event(name)
	}
}

//export altResourceStopEvent
func altResourceStopEvent(n *C.char) {
	name := C.GoString(n)

	for _, event := range On.resourceStopEvents {
		event(name)
	}
}

//export altResourceErrorEvent
func altResourceErrorEvent(n *C.char) {
	name := C.GoString(n)

	for _, event := range On.resourceErrorEvents {
		event(name)
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

	for _, event := range On.weaponDamageEvents {
		c := event(player, entity, weapon, damage, offset, bodyPart)
		if !c {
			cont = c
		}
	}

	return C.int(module.Bool2int(!cont))
}

//export altPlayerEnteringVehicleEvent
func altPlayerEnteringVehicleEvent(p unsafe.Pointer, v unsafe.Pointer, s C.ushort) {
	player := newPlayer(p)
	vehicle := newVehicle(v)
	seat := uint8(s)

	for _, event := range On.playerEnteringVehicleEvents {
		event(player, vehicle, seat)
	}
}

//export altColShapeEvent
func altColShapeEvent(c unsafe.Pointer, e C.struct_entity, s C.int) {
	colShape := newColShape(c)
	state := int(s) == 1
	entity := newEntity(e)

	if state {
		for _, event := range On.entityEnterColShapeEvents {
			event(colShape, entity)
		}
	} else {
		for _, event := range On.entityLeaveColShapeEvents {
			event(colShape, entity)
		}
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

	for _, event := range On.fireEvents {
		c := event(player, array)
		if !c {
			cont = c
		}
	}

	return C.int(module.Bool2int(cont))
}

//export altGlobalMetaDataChangeEvent
func altGlobalMetaDataChangeEvent(k *C.char, nVal C.struct_metaData, oVal C.struct_metaData) {
	key := C.GoString(k)
	newVal := &MValue{Ptr: nVal.Ptr, Type: uint8(nVal.Type)}
	oldVal := &MValue{Ptr: oVal.Ptr, Type: uint8(oVal.Type)}
	var oldValue interface{}
	var newValue interface{}

	oldVal.Value(&oldValue)
	newVal.Value(&newValue)

	for _, event := range On.globalMetaDataChangeEvents {
		event(key, newValue, oldValue)
	}
}

//export altGlobalSyncedMetaDataChangeEvent
func altGlobalSyncedMetaDataChangeEvent(k *C.char, nVal C.struct_metaData, oVal C.struct_metaData) {
	key := C.GoString(k)
	newVal := &MValue{Ptr: nVal.Ptr, Type: uint8(nVal.Type)}
	oldVal := &MValue{Ptr: oVal.Ptr, Type: uint8(oVal.Type)}

	var oldValue interface{}
	var newValue interface{}

	oldVal.Value(&oldValue)
	newVal.Value(&newValue)

	for _, event := range On.globalSyncedMetaDataChangeEvents {
		event(key, newValue, oldValue)
	}
}

//export altLocalSyncedMetaDataChangeEvent
func altLocalSyncedMetaDataChangeEvent(p unsafe.Pointer, cKey *C.char, cNewValue C.struct_metaData, cOldValue C.struct_metaData) {
	player := newPlayer(p)
	key := C.GoString(cKey)
	newVal := &MValue{Ptr: cNewValue.Ptr, Type: uint8(cNewValue.Type)}
	oldVal := &MValue{Ptr: cOldValue.Ptr, Type: uint8(cOldValue.Type)}

	var oldValue interface{}
	var newValue interface{}

	oldVal.Value(&oldValue)
	newVal.Value(&newValue)

	for _, event := range On.localSyncedMetaDataChangeEvents {
		event(player, key, newValue, oldValue)
	}
}

//export altMetaDataChangeEvent
func altMetaDataChangeEvent(cKey *C.char, cNewValue C.struct_metaData, cOldValue C.struct_metaData) {
	key := C.GoString(cKey)
	newVal := &MValue{Ptr: cNewValue.Ptr, Type: uint8(cNewValue.Type)}
	oldVal := &MValue{Ptr: cOldValue.Ptr, Type: uint8(cOldValue.Type)}

	var oldValue interface{}
	var newValue interface{}

	oldVal.Value(&oldValue)
	newVal.Value(&newValue)

	for _, event := range On.metaDataChangeEvents {
		event(key, newValue, oldValue)
	}
}

//export altNetOwnerChangeEvent
func altNetOwnerChangeEvent(e C.struct_entity, o unsafe.Pointer, oo unsafe.Pointer) {
	owner := newPlayer(o)
	oldOwner := newPlayer(oo)
	entity := newEntity(e)

	for _, event := range On.netOwnerChangeEvents {
		event(entity, owner, oldOwner)
	}
}

//export altPlayerWeaponChangeEvent
func altPlayerWeaponChangeEvent(p unsafe.Pointer, oWeap C.ulong, nWeap C.ulong) C.int {
	player := newPlayer(p)
	oldWeapon := uint32(oWeap)
	newWeapon := uint32(nWeap)

	cont := true

	for _, event := range On.playerWeaponChangeEvents {
		c := event(player, oldWeapon, newWeapon)
		if !c {
			cont = c
		}
	}

	return C.int(module.Bool2int(cont))
}

//export altPlayerBeforeConnectEvent
func altPlayerBeforeConnectEvent(cInfo C.struct_connectionInfo, cReason *C.char) *C.char {
	info := newConnectionInfo(cInfo)
	reason := C.GoString(cReason)

	// FIXME: C.CString memory leak?

	for _, event := range On.playerBeforeConnectEvents {
		r := event(info, reason)
		if r != "" {
			return C.CString(r)
		}
	}

	return C.CString("")
}

//export altConnectionQueueAddEvent
func altConnectionQueueAddEvent(cInfo C.struct_connectionInfo) *C.char {
	info := newConnectionInfo(cInfo)

	// FIXME: C.CString memory leak?

	for _, event := range On.connectionQueueAddEvents {
		r := event(info)
		if r != "" {
			return C.CString(r)
		}
	}

	return C.CString("")
}

//export altConnectionQueueRemoveEvent
func altConnectionQueueRemoveEvent(cInfo C.struct_connectionInfo) {
	info := newConnectionInfo(cInfo)

	for _, event := range On.connectionQueueRemoveEvents {
		event(info)
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

	for _, event := range On.startProjectileEvents {
		c := event(player, position, direction, ammoHash, weaponHash)
		if !c {
			cont = c
		}
	}

	return C.int(module.Bool2int(cont))
}

//export altStreamSyncedMetaDataChangeEvent
func altStreamSyncedMetaDataChangeEvent(e C.struct_entity, k *C.char, nVal C.struct_metaData, oVal C.struct_metaData) {
	key := C.GoString(k)
	newVal := &MValue{Ptr: nVal.Ptr, Type: uint8(nVal.Type)}
	oldVal := &MValue{Ptr: oVal.Ptr, Type: uint8(oVal.Type)}

	var oldValue interface{}
	var newValue interface{}

	oldVal.Value(&oldValue)
	newVal.Value(&newValue)

	entity := newEntity(e)

	for _, event := range On.streamSyncedMetaDataChangeEvents {
		event(entity, key, newValue, oldValue)
	}
}

//export altSyncedMetaDataChangeEvent
func altSyncedMetaDataChangeEvent(e C.struct_entity, k *C.char, nVal C.struct_metaData, oVal C.struct_metaData) {
	key := C.GoString(k)
	newVal := &MValue{Ptr: nVal.Ptr, Type: uint8(nVal.Type)}
	oldVal := &MValue{Ptr: oVal.Ptr, Type: uint8(oVal.Type)}

	var oldValue interface{}
	var newValue interface{}

	oldVal.Value(&oldValue)
	newVal.Value(&newValue)

	entity := newEntity(e)

	for _, event := range On.streamSyncedMetaDataChangeEvents {
		event(entity, key, newValue, oldValue)
	}
}

//export altVehicleAttachEvent
func altVehicleAttachEvent(v unsafe.Pointer, a unsafe.Pointer) {
	vehicle := newVehicle(v)
	attached := newVehicle(a)

	for _, event := range On.vehicleAttachEvents {
		event(vehicle, attached)
	}
}

//export altVehicleDetachEvent
func altVehicleDetachEvent(v unsafe.Pointer, a unsafe.Pointer) {
	vehicle := newVehicle(v)
	attached := newVehicle(a)

	for _, event := range On.vehicleDetachEvents {
		event(vehicle, attached)
	}
}

//export altVehicleDestroyEvent
func altVehicleDestroyEvent(v unsafe.Pointer) {
	vehicle := newVehicle(v)

	for _, event := range On.vehicleDestroyEvents {
		event(vehicle)
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

	for _, event := range On.vehicleDamageEvents {
		event(vehicle, entity, bodyDamage, additionalBodyDamage, engineDamage, tankDamage, damageWidth)
	}
}
