package alt

/*
#cgo windows CFLAGS: -I../../c-api/lib
#cgo windows LDFLAGS: -L../../c-api/lib/win32 -lcapi

#cgo linux CFLAGS: -I../../c-api/lib
#cgo linux LDFLAGS: -g -L../../c-api/lib/linux -lcapi  -ldl

#ifndef GOLANG_APP
#define GOLANG_APP

#include <stdlib.h>
#include "capi.h"

#endif
*/
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
	ptr  unsafe.Pointer
	typ  BaseObjectType
	data map[string]interface{}
}

type IBaseObject interface {
	Type() BaseObjectType
	NativePointer() unsafe.Pointer
	Valid() bool
	Destroy()
	HasMetaData(key string) bool
	SetMetaData(key string, value interface{}) bool
	MetaData(key string, out interface{}) bool
	DeleteMetaData(key string)
}

func (b BaseObject) Type() BaseObjectType {
	return b.typ
}

func (b BaseObject) NativePointer() unsafe.Pointer {
	return b.ptr
}

/*typ Base interface {
	HasMetaData(key string) bool
	MetaData(key string, value interface{}) bool
	SetMetaData(key string, value interface{})
	DeleteMetaData(key string)
}*/

func (b BaseObject) Valid() bool {
	// TODO check if it works with player
	if b.ptr == nil {
		return false
	}

	cName := C.CString(CurrentResource.Name())
	defer C.free(unsafe.Pointer(cName))

	// if so add for other base object extenders
	if b.typ == PlayerObject {
		return int(C.player_is_valid(cName, b.ptr)) == 1
	} else if b.typ == VoiceChannelObject {
		return int(C.voice_channel_is_valid(cName, b.ptr)) == 1
	} else if b.typ == CheckpointObject {
		return int(C.checkpoint_is_valid(cName, b.ptr)) == 1
	} else if b.typ == ColshapeObject {
		return int(C.col_shape_is_valid(cName, b.ptr)) == 1
	} else if b.typ == VehicleObject {
		return int(C.vehicle_is_valid(cName, b.ptr)) == 1
	} else if b.typ == BlipObject {
		return int(C.blip_is_valid(cName, b.ptr)) == 1
	}
	return false
}

func (b BaseObject) Destroy() {
	if b.typ == PlayerObject {
		C.player_destroy(b.ptr)
	} else if b.typ == VoiceChannelObject {
		C.voice_channel_destroy(b.ptr)
	} else if b.typ == CheckpointObject {
		C.checkpoint_destroy(b.ptr)
	} else if b.typ == ColshapeObject {
		C.col_shape_destroy(b.ptr)
	} else if b.typ == VehicleObject {
		C.vehicle_destroy(b.ptr)
	} else if b.typ == BlipObject {
		C.blip_destroy(b.ptr)
	}
}

func (b BaseObject) HasMetaData(key string) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if b.typ == PlayerObject {
		return int(C.player_has_meta_data(b.ptr, cKey)) == 1
	} else if b.typ == VoiceChannelObject {
		return int(C.voice_channel_has_meta_data(b.ptr, cKey)) == 1
	} else if b.typ == CheckpointObject {
		return int(C.checkpoint_has_meta_data(b.ptr, cKey)) == 1
	} else if b.typ == ColshapeObject {
		return int(C.col_shape_has_meta_data(b.ptr, cKey)) == 1
	} else if b.typ == VehicleObject {
		return int(C.vehicle_has_meta_data(b.ptr, cKey)) == 1
	} else if b.typ == BlipObject {
		return int(C.blip_has_meta_data(b.ptr, cKey)) == 1
	}

	return false
}

func (b BaseObject) MetaData(key string, val interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	var arr C.struct_array
	if b.typ == PlayerObject {
		arr = C.player_get_meta_data(b.ptr, cKey)
	} else if b.typ == VoiceChannelObject {
		arr = C.voice_channel_get_meta_data(b.ptr, cKey)
	} else if b.typ == CheckpointObject {
		arr = C.checkpoint_get_meta_data(b.ptr, cKey)
	} else if b.typ == ColshapeObject {
		arr = C.col_shape_get_meta_data(b.ptr, cKey)
	} else if b.typ == VehicleObject {
		arr = C.vehicle_get_meta_data(b.ptr, cKey)
	} else if b.typ == BlipObject {
		arr = C.blip_get_meta_data(b.ptr, cKey)
	}

	err := decode(arr, val)

	return err == nil
}

func (b BaseObject) SetMetaData(key string, value interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	arr, err := encode(value)
	if err != nil {
		return false
	}
	defer C.free(arr.array)

	bytes := (*C.uchar)(arr.array)
	if b.typ == PlayerObject {
		C.player_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.typ == VoiceChannelObject {
		C.voice_channel_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.typ == CheckpointObject {
		C.checkpoint_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.typ == ColshapeObject {
		C.col_shape_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.typ == VehicleObject {
		C.vehicle_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.typ == BlipObject {
		C.blip_set_meta_data(b.ptr, cKey, bytes, arr.size)
	}

	return true
}

func (b BaseObject) DeleteMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if b.typ == PlayerObject {
		C.player_delete_meta_data(b.ptr, cKey)
	} else if b.typ == VoiceChannelObject {
		C.voice_channel_delete_meta_data(b.ptr, cKey)
	} else if b.typ == CheckpointObject {
		C.checkpoint_delete_meta_data(b.ptr, cKey)
	} else if b.typ == ColshapeObject {
		C.col_shape_delete_meta_data(b.ptr, cKey)
	} else if b.typ == VehicleObject {
		C.vehicle_delete_meta_data(b.ptr, cKey)
	} else if b.typ == BlipObject {
		C.blip_delete_meta_data(b.ptr, cKey)
	}
}
