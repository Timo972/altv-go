package alt

import (
	"unsafe"

	"github.com/timo972/altv-go/internal/altcapi"
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
	Type BaseObjectType
}

/*type Base interface {
	HasMetaData(key string) bool
	MetaData(key string, value interface{}) bool
	SetMetaData(key string, value interface{})
	DeleteMetaData(key string)
}*/

func (b BaseObject) Valid() bool {
	if b.ptr == nil {
		return false
	}

	// if so add for other base object extenders
	if b.Type == PlayerObject {
		return altcapi.Player_is_valid(CurrentResource.Name(), b.ptr) == 1
	} else if b.Type == VoiceChannelObject {
		return altcapi.Voice_channel_is_valid(CurrentResource.Name(), b.ptr) == 1
	} else if b.Type == CheckpointObject {
		return altcapi.Checkpoint_is_valid(CurrentResource.Name(), b.ptr) == 1
	} else if b.Type == ColshapeObject {
		return altcapi.Col_shape_is_valid(CurrentResource.Name(), b.ptr) == 1
	} else if b.Type == VehicleObject {
		return altcapi.Vehicle_is_valid(CurrentResource.Name(), b.ptr) == 1
	} else if b.Type == BlipObject {
		return altcapi.Blip_is_valid(CurrentResource.Name(), b.ptr) == 1
	}
	return false
}

func (b BaseObject) Destroy() {
	if b.Type == PlayerObject {
		altcapi.Player_destroy(b.ptr)
	} else if b.Type == VoiceChannelObject {
		altcapi.Voice_channel_destroy(b.ptr)
	} else if b.Type == CheckpointObject {
		altcapi.Checkpoint_destroy(b.ptr)
	} else if b.Type == ColshapeObject {
		altcapi.Col_shape_destroy(b.ptr)
	} else if b.Type == VehicleObject {
		altcapi.Vehicle_destroy(b.ptr)
	} else if b.Type == BlipObject {
		altcapi.Blip_destroy(b.ptr)
	}
}

func (b BaseObject) HasMetaData(key string) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if b.Type == PlayerObject {
		return int(C.player_has_meta_data(b.ptr, cKey)) == 1
	} else if b.Type == VoiceChannelObject {
		return int(C.voice_channel_has_meta_data(b.ptr, cKey)) == 1
	} else if b.Type == CheckpointObject {
		return int(C.checkpoint_has_meta_data(b.ptr, cKey)) == 1
	} else if b.Type == ColshapeObject {
		return int(C.col_shape_has_meta_data(b.ptr, cKey)) == 1
	} else if b.Type == VehicleObject {
		return int(C.vehicle_has_meta_data(b.ptr, cKey)) == 1
	} else if b.Type == BlipObject {
		return int(C.blip_has_meta_data(b.ptr, cKey)) == 1
	}

	return false
}

func (b BaseObject) MetaData(key string, val interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	var arr C.struct_array
	if b.Type == PlayerObject {
		arr = C.player_get_meta_data(b.ptr, cKey)
	} else if b.Type == VoiceChannelObject {
		arr = C.voice_channel_get_meta_data(b.ptr, cKey)
	} else if b.Type == CheckpointObject {
		arr = C.checkpoint_get_meta_data(b.ptr, cKey)
	} else if b.Type == ColshapeObject {
		arr = C.col_shape_get_meta_data(b.ptr, cKey)
	} else if b.Type == VehicleObject {
		arr = C.vehicle_get_meta_data(b.ptr, cKey)
	} else if b.Type == BlipObject {
		arr = C.blip_get_meta_data(b.ptr, cKey)
	}

	err := decode(arr, val)
	if err != nil {
		return false
	}

	return true
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
	if b.Type == PlayerObject {
		C.player_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.Type == VoiceChannelObject {
		C.voice_channel_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.Type == CheckpointObject {
		C.checkpoint_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.Type == ColshapeObject {
		C.col_shape_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.Type == VehicleObject {
		C.vehicle_set_meta_data(b.ptr, cKey, bytes, arr.size)
	} else if b.Type == BlipObject {
		C.blip_set_meta_data(b.ptr, cKey, bytes, arr.size)
	}

	return true
}

func (b BaseObject) DeleteMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if b.Type == PlayerObject {
		C.player_delete_meta_data(b.ptr, cKey)
	} else if b.Type == VoiceChannelObject {
		C.voice_channel_delete_meta_data(b.ptr, cKey)
	} else if b.Type == CheckpointObject {
		C.checkpoint_delete_meta_data(b.ptr, cKey)
	} else if b.Type == ColshapeObject {
		C.col_shape_delete_meta_data(b.ptr, cKey)
	} else if b.Type == VehicleObject {
		C.vehicle_delete_meta_data(b.ptr, cKey)
	} else if b.Type == BlipObject {
		C.blip_delete_meta_data(b.ptr, cKey)
	}
}
