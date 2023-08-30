package altv

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

func getEntityData(e C.struct_entity) (typ entity.BaseObjectType, ptr unsafe.Pointer, id uint32, model uint32) {
	ptr = unsafe.Pointer(e.ptr)
	id = uint32(e.id)
	typ = entity.BaseObjectType(e.typ)
	model = uint32(e.model)

	return
}

func newBaseObjectArray[T entity.BaseObject](arr C.struct_array) []T {
	return cutil.NewArrayFunc[C.struct_entity, T](unsafe.Pointer(arr.array), int(arr.size), func(item C.struct_entity) T {
		v, err := factory.GetBaseObject[T](getEntityData(item))
		if err != nil {
			altlog.Errorln(fmt.Sprintf("[Go] newBaseObjectArray: %s", err.Error()))
		}
		return v
	})
}

func Players() []entity.Player {
	arr := C.core_get_players()
	return newBaseObjectArray[entity.Player](arr)
}

func PlayerByID(id uint32) (entity.Player, error) {
	p := C.core_get_base_object_by_i_d(C.uchar(entity.BaseTypePlayer), C.uint(id))
	return factory.GetBaseObject[entity.Player](getEntityData(p))
}

func VehicleByID(id uint32) (entity.Vehicle, error) {
	e := C.core_get_base_object_by_i_d(C.uchar(entity.BaseTypeVehicle), C.uint(id))
	return factory.GetBaseObject[entity.Vehicle](getEntityData(e))
}

func CreateVehicle(model uint32, pos Vector3, rot Vector3) (entity.Vehicle, error) {
	// TODO: validate model beforehand. best solution: data/vehmodels.bin

	e := C.core_create_vehicle(C.ulong(model), C.float(pos.X), C.float(pos.Y), C.float(pos.Z), C.float(rot.X), C.float(rot.Y), C.float(rot.Z))

	return factory.GetBaseObject[entity.Vehicle](getEntityData(e))
}
