package altv

// #include "capi.h"
import "C"
import (
	"context"
	"errors"
	"fmt"
	"log"
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
	// json.Unmarshaler
	ID() uint32
	Type() BaseObjectType
	Ptr() unsafe.Pointer
	Valid() bool
	Destroy()
	Context() context.Context
	SetMetaData(key string, value interface{}) error
	MetaData(key string, value interface{}) error
	cancel(error)
}

type baseObject struct {
	id         uint32
	ptr        unsafe.Pointer
	typ        BaseObjectType
	ctx        context.Context
	cancelFunc context.CancelCauseFunc
}

type BaseObjectData[T BaseObject] struct {
	json.Marshaler
	json.Unmarshaler
	ID    uint32
	Type  BaseObjectType
	ptr   unsafe.Pointer
	Model uint32
}

type baseObjectData struct {
	mvalue.SpecialType
	ID    uint32         `json:"id"`
	Type  BaseObjectType `json:"type"`
	Ptr   string         `json:"ptr"`
	Model uint32         `json:"model,omitempty"`
}

func (b *BaseObjectData[T]) MarshalJSON() ([]byte, error) {
	return json.Marshal(baseObjectData{ID: b.ID, Type: b.Type, Ptr: "", Model: b.Model, SpecialType: mvalue.SpecialType{Type: mvalue.TypeBaseObject}})
}

func (b *BaseObjectData[T]) UnmarshalJSON(data []byte) error {
	var obj baseObjectData
	var err error
	if err = json.Unmarshal(data, &obj); err != nil {
		return err
	}

	if b.ptr, err = mvalue.ParsePointer(obj.Ptr); err != nil {
		return err
	}
	b.ID = obj.ID
	b.Type = obj.Type
	b.Model = obj.Model
	return nil
}

func (b *BaseObjectData[T]) Obj() (T, error) {
	return GetBaseObject[T](b.Type, b.ptr, b.ID, b.Model)
}

func (b *baseObject) MarshalJSON() ([]byte, error) {
	return json.Marshal(baseObjectData{ID: b.id, Type: b.typ})
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
	if b.ctx == nil {
		return false
	}

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

func (b *baseObject) SetMetaData(key string, v interface{}) error {
	raw, err := mvalue.Marshal(v)
	if err != nil {
		return err
	}

	log.Printf("SetMetaData: %s -> %s\n", key, string(raw))

	data := C.struct_array{
		array: unsafe.Pointer(C.CBytes(raw)),
		size:  C.ulonglong(len(raw)),
	}

	if b.typ == BaseTypePlayer {
		C.player_set_meta_data(b.ptr, C.CString(key), data)
	} else if b.typ == BaseTypeVehicle {
		C.vehicle_set_meta_data(b.ptr, C.CString(key), data)
	}

	return nil
}

func (b *baseObject) MetaData(key string, v interface{}) error {
	return nil
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
