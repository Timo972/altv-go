package test

import (
	"context"
	"encoding/json"
	"errors"
	"unsafe"

	"github.com/timo972/altv-go"
	"github.com/timo972/altv-go/mvalue"
)

// copied from altv-go/base_object.go
type baseObjectData struct {
	mvalue.SpecialType
	ID    uint32              `json:"id"`
	Type  altv.BaseObjectType `json:"type"`
	Ptr   string              `json:"ptr"`
	Model uint32              `json:"model,omitempty"`
}

type BaseObject struct {
	ctx        context.Context
	cancelFunc context.CancelCauseFunc
	ptr        unsafe.Pointer
	id         uint32
	typ        altv.BaseObjectType
	meta       map[string][]byte
}

func (b *BaseObject) Type() altv.BaseObjectType {
	return b.typ
}

func (b *BaseObject) SetType(typ altv.BaseObjectType) *BaseObject {
	b.typ = typ
	return b
}

func (b *BaseObject) ID() uint32 {
	return b.id
}

func (b *BaseObject) SetID(id uint32) *BaseObject {
	b.id = id
	return b
}

func (b *BaseObject) Valid() bool {
	return b.ctx.Err() == nil
}

func (b *BaseObject) Ptr() unsafe.Pointer {
	return b.ptr
}

func (b *BaseObject) SetPtr(ptr unsafe.Pointer) *BaseObject {
	b.ptr = ptr
	return b
}

func (b *BaseObject) Destroy() {
	b.cancelFunc(errors.New("object destroyed"))
}

func (b *BaseObject) Context() context.Context {
	return b.ctx
}

func (b *BaseObject) SetMetaData(key string, value interface{}) error {
	data, err := mvalue.Marshal(value)
	if err != nil {
		return err
	}
	b.meta[key] = data
	return nil
}

func (b *BaseObject) MetaData(key string, value interface{}) error {
	raw, ok := b.meta[key]
	if !ok {
		return errors.New("meta data not found")
	}
	return mvalue.Unmarshal(raw, value)
}

func (b *BaseObject) MarshalJSON() ([]byte, error) {
	return json.Marshal(baseObjectData{ID: b.id, Type: b.typ})
}

func (b *BaseObject) CancelCtx(err error) {
	b.cancelFunc(err)
}

func NewBaseObject(id uint32, typ altv.BaseObjectType) *BaseObject {
	ctx, cancel := context.WithCancelCause(context.Background())
	return &BaseObject{
		ctx:        ctx,
		cancelFunc: cancel,
	}
}
