package entity

// #include "capi.h"
import "C"
import (
	"unsafe"
)

type Vehicle interface {
	Entity
}

type AltVehicle struct {
	AltEntity
	model uint32
}

func NewVehicle(ptr unsafe.Pointer, id uint32, model uint32) Vehicle {
	v := &AltVehicle{
		AltEntity{
			AltWorldObject{
				AltBaseObject: newBaseObject(TypeVehicle, ptr, id),
			},
		},
		model,
	}

	return v
}

func (v *AltVehicle) Model() uint32 {
	return v.model
}
