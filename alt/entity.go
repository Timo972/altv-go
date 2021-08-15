package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import (
	"unsafe"

	"github.com/shockdev04/altv-go-pkg/internal/module"
)

type Entity struct {
	WorldObject
}

func NewEntity(e unsafe.Pointer) *Entity {
	entity := &Entity{}
	entity.Ptr = e
	//entity.Type = PlayerObject

	return entity
}

func (e Entity) Model() uint32 {
	if e.Type == PlayerObject {
		return uint32(C.player_get_model(e.Ptr))
	} else if e.Type == VehicleObject {
		return uint32(C.vehicle_get_model(e.Ptr))
	}
	return 0
}

func (e Entity) Detach() {
	if e.Type == PlayerObject {
		C.player_detach(e.Ptr)
	} else if e.Type == VehicleObject {
		C.vehicle_detach(e.Ptr)
	}
}

// AttachToEntity TODO: make capi accept x, y, z instead of Position and Rotation
func (e Entity) AttachToEntity(entity Entity, otherBoneIndex int16, myBoneIndex int16, position Position, rotation Rotation, collision bool, noFixedRotation bool) {
	//C.player_attach_to_entity(p.Ptr, entity.Ptr, C.int(otherBoneIndex), C.int(myBoneIndex), )
}

func (e Entity) SetVisible(toggle bool) {
	if e.Type == PlayerObject {
		C.player_set_visible(e.Ptr, C.int(module.Bool2int(toggle)))
	} else if e.Type == VehicleObject {
		C.vehicle_set_visible(e.Ptr, C.int(module.Bool2int(toggle)))
	}
}

func (e Entity) Visible() bool {
	if e.Type == PlayerObject {
		return int(C.player_get_visible(e.Ptr)) == 1
	} else if e.Type == VehicleObject {
		return int(C.vehicle_get_visible(e.Ptr)) == 1
	}
	return false
}

func (e Entity) ID() uint16 {
	if e.Type == PlayerObject {
		return uint16(C.player_get_id(e.Ptr))
	} else if e.Type == VehicleObject {
		return uint16(C.vehicle_get_id(e.Ptr))
	}
	return 0
}

func (e Entity) NetworkOwner() *Player {
	var cPtr unsafe.Pointer
	if e.Type == PlayerObject {
		cPtr = unsafe.Pointer(C.player_get_network_owner(e.Ptr))
	} else if e.Type == VehicleObject {
		cPtr = unsafe.Pointer(C.vehicle_get_network_owner(e.Ptr))
	}
	return NewPlayer(cPtr)
}

func (e Entity) SetNetworkOwner(owner *Player, disableMigration bool) {
	if e.Type == PlayerObject {
		C.player_set_network_owner(e.Ptr, owner.Ptr, C.int(module.Bool2int(disableMigration)))
	} else if e.Type == VehicleObject {
		C.vehicle_set_network_owner(e.Ptr, owner.Ptr, C.int(module.Bool2int(disableMigration)))
	}
}

func (e Entity) Rotation() Rotation {
	var cRot C.struct_rot
	if e.Type == PlayerObject {
		cRot = C.player_get_rotation(e.Ptr)
	} else if e.Type == VehicleObject {
		cRot = C.vehicle_get_rotation(e.Ptr)
	}
	return Rotation{X: float32(cRot.roll), Y: float32(cRot.pitch), Z: float32(cRot.yaw)}
}

func (e Entity) SetRotation(rotation Rotation) {
	if e.Type == PlayerObject {
		C.player_set_rotation(e.Ptr, C.float(rotation.X), C.float(rotation.Y), C.float(rotation.Z))
	} else if e.Type == VehicleObject {
		C.vehicle_set_rotation(e.Ptr, C.float(rotation.X), C.float(rotation.Y), C.float(rotation.Z))
	}
}

func (e Entity) HasSyncedMetaData(key string) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if e.Type == PlayerObject {
		return int(C.player_has_synced_meta_data(e.Ptr, cKey)) == 1
	}

	if e.Type == VehicleObject {
		return int(C.vehicle_has_synced_meta_data(e.Ptr, cKey)) == 1
	}

	return false
}

func (e Entity) GetSyncedMetaData(key string) interface{} {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if e.Type == PlayerObject {
		meta := C.player_get_synced_meta_data(e.Ptr, cKey)
		mValue := &MValue{Ptr: meta.Ptr, Type: uint8(meta.Type), Value: nil}

		return mValue.GetValue()
	}

	if e.Type == VehicleObject {
		meta := C.vehicle_get_synced_meta_data(e.Ptr, cKey)
		mValue := &MValue{Ptr: meta.Ptr, Type: uint8(meta.Type), Value: nil}

		return mValue.GetValue()
	}

	return nil
}

func (e Entity) HasStreamSyncedMetaData(key string) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if e.Type == PlayerObject {
		return int(C.player_has_stream_synced_meta_data(e.Ptr, cKey)) == 1
	}

	if e.Type == VehicleObject {
		return int(C.vehicle_has_stream_synced_meta_data(e.Ptr, cKey)) == 1
	}

	return false
}

func (e Entity) GetStreamSyncedMetaData(key string) interface{} {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if e.Type == PlayerObject {
		meta := C.player_get_stream_synced_meta_data(e.Ptr, cKey)
		mValue := &MValue{Ptr: meta.Ptr, Type: uint8(meta.Type), Value: nil}

		return mValue.GetValue()
	}

	if e.Type == VehicleObject {
		meta := C.vehicle_get_stream_synced_meta_data(e.Ptr, cKey)
		mValue := &MValue{Ptr: meta.Ptr, Type: uint8(meta.Type), Value: nil}

		return mValue.GetValue()
	}


	return nil
}

func (e Entity) SetSyncedMetaData(key string, value interface{}) {
	mValue := CreateMValue(value)

	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if e.Type == PlayerObject {
		C.player_set_synced_meta_data(e.Ptr, cKey, mValue.Ptr)
	}

	if e.Type == VehicleObject {
		C.vehicle_set_synced_meta_data(e.Ptr, cKey, mValue.Ptr)
	}
}

func (e Entity) DeleteSyncedMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if e.Type == PlayerObject {
		C.player_delete_synced_meta_data(e.Ptr, cKey)
	}

	if e.Type == VehicleObject {
		C.vehicle_delete_synced_meta_data(e.Ptr, cKey)
	}
}

func (e Entity) SetStreamSyncedMetaData(key string, value interface{}) {
	mValue := CreateMValue(value)

	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if e.Type == PlayerObject {
		C.player_set_stream_synced_meta_data(e.Ptr, cKey, mValue.Ptr)
	}

	if e.Type == VehicleObject {
		C.vehicle_set_stream_synced_meta_data(e.Ptr, cKey, mValue.Ptr)
	}
}

func (e Entity) DeleteStreamSyncedMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	if e.Type == PlayerObject {
		C.player_delete_stream_synced_meta_data(e.Ptr, cKey)
	}

	if e.Type == VehicleObject {
		C.vehicle_delete_stream_synced_meta_data(e.Ptr, cKey)
	}
}