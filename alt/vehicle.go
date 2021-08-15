package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"
import "unsafe"

type VehicleModCategory = uint8

const (
	Aerials VehicleModCategory = iota
	AirFilter
	ArchCover
	Armor
	BackWheels
	Brakes
	ColumnShifterLeavers
	Dashboard
	Dial
	DoorSpeaker
	Engine
	EngineBlock
	Exhaust
	Fender
	Frame
	FrontBumper
	FrontWheels
	Grille
	Hood
	Horn
	Hydraulics
	Livery
	Ornaments
	Plaques
	Plateholder
	RearBumper
	RightFender
	Roof
	Seats
	SideSkirt
	Speakers
	Spoiler
	SteeringWheel
	Struts
	Suspension
	Tank
	TireSmoke
	Transmission
	Trim
	TrimDesign
	Trunk
	Turbo
	Unk1
	Unk2
	Unk3
	Unk4
	VanityPlates
	Windows
	XenonLights
)

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

func (v Vehicle) Driver() *Player {
	cPtr := C.vehicle_get_driver(v.Ptr)
	player := NewPlayer(unsafe.Pointer(cPtr))
	return player
}

func (v Vehicle) IsDestroyed() bool {
	return int(C.vehicle_is_destroyed(v.Ptr)) == 1
}

func (v Vehicle) Mod(category VehicleModCategory) uint8 {
	return uint8(C.vehicle_get_mod(v.Ptr, C.uint(category)))
}

func (v Vehicle) ModsCount(category VehicleModCategory) uint8 {
	return uint8(C.vehicle_get_mods_count(v.Ptr, C.uint(category)))
}

func (v Vehicle) ModKit() uint8 {
	return uint8(C.vehicle_get_mod_kit(v.Ptr))
}

func (v Vehicle) IsPrimaryColorRGB() bool {
	return int(C.vehicle_is_primary_color_r_g_b(v.Ptr)) == 1
}

func (v Vehicle) GetPrimaryColor() {
	
}