package alt

import "C"
import "unsafe"

type IPool[T IBaseObject, TFactory any] interface {
	Add(entity T)
	Remove(ptr unsafe.Pointer)
	Has(ptr unsafe.Pointer) bool
	Get(ptr unsafe.Pointer) T
}

type pool[T IBaseObject, TFactory any] struct {
	entities map[unsafe.Pointer]T
	factory  TFactory
}

var (
	playerCache       = &playerPool{}
	vehicleCache      = &vehiclePool{}
	colShapeCache     = &colShapePool{}
	checkpointCache   = &checkpointPool{}
	voiceChannelCache = &voiceChannelPool{}
	blipCache         = &blipPool{}
)

func (p *pool[T, TF]) Add(e T) {
	p.entities[e.NativePointer()] = e
}

func (p *pool[T, TF]) Remove(ptr unsafe.Pointer) {
	delete(p.entities, ptr)
}

func (p *pool[T, TF]) Has(ptr unsafe.Pointer) bool {
	_, ok := p.entities[ptr]
	return ok
}

func (p *pool[T, TF]) Get(ptr unsafe.Pointer) (T, bool) {
	t, ok := p.entities[ptr]
	return t, ok
}

type playerPool struct {
	pool[IPlayer, playerFactory]
}

type vehiclePool struct {
	pool[IVehicle, vehicleFactory]
}

type colShapePool struct {
	pool[IColShape, colShapeFactory]
}

type checkpointPool struct {
	pool[ICheckpoint, checkpointFactory]
}

type voiceChannelPool struct {
	pool[IVoiceChannel, voiceChannelFactory]
}

type blipPool struct {
	pool[IBlip, blipFactory]
}

func (p *playerPool) GetOrCreate(ptr unsafe.Pointer, id uint16) IPlayer {
	if pl, ok := p.Get(ptr); ok {
		return pl
	}

	e := Factories.player(ptr, id)
	p.Add(e)

	return e
}

func (v *vehiclePool) GetOrCreate(ptr unsafe.Pointer, id uint16, model uint32) IVehicle {
	if ve, ok := v.Get(ptr); ok {
		return ve
	}

	e := Factories.vehicle(ptr, id, model)
	v.Add(e)

	return e
}

func (c *colShapePool) GetOrCreate(ptr unsafe.Pointer) IColShape {
	if cs, ok := c.Get(ptr); ok {
		return cs
	}

	e := Factories.colShape(ptr)
	c.Add(e)

	return e
}

func (c *checkpointPool) GetOrCreate(ptr unsafe.Pointer) ICheckpoint {
	if cp, ok := c.Get(ptr); ok {
		return cp
	}

	e := Factories.checkpoint(ptr)
	c.Add(e)

	return e
}

func (v *voiceChannelPool) GetOrCreate(ptr unsafe.Pointer) IVoiceChannel {
	if vc, ok := v.Get(ptr); ok {
		return vc
	}

	e := Factories.voiceChannel(ptr)
	v.Add(e)

	return e
}

func (b *blipPool) GetOrCreate(ptr unsafe.Pointer) IBlip {
	if bl, ok := b.Get(ptr); ok {
		return bl
	}

	e := Factories.blip(ptr)
	b.Add(e)

	return e
}

func getPlayer(e C.struct_entity) IPlayer {
	typ := BaseObjectType(e.typ)
	if typ != PlayerObject {
		return nil
	}

	ptr := unsafe.Pointer(e.ptr)
	id := uint16(e.id)

	return playerCache.GetOrCreate(ptr, id)
}

func getVehicle(e C.struct_entity) IVehicle {
	typ := BaseObjectType(e.typ)
	ptr := unsafe.Pointer(e.ptr)
	id := uint16(e.id)
	model := uint32(e.model)

	if typ != VehicleObject {
		return nil
	}

	return vehicleCache.GetOrCreate(ptr, id, model)
}

func getColShape(e C.struct_entity) IColShape {
	typ := BaseObjectType(e.typ)
	ptr := unsafe.Pointer(e.ptr)

	if typ != ColshapeObject {
		return nil
	}

	return colShapeCache.GetOrCreate(ptr)
}

func getCheckpoint(e C.struct_entity) ICheckpoint {
	typ := BaseObjectType(e.typ)
	ptr := unsafe.Pointer(e.ptr)

	if typ != CheckpointObject {
		return nil
	}

	return checkpointCache.GetOrCreate(ptr)
}

func getVoiceChannel(e C.struct_entity) IVoiceChannel {
	typ := BaseObjectType(e.typ)
	ptr := unsafe.Pointer(e.ptr)

	if typ != VoiceChannelObject {
		return nil
	}

	return voiceChannelCache.GetOrCreate(ptr)
}

func getBlip(e C.struct_entity) IBlip {
	typ := BaseObjectType(e.typ)
	ptr := unsafe.Pointer(e.ptr)

	if typ != BlipObject {
		return nil
	}

	return blipCache.GetOrCreate(ptr)
}

func getEntity(e C.struct_entity) IEntity {
	typ := BaseObjectType(e.typ)
	ptr := unsafe.Pointer(e.ptr)
	id := uint16(e.id)

	switch typ {
	case PlayerObject:
		return playerCache.GetOrCreate(ptr, id)
	case VehicleObject:
		return vehicleCache.GetOrCreate(ptr, id, uint32(e.model))
	}

	return nil
}
