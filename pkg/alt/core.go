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
	"crypto/sha256"
	"strings"
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

/*func Hash(str string) uint32 {
	cStr := C.CString(str)
	defer C.free(unsafe.Pointer(cStr))
	return uint32(C.core_hash(cStr))
}*/

func EntityByID(id uint16) IEntity {
	return getEntity(C.core_get_entity_by_i_d(C.ushort(id)))
}

func HasMetaData(key string) bool {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))
	return int(C.core_has_meta_data(cStr)) == 1
}

func MetaData(key string, value interface{}) error {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))

	// meta := C.core_get_meta_data(cStr)
	//err := decode(meta, value)

	return nil
}

func SetMetaData(key string, value interface{}) error {
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	/*arr, err := encode(value)
	if err != nil {
		return false
	}
	defer C.free(arr.array)

	C.core_set_meta_data(cKey, (*C.uchar)(arr.array), arr.size)*/
	return nil
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

func SyncedMetaData(key string, value interface{}) error {
	cStr := C.CString(key)
	defer C.free(unsafe.Pointer(cStr))

	//meta := C.core_get_synced_meta_data(cStr)
	//err := decode(meta, value)

	return nil
}

func SetSyncedMetaData(key string, value interface{}) error {
	// mValue := createMValue(value)
	cKey := C.CString(key)
	defer C.free(unsafe.Pointer(cKey))

	/*arr, err := encode(value)
	if err != nil {
		return false
	}
	defer C.free(arr.array)

	C.core_set_synced_meta_data(cKey, (*C.uchar)(arr.array), arr.size)*/
	return nil
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

func PlayersByName(name string) []IPlayer {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	arr := C.core_get_players_by_name(cName)

	return newPlayerArray(arr)
}

func Players() []IPlayer {
	arr := C.core_get_players()

	return newPlayerArray(arr)
}

func Vehicles() []IVehicle {
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
// Core_DestroyBaseObject

func RequiredPermissions() []Permission {
	arr := C.core_get_required_permissions()
	return newPermissionArray(arr)
}

func OptionalPermissions() []Permission {
	arr := C.core_get_optional_permissions()
	return newPermissionArray(arr)
}

func NetTime() uint32 {
	return uint32(C.core_get_net_time())
}

func Entities() []IEntity {
	arr := C.core_get_entities()
	return newEntityArray(arr)
}

func ServerConfig(v interface{}) error {
	// arr := C.core_get_server_config()
	//return decode(arr, v)
	return nil
}

func HashPassword(password string) uint64 {
	cPassword := C.CString(password)
	defer C.free(unsafe.Pointer(cPassword))
	return uint64(C.core_hash_server_password(cPassword))
}

func VehicleModelByHash(hash uint32) VehicleModelInfo {
	// return (*VehicleModelInfo)(C.core_get_vehicle_model_info(C.uint(hash)))
	return newVehicleModelInfo(C.core_get_vehicle_model_by_hash(C.uint(hash)))
}

func PedModelByHash(hash uint32) PedModelInfo {
	return newPedModelInfo(C.core_get_ped_model_by_hash(C.uint(hash)))
}

func StopServer() {
	C.core_stop_server()
}

/*func HashSHA256(str string) string {
	cStr := C.CString(str)
	defer C.free(unsafe.Pointer(cStr))
	return C.GoString(C.core_string_to_s_h_a256(cStr))
}*/

func HashSHA256(str string) string {
	h := sha256.New()
	return string(h.Sum([]byte(str)))
}

func Hash(str string) uint32 {
	hash := uint32(0)

	for _, c := range strings.ToLower(str) {
		hash += uint32(c)
		hash += hash << 10
		hash ^= hash >> 6
	}

	hash += hash << 3
	hash ^= hash >> 11
	hash += hash << 15

	return hash
}
