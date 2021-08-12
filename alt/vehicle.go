package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"

type Vehicle struct {
	Entity
}

func NewVehicle(model uint32, pos Position, rot Rotation) *Vehicle {
	vehicle := &Vehicle{}
	vehicle.Ptr = C.core_create_vehicle(C.ulong(model), C.float(pos.X), C.float(pos.Y), C.float(pos.Z),
		C.float(rot.X), C.float(rot.Y), C.float(rot.Z))
	vehicle.Type = VehicleObject

	return vehicle
}
