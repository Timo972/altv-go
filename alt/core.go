package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import (
	"unsafe"
)

var File FileApi = &fileApi{}

type fileApi struct {
}

type FileApi interface {
	Exists(path string) bool
	Read(path string) string
}

func (f *fileApi) Exists(path string) bool {
	cStr := C.CString(path)
	defer C.free(unsafe.Pointer(cStr))
	return int(C.core_file_exists(cStr)) == 1
}

func (f *fileApi) Read(path string) string {
	cStr := C.CString(path)
	defer C.free(unsafe.Pointer(cStr))
	cContent := C.core_read_file(cStr)
	return C.GoString(cContent)
}

func Hash(str string) uint32 {
	cStr := C.CString(str)
	defer C.free(unsafe.Pointer(cStr))
	return uint32(C.core_hash(cStr))
}

func EntityByID(id uint16) interface{} {
	entity := C.core_get_entity_by_id(C.ushort(id))

	entityType := BaseObjectType(entity.Type)

	if entityType == PlayerObject {
		p := newPlayer(entity.Ptr)
		return p
	} else if entityType == VehicleObject {
		v := newVehicle(entity.Ptr)
		return v
	} else if entityType == ColshapeObject {
		c := newColShape(entity.Ptr)
		return c
	} else if entityType == CheckpointObject {
		c := newCheckpoint(entity.Ptr)
		return c
	} else if entityType == VoiceChannelObject {
		v := newVoiceChannel(entity.Ptr)
		return v
	}

	return nil
}

func HasMetaData(key string) bool {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))
	return int(C.core_has_meta_data(cStr)) == 1
}

func GetMetaData(key string) interface{} {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))
	var mValue *MValue

	meta := C.core_get_meta_data(cStr)
	mValue = &MValue{Ptr: meta.Ptr, Type: uint8(meta.Type), Value: nil}

	return mValue.GetValue()
}

func SetMetaData(key string, value interface{}) {
	mValue := CreateMValue(value)
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))
	C.core_set_meta_data(cKey, mValue.Ptr)
}

func DeleteMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))
	C.core_delete_meta_data(cKey)
}

func HasSyncedMetaData(key string) bool {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))
	return int(C.core_has_synced_meta_data(cStr)) == 1
}

func GetSyncedMetaData(key string) interface{} {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))
	var mValue *MValue

	meta := C.core_get_synced_meta_data(cStr)
	mValue = &MValue{Ptr: meta.Ptr, Type: uint8(meta.Type), Value: nil}

	return mValue.GetValue()
}

func SetSyncedMetaData(key string, value interface{}) {
	mValue := CreateMValue(value)
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))
	C.core_set_synced_meta_data(cKey, mValue.Ptr)
}

func DeleteSyncedMetaData(key string) {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))
	C.core_delete_synced_meta_data(cKey)
}

func StartResource(name string) bool {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	return int(C.core_start_resource(cName)) == 1
}

func StopResource(name string) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	C.core_stop_resource(cName)
}

func RestartResource(name string) bool {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	return int(C.core_restart_resource(cName)) == 1
}

func PlayersByName(name string) []*Player {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	arr := C.core_get_players_by_name(cName)

	size := int(arr.size)
	values := (*[1 << 28]unsafe.Pointer)(arr.array)[:size:size]

	players := make([]*Player, size)

	if size == 0 {
		return players
	}

	for i := 0; i < size; i++ {
		player := values[i]
		players[i] = newPlayer(player)
	}

	return players
}

func Players() []*Player {
	arr := C.core_get_players()

	return newPlayerArray(arr)
}

func Vehicles() []*Vehicle {
	arr := C.core_get_vehicles()

	return newVehicleArray(arr)
}

func SetPassword(password string) {
	cPassword := C.CString(password)
	defer C.free(unsafe.Pointer(cPassword))
	C.core_set_password(cPassword)
}

func Branch() string {
	return C.GoString(C.core_get_branch())
}

func Version() string {
	return C.GoString(C.core_get_version())
}

func RootDir() string {
	return C.GoString(C.core_get_root_directory())
}

func SDKHash() string {
	return C.GoString(C.core_get_sdk_hash())
}

func Debug() bool {
	return int(C.core_is_debug()) == 1
}
