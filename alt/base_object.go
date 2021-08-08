package alt

// #include "Module.h"
import "C"
import (
	"unsafe"
)

type BaseObjectType = uint8

const (
	PlayerObject BaseObjectType = iota
	VehicleObject
	BlipObject
	WebviewObject
	VoiceChannelObject
	ColshapeObject
	CheckpointObject
	WebSocketClientObject
	HttpClientObject
	AudioObject
	LocalPlayerObject
)

type BaseObject struct {
	Ptr unsafe.Pointer
}

type Base interface {
	GetType() BaseObjectType
	HasMetaData(key string) bool
	GetMetaData(key string) interface{}
	SetMetaData(key string, value interface{})
	DeleteMetaData(key string)
}

func (b BaseObject) GetType() BaseObjectType {
	return BaseObjectType(C.base_object_get_type(b.Ptr))
}

func (b BaseObject) HasMetaData(key string) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	return int(C.base_object_has_meta_data(b.Ptr, cKey)) == 1
}

func (b BaseObject) GetMetaData(key string) interface{} {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))
	data := C.base_object_get_meta_data(b.Ptr, cKey)
	mValue := &MValue{Ptr: data.Ptr, Type: uint8(data.Type), Value: nil}

	return mValue.GetValue()
}

func (b BaseObject) SetMetaData(key string, value interface{}) {
	mValue := CreateMValue(value)
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	C.base_object_set_meta_data(b.Ptr, cKey, mValue.Ptr)
}

func (b BaseObject) DeleteMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	C.base_object_delete_meta_data(b.Ptr, cKey)
}
