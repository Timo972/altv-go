package altv

// #include <stdlib.h>
// #include "capi.h"
import "C"
import (
	"fmt"
	"unsafe"

	"github.com/timo972/altv-go/altlog"
	"github.com/timo972/altv-go/entity"
	"github.com/timo972/altv-go/factory"
	"github.com/timo972/altv-go/internal/cutil"
)

func getEntityData(e *C.struct_baseObject) (typ entity.BaseObjectType, ptr unsafe.Pointer, id uint32, model uint32) {
	ptr = unsafe.Pointer(e.ptr)
	id = uint32(e.id)
	typ = entity.BaseObjectType(e.typ)
	model = uint32(e.model)

	return
}

func newBaseObjectArray[T entity.BaseObject](arr C.struct_array) []T {
	entities := cutil.NewArrayFunc[*C.struct_baseObject, T](unsafe.Pointer(arr.ptr), int(arr.size), func(item *C.struct_baseObject) T {
		v, err := factory.GetBaseObject[T](getEntityData(item))
		C.free(unsafe.Pointer(item))
		if err != nil {
			altlog.Errorln(fmt.Sprintf("[Go] newBaseObjectArray: %s", err.Error()))
		}
		return v
	})
	// TODO: not sure, but i think we are leaking memory here: arr is allocated in cpp runtime using new CBaseObject*[arr.size];
	// C.free(arr.ptr) crashes and logs double free :|
	return entities
}

func Players() []entity.Player {
	arr := C.core_get_players()
	return newBaseObjectArray[entity.Player](arr)
}

func PlayerByID(id uint32) (entity.Player, error) {
	p := C.core_get_base_object_by_id(C.uchar(entity.TypePlayer), C.uint(id))
	defer C.free(unsafe.Pointer(p))
	return factory.GetBaseObject[entity.Player](getEntityData(p))
}

func Vehicles() []entity.Vehicle {
	arr := C.core_get_vehicles()
	return newBaseObjectArray[entity.Vehicle](arr)
}

func VehicleByID(id uint32) (entity.Vehicle, error) {
	vehicle := C.core_get_base_object_by_id(C.uchar(entity.TypePlayer), C.uint(id))
	defer C.free(unsafe.Pointer(vehicle))
	return factory.GetBaseObject[entity.Vehicle](getEntityData(vehicle))
}

func CreateVehicle(model uint32, pos Vector3, rot Vector3) (entity.Vehicle, error) {
	// TODO: validate model beforehand. best solution: data/vehmodels.bin

	// core_create_vehicle allocates C.struct_baseObject
	baseObject := C.core_create_vehicle(C.ulong(model), C.float(pos.X), C.float(pos.Y), C.float(pos.Z), C.float(rot.X), C.float(rot.Y), C.float(rot.Z))
	// free memory allocated by runtime
	defer C.free(unsafe.Pointer(baseObject))

	return factory.GetBaseObject[entity.Vehicle](getEntityData(baseObject))
}
