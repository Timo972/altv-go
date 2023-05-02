package altv

// #include "capi.h"
import "C"
import (
	"context"
	"errors"
	"fmt"
	"unsafe"
)

var ErrInvalidBaseObject = errors.New("base object is invalid")

type BaseObjectType = uint8

const (
	BaseTypePlayer BaseObjectType = iota
	BaseTypeVehicle
	BaseTypePed
	BaseTypeNetworkObject
	BaseTypeBlip
	BaseTypeWebView
	BaseTypeVoiceChannel
	BaseTypeColShape
	BaseTypeCheckpoint
	BaseTypeWebSocketClient
	BaseTypeHttpClient
	BaseTypeAudio
	BaseTypeRMLElement
	BaseTypeRMLDocument
	BaseTypeLocalPlayer
	BaseTypeObject
	BaseTypeVirtualEntity
	BaseTypeVirtualEntityGroup
	BaseTypeMarker
	BaseTypeTextLabel
	BaseTypeLocalPed
	BaseTypeLocalVehicle
	BaseTypeAudioFilter
	BaseTypeSize
)

type BaseObject interface {
	ID() uint32
	Type() BaseObjectType
	Ptr() unsafe.Pointer
	Valid() bool
	Destroy()
	Context() context.Context
	cancel(error)
}

type baseObject struct {
	id         uint32
	ptr        unsafe.Pointer
	typ        BaseObjectType
	ctx        context.Context
	cancelFunc context.CancelCauseFunc
}

func (b *baseObject) ID() uint32 {
	return b.id
}

func (b *baseObject) Type() BaseObjectType {
	return b.typ
}

func (b *baseObject) Ptr() unsafe.Pointer {
	return b.ptr
}

func (b *baseObject) Valid() bool {
	// TODO: check if base object still exists
	// probably check where pointer is pointing to
	if err := b.ctx.Err(); err != nil {
		return false
	}
	return true
}

func (b *baseObject) Destroy() {
	if b.typ == BaseTypePlayer {
		C.player_destroy(b.ptr)
	} else if b.typ == BaseTypeVoiceChannel {
		C.voice_channel_destroy(b.ptr)
	} else if b.typ == BaseTypeCheckpoint {
		C.checkpoint_destroy(b.ptr)
	} else if b.typ == BaseTypeColShape {
		C.col_shape_destroy(b.ptr)
	} else if b.typ == BaseTypeVehicle {
		C.vehicle_destroy(b.ptr)
	} else if b.typ == BaseTypeBlip {
		C.blip_destroy(b.ptr)
	}
}

func (b *baseObject) Context() context.Context {
	return b.ctx
}

func (b *baseObject) cancel(err error) {
	b.cancelFunc(err)
}

//export altCreateBaseObject
func altCreateBaseObject(entity C.struct_entity) {
	fmt.Printf("altCreateBaseObject\n")
	id := uint32(entity.id)
	typ := BaseObjectType(entity.typ)
	ptr := unsafe.Pointer(entity.ptr)
	model := uint32(entity.model)

	if _, err := GetBaseObject[BaseObject](typ, ptr, id, model); err != nil {
		LogError(fmt.Sprintf("altCreateBaseObject: %s", err.Error()))
	}
}

//export altRemoveBaseObject
func altRemoveBaseObject(entity C.struct_entity) {
	fmt.Printf("altRemoveBaseObject\n")
	id := uint32(entity.id)
	typ := BaseObjectType(entity.typ)
	ptr := unsafe.Pointer(entity.ptr)
	model := uint32(entity.model)

	obj, err := GetBaseObject[BaseObject](typ, ptr, id, model)
	if err != nil {
		LogError(fmt.Sprintf("altRemoveBaseObject: %s", err.Error()))
		return
	}

	obj.cancel(ErrInvalidBaseObject)
	baseObjectCache.Delete(id)
}
