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
	Ptr  unsafe.Pointer
	Type BaseObjectType
}

type MetaData struct {
	Ptr unsafe.Pointer
}

type Base interface {
	HasMetaData(key string) bool
	GetMetaData(key string) interface{}
	SetMetaData(key string, value interface{})
	DeleteMetaData(key string)
}

func (b BaseObject) HasMetaData(key string) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if b.Type == PlayerObject {
		return int(C.player_has_meta_data(b.Ptr, cKey)) != 1
	}

	return false
}

func (b BaseObject) GetMetaData(key string) interface{} {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	var data *MetaData

	if b.Type == PlayerObject {
		data = &MetaData{Ptr: C.player_get_meta_data(b.Ptr, cKey).Ptr}
	}

	mValue := &MValue{Ptr: data.Ptr, Type: b.Type, Value: nil}

	return mValue.GetValue()
}

func (b BaseObject) SetMetaData(key string, value interface{}) {
	mValue := CreateMValue(value)
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if b.Type == PlayerObject {
		C.player_set_meta_data(b.Ptr, cKey, mValue.Ptr)
	}
}

func (b BaseObject) DeleteMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if b.Type == PlayerObject {
		C.player_delete_meta_data(b.Ptr, cKey)
	}
}
