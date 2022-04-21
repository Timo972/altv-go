package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
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
	Ptr  unsafe.Pointer `json:"ptr"`
	Type BaseObjectType `json:"type"`
}

type Base interface {
	HasMetaData(key string) bool
	MetaData(key string, value interface{}) bool
	SetMetaData(key string, value interface{})
	DeleteMetaData(key string)
}

func (b BaseObject) Valid() bool {
	// TODO check if it works with player
	if b.Ptr == nil {
		return false
	}
	// if so add for other base object extenders
	if b.Type == PlayerObject {
		return int(C.player_is_valid(b.Ptr)) == 1
	} else if b.Type == VoiceChannelObject {
		return int(C.voice_channel_is_valid(b.Ptr)) == 1
	} else if b.Type == CheckpointObject {
		return int(C.checkpoint_is_valid(b.Ptr)) == 1
	} else if b.Type == ColshapeObject {
		return int(C.col_shape_is_valid(b.Ptr)) == 1
	} else if b.Type == VehicleObject {
		return int(C.vehicle_is_valid(b.Ptr)) == 1
	} else if b.Type == BlipObject {
		return int(C.blip_is_valid(b.Ptr)) == 1
	}
	return false
}

func (b BaseObject) Destroy() {
	if b.Type == PlayerObject {
		C.player_destroy(b.Ptr)
	} else if b.Type == VoiceChannelObject {
		C.voice_channel_destroy(b.Ptr)
	} else if b.Type == CheckpointObject {
		C.checkpoint_destroy(b.Ptr)
	} else if b.Type == ColshapeObject {
		C.col_shape_destroy(b.Ptr)
	} else if b.Type == VehicleObject {
		C.vehicle_destroy(b.Ptr)
	} else if b.Type == BlipObject {
		C.blip_destroy(b.Ptr)
	}
}

func (b BaseObject) HasMetaData(key string) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if b.Type == PlayerObject {
		return int(C.player_has_meta_data(b.Ptr, cKey)) == 1
	} else if b.Type == VoiceChannelObject {
		return int(C.voice_channel_has_meta_data(b.Ptr, cKey)) == 1
	} else if b.Type == CheckpointObject {
		return int(C.checkpoint_has_meta_data(b.Ptr, cKey)) == 1
	} else if b.Type == ColshapeObject {
		return int(C.col_shape_has_meta_data(b.Ptr, cKey)) == 1
	} else if b.Type == VehicleObject {
		return int(C.vehicle_has_meta_data(b.Ptr, cKey)) == 1
	} else if b.Type == BlipObject {
		return int(C.blip_has_meta_data(b.Ptr, cKey)) == 1
	}

	return false
}

func (b BaseObject) MetaData(key string, val interface{}) bool {
	/*cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	var arr C.struct_array
	if b.Type == PlayerObject {
		arr = C.player_get_meta_data(b.Ptr, cKey)
	} else if b.Type == VoiceChannelObject {
		arr = C.voice_channel_get_meta_data(b.Ptr, cKey)
	} else if b.Type == CheckpointObject {
		arr = C.checkpoint_get_meta_data(b.Ptr, cKey)
	} else if b.Type == ColshapeObject {
		arr = C.col_shape_get_meta_data(b.Ptr, cKey)
	} else if b.Type == VehicleObject {
		arr = C.vehicle_get_meta_data(b.Ptr, cKey)
	} else if b.Type == BlipObject {
		arr = C.blip_get_meta_data(b.Ptr, cKey)
	}*/

	// mValue := &MValue{Ptr: meta.Ptr, Type: uint8(meta.Type)}

	//return mValue.Value(val)
	return true
}

func (b BaseObject) SetMetaData(key string, value interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	protoValue, _ := newProtoMValue(value)
	out, err := serializeProtoMValue(protoValue)
	if err != nil {
		return false
	}

	arrayPtr := C.CBytes(out)
	defer C.free(arrayPtr)

	bytes := (*C.uchar)(arrayPtr)
	size := C.ulonglong(len(out))
	if b.Type == PlayerObject {
		C.player_set_meta_data(b.Ptr, cKey, bytes, size)
	} else if b.Type == VoiceChannelObject {
		C.voice_channel_set_meta_data(b.Ptr, cKey, bytes, size)
	} else if b.Type == CheckpointObject {
		C.checkpoint_set_meta_data(b.Ptr, cKey, bytes, size)
	} else if b.Type == ColshapeObject {
		C.col_shape_set_meta_data(b.Ptr, cKey, bytes, size)
	} else if b.Type == VehicleObject {
		C.vehicle_set_meta_data(b.Ptr, cKey, bytes, size)
	} else if b.Type == BlipObject {
		C.blip_set_meta_data(b.Ptr, cKey, bytes, size)
	}

	return true
}

func (b BaseObject) DeleteMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if b.Type == PlayerObject {
		C.player_delete_meta_data(b.Ptr, cKey)
	} else if b.Type == VoiceChannelObject {
		C.voice_channel_delete_meta_data(b.Ptr, cKey)
	} else if b.Type == CheckpointObject {
		C.checkpoint_delete_meta_data(b.Ptr, cKey)
	} else if b.Type == ColshapeObject {
		C.col_shape_delete_meta_data(b.Ptr, cKey)
	} else if b.Type == VehicleObject {
		C.vehicle_delete_meta_data(b.Ptr, cKey)
	} else if b.Type == BlipObject {
		C.blip_delete_meta_data(b.Ptr, cKey)
	}
}
