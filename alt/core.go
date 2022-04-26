package alt

// #cgo CFLAGS: -I../c-api/lib
// #cgo LDFLAGS: -L../c-api/lib -lcapi
// #include <stdlib.h>
// #include "../c-api/src/capi.h"
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

func EntityByID(id uint16) *Entity {
	return newEntity(C.core_get_entity_by_i_d(C.ushort(id)))
}

func HasMetaData(key string) bool {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))
	return int(C.core_has_meta_data(cStr)) == 1
}

func MetaData(key string, value interface{}) bool {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))

	meta := C.core_get_meta_data(cStr)
	err := decode(meta, value)
	if err != nil {
		LogError(err.Error())
		return false
	}

	return true
}

func SetMetaData(key string, value interface{}) bool {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	arr, err := encode(value)
	if err != nil {
		return false
	}
	defer C.free(arr.array)

	C.core_set_meta_data(cKey, (*C.uchar)(arr.array), arr.size)
	return true
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

func SyncedMetaData(key string, value interface{}) bool {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))

	meta := C.core_get_synced_meta_data(cStr)
	err := decode(meta, value)
	if err != nil {
		return false
	}

	return true
}

func SetSyncedMetaData(key string, value interface{}) bool {
	// mValue := createMValue(value)
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	arr, err := encode(value)
	if err != nil {
		return false
	}
	defer C.free(arr.array)

	C.core_set_synced_meta_data(cKey, (*C.uchar)(arr.array), arr.size)
	return true
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

func RestartResource(name string) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	C.core_restart_resource(cName)
}

func PlayersByName(name string) []*Player {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	arr := C.core_get_players_by_name(cName)

	return newPlayerArray(arr)
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
	return C.GoString(C.core_get_s_d_k_hash())
}

func Debug() bool {
	return int(C.core_is_debug()) == 1
}

// TODO missing:
// Core_GetEntities
// Core_GetRequiredPermissions
// Core_GetOptionalPermissions
// Core_DestroyBaseObject
// Core_GetNetTime
// Core_GetAllResources
// Core_StringToSHA256
// Core_StopServer
// Core_GetVehicleModelByHash
// Core_GetServerConfig
// Core_HashServerPassword
