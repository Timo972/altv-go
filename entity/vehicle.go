package entity

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

func (v *vehicle) Model() uint32 {
	return v.model
}
