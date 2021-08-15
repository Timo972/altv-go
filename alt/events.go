package alt

// #include "Module.h"
import "C"
import (
	"unsafe"
)

type eventType = uint16
type playerConnectListener = func(p *Player)
type playerDisconnectListener = func(p *Player, reason string)
type consoleCommandListener = func(command string, args []string)
type explosionListener = func(p *Player, t *Entity, pos Position, explosionType int16, explosionFX uint)
type playerChangeVehicleSeatListener = func(p *Player, v *Vehicle, oldSeat uint8, newSeat uint8)
type playerDamageListener = func(p *Player, attacker *Entity, damage uint16, weapon uint32)
type playerDeathListener = func(p *Player, killer *Entity, weapon uint32)
type playerEnterVehicleListener = func(p *Player, v *Vehicle, seat uint8)
type playerLeaveVehicleListener = func(p *Player, v *Vehicle, seat uint8)
type removeEntityListener = func(entity *Entity)
type resourceStartListener = func(resourceName string)
// TODO bodyPart ENUM
type weaponDamageListener = func(source *Player, target *Entity, weapon uint32, damage uint8, offset Position, bodyPart int8)

type eventManager struct {
	playerConnectEvents  []playerConnectListener
	consoleCommandEvents []consoleCommandListener
	playerDisconnectEvents []playerDisconnectListener
	explosionEvents []explosionListener
	playerChangeVehicleSeatEvents []playerChangeVehicleSeatListener
	playerDamageEvents []playerDamageListener
	playerDeathEvents []playerDeathListener
	playerEnterVehicleEvents []playerEnterVehicleListener
	playerLeaveVehicleEvents []playerLeaveVehicleListener
	removeEntityEvents []removeEntityListener
	resourceStartEvents []resourceStartListener
	weaponDamageEvents []weaponDamageListener
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
func altPlayerDisconnectEvent(player unsafe.Pointer, reason *C.char) {
	for _, event := range On.playerDisconnectEvents {
		reason := C.GoString(reason)
		player := NewPlayer(player)
		event(player, reason)
	}
}

//export altExplosionEvent
func altExplosionEvent(player unsafe.Pointer, entity unsafe.Pointer, pos C.struct_pos, explosionType C.short, explosionFX C.uint) {
	for _, event := range On.explosionEvents {
		player := NewPlayer(player)
		entity := NewEntity(entity)
		event(player, entity, Position{X: float32(pos.x), Y: float32(pos.y), Z: float32(pos.z)}, int16(explosionType), uint(explosionFX))
	}
}