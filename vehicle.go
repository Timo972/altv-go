package altv

// #include "capi.h"
import "C"
import (
	"unsafe"
)

type Vehicle interface {
	Entity
}

type vehicle struct {
	entity
	model uint32
}

func NewVehicle(ptr unsafe.Pointer, id uint32, model uint32) Vehicle {
	v := &vehicle{
		entity{
			worldObject{
				baseObject: newBaseObject(BaseTypeVehicle, ptr, id),
			},
		},
		model,
	}

	return v
}

func VehicleByID(id uint32) (Vehicle, error) {
	return getBaseObject[Vehicle](C.core_get_base_object_by_i_d(C.uchar(BaseTypeVehicle), C.uint(id)))
}

func CreateVehicle(model uint32, pos Vector3, rot Vector3) (Vehicle, error) {
	// TODO: validate model beforehand. best solution: data/vehmodels.bin

	e := C.core_create_vehicle(C.ulong(model), C.float(pos.X), C.float(pos.Y), C.float(pos.Z), C.float(rot.X), C.float(rot.Y), C.float(rot.Z))

	return getBaseObject[Vehicle](e)
}

func (v *vehicle) Model() uint32 {
	return v.model
}
