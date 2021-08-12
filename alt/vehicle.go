package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import "unsafe"

type Vehicle struct {
	Entity
}

func NewVehicle(p unsafe.Pointer) *Vehicle {
	vehicle := &Vehicle{}
	vehicle.Ptr = p
	vehicle.Type = VehicleObject

	return vehicle
}

func CreateVehicle(model uint32, pos Position, rot Rotation) *Vehicle {
	vehicle := C.core_create_vehicle(C.ulong(model), C.float(pos.X), C.float(pos.Y), C.float(pos.Z),
		C.float(rot.X), C.float(rot.Y), C.float(rot.Z))

	return NewVehicle(vehicle)
}
