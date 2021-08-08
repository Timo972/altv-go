package alt

// #include "Module.h"
import "C"
import "unsafe"

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
	panic("implement me")
}

func (b BaseObject) HasMetaData(key string) bool {
	cstr := C.CString(key)
	defer C.free(unsafe.Pointer(cstr))

	return int(C.base_object_has_meta_data(b.Ptr, cstr)) == 1
}

func (b BaseObject) GetMetaData(key string) interface{} {
	cstr := C.CString(key)
	defer C.free(unsafe.Pointer(cstr))

	data := C.base_object_get_meta_data(b.Ptr, cstr)

	// Get actual data from capi
	// Return value
	return nil
}

func (b BaseObject) SetMetaData(key string, value interface{}) {
	// Put logic inside another func, call capi func based on type
	// Call capi func and convert value to actual mvalue

	switch valueType := value.(type) {
	case int, int16, int32, int64, int8:
		valueType = 0
		break
	}
}

func (b BaseObject) DeleteMetaData(key string) {
	cstr := C.CString(key)
	defer C.free(unsafe.Pointer(cstr))

	C.base_object_delete_meta_data(b.Ptr, cstr)
}
