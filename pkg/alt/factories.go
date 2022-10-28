package alt

import "unsafe"

type IPlayer interface {
	IEntity
	Name() string
	SetModel(model uint32)
	Spawn(pos Vector3, delay uint32)
}

type IVehicle interface {
	IEntity
}

type IColShape interface {
	World
}

type IVoiceChannel interface {
	IBaseObject
}

type ICheckpoint interface {
	World
}

type IBlip interface {
	World
}

type playerFactory = func(p unsafe.Pointer, id uint16) IPlayer
type vehicleFactory = func(p unsafe.Pointer, id uint16, model uint32) IVehicle
type colShapeFactory = func(p unsafe.Pointer) IColShape
type checkpointFactory = func(p unsafe.Pointer) ICheckpoint
type voiceChannelFactory = func(p unsafe.Pointer) IVoiceChannel
type blipFactory = func(p unsafe.Pointer) IBlip

type factories struct {
	player       playerFactory
	vehicle      vehicleFactory
	colShape     colShapeFactory
	checkpoint   checkpointFactory
	voiceChannel voiceChannelFactory
	blip         blipFactory
}

var Factories = &factories{}

func (f *factories) Player(factory playerFactory) {
	f.player = factory
}

func (f *factories) Vehicle(factory vehicleFactory) {
	f.vehicle = factory
}

type MyPlayer struct {
	Player
	loggedIn bool
}

func NewPlayer(ptr unsafe.Pointer, id uint16) Player {
	p := Player{}
	p.ptr = ptr
	p.id = id

	return p
}

func myPlayerFactory(ptr unsafe.Pointer, id uint16) IPlayer {
	p := MyPlayer{
		Player: NewPlayer(ptr, id),
	}
	p.loggedIn = false
	return p
}

func test() {
	Factories.Player(myPlayerFactory)

	On.PlayerConnect(func(p IPlayer) {

	})
}
