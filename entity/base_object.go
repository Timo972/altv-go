package entity

// #cgo CFLAGS: -I../internal/capi/lib
// #cgo linux LDFLAGS: -L../internal/capi/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L../internal/capi/lib/win32 -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
// #include <stdlib.h>
// #include "capi.h"
import "C"
import (
	"context"
	"errors"
	"unsafe"

	"github.com/goccy/go-json"
)

var ErrInvalidBaseObject = errors.New("base object is invalid")

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
	CancelCtx(error)
}

type AltBaseObject struct {
	id         uint32
	ptr        unsafe.Pointer
	typ        BaseObjectType
	ctx        context.Context
	cancelFunc context.CancelCauseFunc
}

/*type BaseObjectData[T BaseObject] struct {
	json.Marshaler
	json.Unmarshaler
	ID    uint32
	Type  BaseObjectType
	Ptr   unsafe.Pointer
	Model uint32
}

type altBaseObjectData struct {
	mvalue.SpecialType
	ID    uint32         `json:"id"`
	Type  BaseObjectType `json:"type"`
	Ptr   string         `json:"ptr"`
	Model uint32         `json:"model,omitempty"`
}

func (b *BaseObjectData[T]) MarshalJSON() ([]byte, error) {
	return json.Marshal(AltBaseObjectData{ID: b.ID, Type: b.Type, Ptr: "", Model: b.Model, SpecialType: mvalue.SpecialType{Type: mvalue.TypeBaseObject}})
}

func (b *BaseObjectData[T]) UnmarshalJSON(data []byte) error {
	var obj AltBaseObjectData
	var err error
	if err = json.Unmarshal(data, &obj); err != nil {
		return err
	}

	if b.Ptr, err = mvalue.ParsePointer(obj.Ptr); err != nil {
		return err
	}
	b.ID = obj.ID
	b.Type = obj.Type
	b.Model = obj.Model
	return nil
}

func (b *BaseObjectData[T]) Obj() (T, error) {
	return nil, nil // factory.GetBaseObject[T](b.Type, b.Ptr, b.ID, b.Model)
}*/

func (b *AltBaseObject) MarshalJSON() ([]byte, error) {
	return []byte("{}"), nil // json.Marshal(AltBaseObjectData{ID: b.id, Type: b.typ})
}

func (b *AltBaseObject) ID() uint32 {
	return b.id
}

func (b *AltBaseObject) Type() BaseObjectType {
	return b.typ
}

func (b *AltBaseObject) Ptr() unsafe.Pointer {
	return b.ptr
}

func (b *AltBaseObject) Valid() bool {
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

func (b *AltBaseObject) Destroy() {
	if b.typ == TypePlayer {
		C.player_destroy(b.ptr)
	} else if b.typ == TypeVoiceChannel {
		C.voice_channel_destroy(b.ptr)
	} else if b.typ == TypeCheckpoint {
		C.checkpoint_destroy(b.ptr)
	} else if b.typ == TypeColShape {
		C.col_shape_destroy(b.ptr)
	} else if b.typ == TypeVehicle {
		C.vehicle_destroy(b.ptr)
	} else if b.typ == TypeBlip {
		C.blip_destroy(b.ptr)
	}
}

func (b *AltBaseObject) Context() context.Context {
	return b.ctx
}

func (b *AltBaseObject) CancelCtx(err error) {
	b.cancelFunc(err)
}

func (b *AltBaseObject) SetMetaData(key string, v any) error {
	/*data, free, err := marshal(v)
	if err != nil {
		return err
	}
	defer free()

	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))
	if b.typ == BaseTypePlayer {
		C.player_set_meta_data(b.ptr, cKey, data)
	} else if b.typ == BaseTypeVehicle {
		C.vehicle_set_meta_data(b.ptr, cKey, data)
	}*/

	return nil
}

func (b *AltBaseObject) MetaData(key string, v any) error {
	/*var carr C.struct_array
	ckey := C.CString(key)
	defer C.free(unsafe.Pointer(ckey))
	if b.typ == BaseTypePlayer {
		carr = C.player_get_meta_data(b.ptr, ckey)
	} else if b.typ == BaseTypeVehicle {
		carr = C.vehicle_get_meta_data(b.ptr, ckey)
	}*/

	return nil // unmarshal(carr, v)
}

func newBaseObject(typ BaseObjectType, ptr unsafe.Pointer, id uint32) AltBaseObject {
	ctx, cancel := context.WithCancelCause(context.Background())
	return AltBaseObject{
		ptr:        ptr,
		id:         id,
		typ:        typ,
		ctx:        ctx,
		cancelFunc: cancel,
	}
}
