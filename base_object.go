package altv

// #include "capi.h"
import "C"
import (
	"context"
	"errors"
	"fmt"
	"unsafe"

	"github.com/goccy/go-json"
	"github.com/timo972/altv-go/mvalue"
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
	json.Marshaler
	json.Unmarshaler
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

type jsonBaseObject struct {
	ID   uint32         `json:"id"`
	Type BaseObjectType `json:"type"`
	Ptr  string         `json:"ptr"`
}

func (b *baseObject) MarshalJSON() ([]byte, error) {
	return json.Marshal(jsonBaseObject{ID: b.id, Type: b.typ})
}

func (b *baseObject) UnmarshalJSON(data []byte) error {
	var obj jsonBaseObject
	if err := json.Unmarshal(data, &obj); err != nil {
		return err
	}

	ptr, err := mvalue.ParsePointer(obj.Ptr)
	if err != nil {
		return err
	}

	b.id = obj.ID
	b.typ = obj.Type
	b.ptr = ptr

	return nil
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

func newBaseObject(typ BaseObjectType, ptr unsafe.Pointer, id uint32) baseObject {
	ctx, cancel := context.WithCancelCause(context.Background())
	return baseObject{
		ptr:        ptr,
		id:         id,
		typ:        typ,
		ctx:        ctx,
		cancelFunc: cancel,
	}
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
