package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
import "C"
import (
	"unsafe"
)

type eventType = uint16

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

type playerConnectListener = func(p *Player)
type playerDisconnectListener = func(p *Player, reason string)
type consoleCommandListener = func(command string, args []string)
type explosionListener = func(p *Player, t interface{}, pos Vector3, explosionType int16, explosionFX uint) bool
type playerChangeVehicleSeatListener = func(p *Player, v *Vehicle, oldSeat uint8, newSeat uint8)
type playerDamageListener = func(p *Player, attacker interface{}, healthDamage uint16, armourDamage uint16, weapon uint32)
type playerDeathListener = func(p *Player, killer interface{}, weapon uint32)
type playerEnterVehicleListener = func(p *Player, v *Vehicle, seat uint8)
type playerEnteringVehicleListener = func(p *Player, v *Vehicle, seat uint8)
type playerLeaveVehicleListener = func(p *Player, v *Vehicle, seat uint8)
type removeEntityListener = func(entity interface{})
type resourceStartListener = func(resourceName string)
type entityEnterColShapeListener = func(colShape *ColShape, entity interface{})
type entityLeaveColShapeListener = func(colShape *ColShape, entity interface{})
type fireListener = func(player *Player, fires []FireInfo) bool
type globalMetaDataChangeListener = func(key string, newValue interface{}, oldValue interface{})
type globalSyncedMetaDataChangeListener func(key string, newValue interface{}, oldValue interface{})
type netOwnerChangeListener = func(entity interface{}, owner *Player, oldOwner *Player)
type playerWeaponChangeListener = func(player *Player, oldWeapon uint32, newWeapon uint32)
type resourceErrorListener = func(resourceName string)
type resourceStopListener = func(resourceName string)
type startProjectileListener = func(player *Player, position Vector3, direction Vector3, ammoHash uint16, weaponHash uint32) bool
type streamSyncedMetaDataChangeListener = func(entity interface{}, key string, newValue interface{}, oldValue interface{})
type syncedMetaDataChangeListener = func(entity interface{}, key string, newValue interface{}, oldValue interface{})
type vehicleAttachListener = func(vehicle *Vehicle, attachedVehicle *Vehicle)
type vehicleDestroyListener = func(vehicle *Vehicle)
type vehicleDetachListener = func(vehicle *Vehicle, detachedVehicle *Vehicle)

// TODO bodyPart ENUM
type weaponDamageListener = func(source *Player, target interface{}, weapon uint32, damage uint16, offset Vector3, bodyPart int8) bool
type allServerEventsListener = func(eventName string, args ...interface{})
type serverEventListener = func(args ...interface{})
type allClientEventsListener = func(player *Player, eventName string, args ...interface{})
type clientEventListener = func(player *Player, args ...interface{})

type eventManager struct {
	playerConnectEvents              []playerConnectListener
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
	serverScriptEvents               map[string][]serverEventListener
	clientScriptEvents               map[string][]clientEventListener
	allServerScriptEvents 			 []allServerEventsListener
	allClientScriptEvents 			 []allClientEventsListener
}

type listener interface {
	PlayerConnect(listener playerConnectListener)
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
	AllServerEvents(listener allServerEventsListener)
	ServerEvent(eventName string, listener serverEventListener)
	AllClientEvents(listener allClientEventsListener)
	ClientEvent(eventName string, listener clientEventListener)
}

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

func (e eventManager) NetOwnerChange(listener netOwnerChangeListener) {
	On.netOwnerChangeEvents = append(On.netOwnerChangeEvents, listener)
	registerOnEvent(Resource.Name, netownerChange)
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

func createArgArray(args []interface{}) (*C.struct_data, C.ulonglong) {
	size := len(args)
	ptr := C.malloc(C.size_t(C.sizeof_CustomData * size))
	cArray := (*[1 << 30]C.struct_data)(ptr)

	for i := 0; i < size; i++ {
		mValue := CreateMValue(args[i])

		cArray[i] = C.struct_data{mValue: mValue.Ptr, Type: C.uint(mValue.Type)}
	}

	return (*C.struct_data)(ptr), C.ulonglong(size)
}

func EmitServer(eventName string, args ...interface{}) {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	argPtr, argSize := createArgArray(args)
	defer C.free(unsafe.Pointer(argPtr))

	C.core_trigger_local_event(cEvent, argPtr, argSize)
}

func EmitClient(player *Player, eventName string, args... interface{}) {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	argPtr, argSize := createArgArray(args)
	defer C.free(unsafe.Pointer(argPtr))

	C.core_trigger_client_event(player.Ptr, cEvent, argPtr, argSize)
}

func EmitClients(players []*Player, eventName string, args... interface{}) {
	clientSize := uint64(len(players))

	if clientSize < 1 {
		return
	}

	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	argPtr, argSize := createArgArray(args)
	defer C.free(unsafe.Pointer(argPtr))

	clientArrayPtr := C.malloc(C.size_t(clientSize) * C.size_t(8))
	clientArray := (*[1 << 30]unsafe.Pointer)(clientArrayPtr)
	defer C.free(clientArrayPtr)

	for i := uint64(0); i < clientSize; i++ {
		clientArray[i] = players[i].Ptr
	}

	C.core_trigger_client_event_for((*unsafe.Pointer)(clientArrayPtr), C.ulonglong(clientSize), cEvent, argPtr, argSize)
}

func EmitAllClients(eventName string, args... interface{}) {
	cEvent := C.CString(eventName)
	defer C.free(unsafe.Pointer(cEvent))

	argPtr, argSize := createArgArray(args)
	defer C.free(unsafe.Pointer(argPtr))

	C.core_trigger_client_event_for_all(cEvent, argPtr, argSize)
}

//export altServerScriptEvent
func altServerScriptEvent(cName *C.char, cMValues unsafe.Pointer, _size C.ulonglong) {
	name := C.GoString(cName)

	size := uint64(_size)

	args := make([]interface{}, 0)

	cMValueStructs := (*[1 << 30]C.struct_metaData)(cMValues)[:size:size]

	for i := uint64(0); i < size; i++ {
		cMVal := cMValueStructs[i]
		_type := uint8(cMVal.Type)

		mValue := &MValue{Ptr: cMVal.Ptr, Type: _type, Value: nil}

		val := mValue.GetValue()

		args = append(args, val)
	}

	for _, event := range On.allServerScriptEvents {
		event(name, args...)
	}

	for _, event := range On.serverScriptEvents[name] {
		event(args...)
	}
}

//export altClientScriptEvent
func altClientScriptEvent(p unsafe.Pointer, cName *C.char, cMValues unsafe.Pointer, _size C.ulonglong) {
	name := C.GoString(cName)
	player := NewPlayer(p)

	size := uint64(_size)

	args := make([]interface{}, 0)

	cMValueStructs := (*[1 << 30]C.struct_metaData)(cMValues)[:size:size]

	for i := uint64(0); i < size; i++ {
		cMVal := cMValueStructs[i]
		_type := uint8(cMVal.Type)

		mValue := &MValue{Ptr: cMVal.Ptr, Type: _type, Value: nil}

		val := mValue.GetValue()

		args = append(args, val)
	}

	for _, event := range On.allClientScriptEvents {
		event(player, name, args...)
	}

	for _, event := range On.clientScriptEvents[name] {
		event(player, args...)
	}
}

//export altPlayerConnectEvent
func altPlayerConnectEvent(player unsafe.Pointer) {
	for _, event := range On.playerConnectEvents {
		player := NewPlayer(player)
		event(player)
	}
}

//export altConsoleCommandEvent
func altConsoleCommandEvent(cName *C.char, cArray **C.char, cSize C.ulonglong) {
	name := C.GoString(cName)

	size := int(cSize)
	cStrings := (*[1 << 28]*C.char)(unsafe.Pointer(cArray))[:size:size]

	array := make([]string, size)

	for i, cString := range cStrings {
		array[i] = C.GoString(cString)
	}

	for _, event := range On.consoleCommandEvents {
		event(name, array)
	}
}

//export altPlayerDisconnectEvent
func altPlayerDisconnectEvent(p unsafe.Pointer, cReason *C.char) {
	reason := C.GoString(cReason)
	player := NewPlayer(p)
	for _, event := range On.playerDisconnectEvents {
		event(player, reason)
	}
}

//export altExplosionEvent
func altExplosionEvent(p unsafe.Pointer, e C.struct_entity, pos C.struct_pos, explosionType C.short, explosionFX C.uint) {
	player := NewPlayer(p)
	goPos := Vector3{X: float32(pos.x), Y: float32(pos.y), Z: float32(pos.z)}
	expType := int16(explosionType)
	expFX := uint(explosionFX)

	var entity interface{}
	entityType := BaseObjectType(e.Type)

	if entityType == PlayerObject {
		entity = NewPlayer(e.Ptr)
	} else if entityType == VehicleObject {
		entity = NewVehicle(e.Ptr)
	}

	for _, event := range On.explosionEvents {
		event(player, entity, goPos, expType, expFX)
	}
}

//export altPlayerChangeVehicleSeatEvent
func altPlayerChangeVehicleSeatEvent(p unsafe.Pointer, v unsafe.Pointer, old C.uchar, new C.uchar) {
	player := NewPlayer(p)
	vehicle := NewVehicle(v)
	oSeat := uint8(old)
	nSeat := uint8(new)

	for _, event := range On.playerChangeVehicleSeatEvents {
		event(player, vehicle, oSeat, nSeat)
	}
}

//export altPlayerDamageEvent
func altPlayerDamageEvent(p unsafe.Pointer, e C.struct_entity, healthDmg C.ushort, armourDmg C.ushort, weap C.ulong) {
	player := NewPlayer(p)
	healthDamage := uint16(healthDmg)
	armourDamage := uint16(armourDmg)
	weapon := uint32(weap)

	var entity interface{}
	entityType := BaseObjectType(e.Type)

	if entityType == PlayerObject {
		entity = NewPlayer(e.Ptr)
	} else if entityType == VehicleObject {
		entity = NewVehicle(e.Ptr)
	}

	for _, event := range On.playerDamageEvents {
		event(player, entity, healthDamage, armourDamage, weapon)
	}
}

//export altPlayerDeathEvent
func altPlayerDeathEvent(p unsafe.Pointer, e C.struct_entity, weap C.ulong) {
	player := NewPlayer(p)
	weapon := uint32(weap)

	var entity interface{}
	entityType := BaseObjectType(e.Type)

	if entityType == PlayerObject {
		entity = NewPlayer(e.Ptr)
	} else if entityType == VehicleObject {
		entity = NewVehicle(e.Ptr)
	}

	for _, event := range On.playerDeathEvents {
		event(player, entity, weapon)
	}
}

//export altPlayerEnterVehicleEvent
func altPlayerEnterVehicleEvent(p unsafe.Pointer, v unsafe.Pointer, s C.uchar) {
	player := NewPlayer(p)
	vehicle := NewVehicle(v)
	seat := uint8(s)

	for _, event := range On.playerEnterVehicleEvents {
		event(player, vehicle, seat)
	}
}

//export altPlayerLeaveVehicleEvent
func altPlayerLeaveVehicleEvent(p unsafe.Pointer, v unsafe.Pointer, s C.uchar) {
	player := NewPlayer(p)
	vehicle := NewVehicle(v)
	seat := uint8(s)

	for _, event := range On.playerLeaveVehicleEvents {
		event(player, vehicle, seat)
	}
}

//export altRemoveEntityEvent
func altRemoveEntityEvent(e C.struct_entity) {
	var entity interface{}
	entityType := BaseObjectType(e.Type)

	if entityType == PlayerObject {
		entity = NewPlayer(e.Ptr)
	} else if entityType == VehicleObject {
		entity = NewVehicle(e.Ptr)
	}

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
func altWeaponDamageEvent(p unsafe.Pointer, e C.struct_entity, weap C.ulong, dmg C.ushort, ofs C.struct_pos, bPart C.short) {
	player := NewPlayer(p)
	weapon := uint32(weap)
	damage := uint16(dmg)
	offset := Vector3{X: float32(ofs.x), Y: float32(ofs.y), Z: float32(ofs.z)}
	bodyPart := int8(bPart)

	var entity interface{}
	entityType := BaseObjectType(e.Type)

	if entityType == PlayerObject {
		entity = NewPlayer(e.Ptr)
	} else if entityType == VehicleObject {
		entity = NewVehicle(e.Ptr)
	}

	for _, event := range On.weaponDamageEvents {
		event(player, entity, weapon, damage, offset, bodyPart)
	}
}

//export altPlayerEnteringVehicleEvent
func altPlayerEnteringVehicleEvent(p unsafe.Pointer, v unsafe.Pointer, s C.ushort) {
	player := NewPlayer(p)
	vehicle := NewVehicle(v)
	seat := uint8(s)

	for _, event := range On.playerEnteringVehicleEvents {
		event(player, vehicle, seat)
	}
}

//export altColShapeEvent
func altColShapeEvent(c unsafe.Pointer, e C.struct_entity, s C.int) {
	colShape := NewColShape(c)
	state := int(s) == 1

	var entity interface{}
	entityType := BaseObjectType(e.Type)

	if entityType == PlayerObject {
		entity = NewPlayer(e.Ptr)
	} else if entityType == VehicleObject {
		entity = NewVehicle(e.Ptr)
	}

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
func altFireEvent(p unsafe.Pointer, f C.struct_array) {
	player := NewPlayer(p)

	size := int(f.size)
	cFireInfoStructs := (*[1 << 28]C.struct_fireInfo)(f.array)[:size:size]

	array := make([]FireInfo, size)

	for i, fireStruct := range cFireInfoStructs {
		array[i] = FireInfo{WeaponHash: uint32(fireStruct.weaponHash), Position: Vector3{X: float32(fireStruct.position.x), Y: float32(fireStruct.position.y), Z: float32(fireStruct.position.z)}}
	}

	for _, event := range On.fireEvents {
		event(player, array)
	}
}

//export altGlobalMetaDataChangeEvent
func altGlobalMetaDataChangeEvent(k *C.char, nVal C.struct_metaData, oVal C.struct_metaData) {
	key := C.GoString(k)
	newVal := &MValue{Ptr: nVal.Ptr, Type: uint8(nVal.Type), Value: nil}
	oldVal := &MValue{Ptr: oVal.Ptr, Type: uint8(oVal.Type), Value: nil}
	oldValue := oldVal.GetValue()
	newValue := newVal.GetValue()

	for _, event := range On.globalMetaDataChangeEvents {
		event(key, newValue, oldValue)
	}
}

//export altGlobalSyncedMetaDataChangeEvent
func altGlobalSyncedMetaDataChangeEvent(k *C.char, nVal C.struct_metaData, oVal C.struct_metaData) {
	key := C.GoString(k)
	newVal := &MValue{Ptr: nVal.Ptr, Type: uint8(nVal.Type), Value: nil}
	oldVal := &MValue{Ptr: oVal.Ptr, Type: uint8(oVal.Type), Value: nil}
	oldValue := oldVal.GetValue()
	newValue := newVal.GetValue()

	for _, event := range On.globalSyncedMetaDataChangeEvents {
		event(key, newValue, oldValue)
	}
}

//export altNetOwnerChangeEvent
func altNetOwnerChangeEvent(e C.struct_entity, o unsafe.Pointer, oo unsafe.Pointer) {
	owner := NewPlayer(o)
	oldOwner := NewPlayer(oo)

	var entity interface{}
	entityType := BaseObjectType(e.Type)

	if entityType == PlayerObject {
		entity = NewPlayer(e.Ptr)
	} else if entityType == VehicleObject {
		entity = NewVehicle(e.Ptr)
	}

	for _, event := range On.netOwnerChangeEvents {
		event(entity, owner, oldOwner)
	}
}

//export altPlayerWeaponChangeEvent
func altPlayerWeaponChangeEvent(p unsafe.Pointer, oWeap C.ulong, nWeap C.ulong) {
	player := NewPlayer(p)
	oldWeapon := uint32(oWeap)
	newWeapon := uint32(nWeap)

	for _, event := range On.playerWeaponChangeEvents {
		event(player, oldWeapon, newWeapon)
	}
}

//export altStartProjectileEvent
func altStartProjectileEvent(p unsafe.Pointer, pos C.struct_pos, dir C.struct_pos, aHash C.uint, wHash C.ulong) {
	player := NewPlayer(p)
	position := Vector3{X: float32(pos.x), Y: float32(pos.y), Z: float32(pos.z)}
	direction := Vector3{X: float32(dir.x), Y: float32(dir.y), Z: float32(dir.z)}
	ammoHash := uint16(aHash)
	weaponHash := uint32(wHash)

	for _, event := range On.startProjectileEvents {
		event(player, position, direction, ammoHash, weaponHash)
	}
}

//export altStreamSyncedMetaDataChangeEvent
func altStreamSyncedMetaDataChangeEvent(e C.struct_entity, k *C.char, nVal C.struct_metaData, oVal C.struct_metaData) {
	key := C.GoString(k)
	newVal := &MValue{Ptr: nVal.Ptr, Type: uint8(nVal.Type), Value: nil}
	oldVal := &MValue{Ptr: oVal.Ptr, Type: uint8(oVal.Type), Value: nil}
	oldValue := oldVal.GetValue()
	newValue := newVal.GetValue()

	var entity interface{}
	entityType := BaseObjectType(e.Type)

	if entityType == PlayerObject {
		entity = NewPlayer(e.Ptr)
	} else if entityType == VehicleObject {
		entity = NewVehicle(e.Ptr)
	}

	for _, event := range On.streamSyncedMetaDataChangeEvents {
		event(entity, key, newValue, oldValue)
	}
}

//export altSyncedMetaDataChangeEvent
func altSyncedMetaDataChangeEvent(e C.struct_entity, k *C.char, nVal C.struct_metaData, oVal C.struct_metaData) {
	key := C.GoString(k)
	newVal := &MValue{Ptr: nVal.Ptr, Type: uint8(nVal.Type), Value: nil}
	oldVal := &MValue{Ptr: oVal.Ptr, Type: uint8(oVal.Type), Value: nil}
	oldValue := oldVal.GetValue()
	newValue := newVal.GetValue()

	var entity interface{}
	entityType := BaseObjectType(e.Type)

	if entityType == PlayerObject {
		entity = NewPlayer(e.Ptr)
	} else if entityType == VehicleObject {
		entity = NewVehicle(e.Ptr)
	}

	for _, event := range On.streamSyncedMetaDataChangeEvents {
		event(entity, key, newValue, oldValue)
	}
}

//export altVehicleAttachEvent
func altVehicleAttachEvent(v unsafe.Pointer, a unsafe.Pointer) {
	vehicle := NewVehicle(v)
	attached := NewVehicle(a)

	for _, event := range On.vehicleAttachEvents {
		event(vehicle, attached)
	}
}

//export altVehicleDetachEvent
func altVehicleDetachEvent(v unsafe.Pointer, a unsafe.Pointer) {
	vehicle := NewVehicle(v)
	attached := NewVehicle(a)

	for _, event := range On.vehicleDetachEvents {
		event(vehicle, attached)
	}
}

//export altVehicleDestroyEvent
func altVehicleDestroyEvent(v unsafe.Pointer) {
	vehicle := NewVehicle(v)

	for _, event := range On.vehicleDestroyEvents {
		event(vehicle)
	}
}
