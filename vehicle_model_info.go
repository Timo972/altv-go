package altv

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"

type VehicleModelType = uint8

const (
	Invalid VehicleModelType = iota
	Ped
	Automobile
	Plane
	Trailer
	QuadBike
	SubmarineCar
	AmphibiousAutomobile
	AmphibiousQuadBike
	Heli
	Blimp
	Autogyro
	Bike
	BMX
	Boat
	Train
	Submarine
	Object
)

type VehicleModelInfo struct {
	Title             string
	ModelType         VehicleModelType
	WheelsCount       uint8
	ArmoredWindows    bool
	AutoAttachTrailer bool
	Bones             []BoneInfo
	PrimaryColor      uint8
	SecondaryColor    uint8
	PearlColor        uint8
	WheelsColor       uint8
	InteriorColor     uint8
	DashboardColor    uint8

	ModKits       [2]uint16
	Extras        uint16
	DefaultExtras uint16
}

func (v *VehicleModelInfo) DoesExtraExist(extraId uint8) bool {
	return ((v.Extras & (1 << extraId)) != 0)
}

func (v *VehicleModelInfo) DoesExtraDefault(extraId uint8) bool {
	return ((v.DefaultExtras & (1 << extraId)) != 0)
}

func newVehicleModelInfo(info C.struct_vehicleModelInfo) VehicleModelInfo {
	return VehicleModelInfo{
		Title:             C.GoString(info.title),
		ModelType:         VehicleModelType(info.modelType),
		WheelsCount:       uint8(info.wheelsCount),
		ArmoredWindows:    uint8(info.hasArmoredWindows) == 1,
		AutoAttachTrailer: uint8(info.hasAutoAttachTrailer) == 1,
		Bones:             createBoneSlice(info.bones),
		PrimaryColor:      uint8(info.primaryColor),
		SecondaryColor:    uint8(info.secondaryColor),
		PearlColor:        uint8(info.pearlColor),
		WheelsColor:       uint8(info.wheelsColor),
		InteriorColor:     uint8(info.interiorColor),
		DashboardColor:    uint8(info.dashboardColor),

		ModKits:       [2]uint16{uint16(info.modKits[0]), uint16(info.modKits[1])},
		Extras:        uint16(info.extras),
		DefaultExtras: uint16(info.defaultExtras),
	}
}
