package alt

// #cgo CFLAGS: -I../c-api/lib
// #cgo LDFLAGS: -L../c-api/lib -lcapi
// #include <stdlib.h>
// #include "../c-api/src/capi.h"
import "C"
import (
	"fmt"
	"unsafe"

	"github.com/timo972/altv-go-pkg/internal/module"
)

type Entity struct {
	WorldObject
}

type IEntity interface {
	getPtr() unsafe.Pointer
	getType() BaseObjectType
}

func newEntity(e C.struct_entity) *Entity {
	t := BaseObjectType(e.Type)

	if t != PlayerObject && t != VehicleObject {
		return nil
	}

	entity := &Entity{}
	entity.Ptr = e.Ptr
	entity.Type = t

	return entity
}

func newCEntity(e IEntity) C.struct_entity {
	return C.struct_entity{
		Ptr:  e.getPtr(),
		Type: C.uchar(e.getType()),
	}
}

func (e Entity) getPtr() unsafe.Pointer {
	return e.Ptr
}

func (e Entity) getType() BaseObjectType {
	return e.Type
}

func (e Entity) String() string {
	return fmt.Sprintf("Entity{}")
}

func (e Entity) IsPlayer() bool {
	return e.Type == PlayerObject
}

func (e Entity) IsVehicle() bool {
	return e.Type == VehicleObject
}

func (e Entity) AsPlayer() *Player {
	if e.Type != PlayerObject {
		return nil
	}

	return newPlayer(e.Ptr)
}

func (e Entity) AsVehicle() *Vehicle {
	if e.Type != VehicleObject {
		return nil
	}

	return newVehicle(e.Ptr)
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

func (e Entity) AttachToEntity(entity IEntity, otherBoneIndex int16, myBoneIndex int16, position Vector3, rotation Vector3, collision bool, noFixedRotation bool) {
	if e.Type == PlayerObject {
		C.player_attach_to_entity(e.Ptr, newCEntity(entity), C.int(otherBoneIndex), C.int(myBoneIndex), newCPosition(position), newCRotation(rotation), C.int(module.Bool2int(collision)), C.int(module.Bool2int(noFixedRotation)))
	} else if e.Type == VehicleObject {
		C.vehicle_attach_to_entity(e.Ptr, newCEntity(entity), C.int(otherBoneIndex), C.int(myBoneIndex), newCPosition(position), newCRotation(rotation), C.int(module.Bool2int(collision)), C.int(module.Bool2int(noFixedRotation)))
	}
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
		return uint16(C.player_get_i_d(e.Ptr))
	} else if e.Type == VehicleObject {
		return uint16(C.vehicle_get_i_d(e.Ptr))
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
	return newPlayer(cPtr)
}

func (e Entity) SetNetworkOwner(owner *Player, disableMigration bool) {
	if e.Type == PlayerObject {
		C.player_set_network_owner(e.Ptr, owner.Ptr, C.int(module.Bool2int(disableMigration)))
	} else if e.Type == VehicleObject {
		C.vehicle_set_network_owner(e.Ptr, owner.Ptr, C.int(module.Bool2int(disableMigration)))
	}
}

func (e Entity) Rotation() Vector3 {
	var cRot C.struct_rot
	if e.Type == PlayerObject {
		cRot = C.player_get_rotation(e.Ptr)
	} else if e.Type == VehicleObject {
		cRot = C.vehicle_get_rotation(e.Ptr)
	}
	return Vector3{X: float32(cRot.roll), Y: float32(cRot.pitch), Z: float32(cRot.yaw)}
}

func (e Entity) SetRotation(rotation Vector3) {
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

func (e Entity) SyncedMetaData(key string, val interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	var meta C.struct_array
	if e.Type == PlayerObject {
		meta = C.player_get_synced_meta_data(e.Ptr, cKey)
	} else if e.Type == VehicleObject {
		meta = C.vehicle_get_synced_meta_data(e.Ptr, cKey)
	}

	err := decode(meta, val)
	if err != nil {
		return false
	}

	return true
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

func (e Entity) StreamSyncedMetaData(key string, value interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	var meta C.struct_array
	if e.Type == PlayerObject {
		meta = C.player_get_stream_synced_meta_data(e.Ptr, cKey)
	} else if e.Type == VehicleObject {
		meta = C.vehicle_get_stream_synced_meta_data(e.Ptr, cKey)
	}

	err := decode(meta, value)
	if err != nil {
		return false
	}

	return true
}

func (e Entity) SetSyncedMetaData(key string, value interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	arr, err := encode(value)
	if err != nil {
		return false
	}
	defer C.free(arr.array)

	bytes := (*C.uchar)(arr.array)

	if e.Type == PlayerObject {
		C.player_set_synced_meta_data(e.Ptr, cKey, bytes, arr.size)
	} else if e.Type == VehicleObject {
		C.vehicle_set_synced_meta_data(e.Ptr, cKey, bytes, arr.size)
	}

	return true
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

func (e Entity) SetStreamSyncedMetaData(key string, value interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	arr, err := encode(value)
	if err != nil {
		return false
	}
	defer C.free(arr.array)

	bytes := (*C.uchar)(arr.array)

	if e.Type == PlayerObject {
		C.player_set_stream_synced_meta_data(e.Ptr, cKey, bytes, arr.size)
	} else if e.Type == VehicleObject {
		C.vehicle_set_stream_synced_meta_data(e.Ptr, cKey, bytes, arr.size)
	}

	return true
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

func (e Entity) Streamed() bool {
	if e.Type == PlayerObject {
		return int(C.player_get_streamed(e.Ptr)) == 1
	} else if e.Type == VehicleObject {
		return int(C.vehicle_get_streamed(e.Ptr)) == 1
	}
	return false
}

func (e Entity) SetStreamed(toggle bool) {
	state := C.int(module.Bool2int(toggle))
	if e.Type == PlayerObject {
		C.player_set_streamed(e.Ptr, state)
	} else if e.Type == VehicleObject {
		C.vehicle_set_streamed(e.Ptr, state)
	}
}

func (e Entity) IsFrozen() bool {
	var cFrozen C.int
	if e.Type == PlayerObject {
		cFrozen = C.player_is_frozen(e.Ptr)
	} else if e.Type == VehicleObject {
		cFrozen = C.vehicle_is_frozen(e.Ptr)
	}

	return int(cFrozen) == 1
}

func (e Entity) SetFrozen(state bool) {
	s := C.int(module.Bool2int(state))
	if e.Type == PlayerObject {
		C.player_set_frozen(e.Ptr, s)
	} else if e.Type == VehicleObject {
		C.vehicle_set_frozen(e.Ptr, s)
	}
}

func (e Entity) HasCollision() bool {
	var cCol C.int
	if e.Type == PlayerObject {
		cCol = C.player_has_collision(e.Ptr)
	} else if e.Type == VehicleObject {
		cCol = C.vehicle_has_collision(e.Ptr)
	}

	return int(cCol) == 1
}

func (e Entity) SetCollision(state bool) {
	s := C.int(module.Bool2int(state))
	if e.Type == PlayerObject {
		C.player_set_collision(e.Ptr, s)
	} else if e.Type == VehicleObject {
		C.vehicle_set_collision(e.Ptr, s)
	}
}
