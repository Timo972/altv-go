package alt

// #cgo windows CFLAGS: -I../c-api/lib/win32
// #cgo windows LDFLAGS: -L../c-api/lib/win32 -lcapi
// #cgo linux CFLAGS: -I../c-api/lib/linux
// #cgo linux LDFLAGS: -L../c-api/lib/linux -lcapi
// #include <stdlib.h>
// #include "../c-api/src/capi.h"
import "C"
import "math"

const (
	DefaultDimension int32 = 0
	MaxDimension     int32 = math.MaxInt32
	MinDimension     int32 = math.MinInt32
)

type WorldObject struct {
	BaseObject
}

type World interface {
	Position() *Vector3
	SetPosition()
	Dimension() int32
	SetDimension()
}

func (w WorldObject) Position() Vector3 {
	var cPos C.struct_pos

	if w.Type == PlayerObject {
		cPos = C.player_get_position(w.Ptr)
	} else if w.Type == CheckpointObject {
		cPos = C.checkpoint_get_position(w.Ptr)
	} else if w.Type == ColshapeObject {
		cPos = C.col_shape_get_position(w.Ptr)
	} else if w.Type == VehicleObject {
		cPos = C.vehicle_get_position(w.Ptr)
	} else if w.Type == BlipObject {
		cPos = C.blip_get_position(w.Ptr)
	}

	return Vector3{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
}

func (w WorldObject) SetPosition(pos Vector3) {
	if w.Type == PlayerObject {
		C.player_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
	} else if w.Type == CheckpointObject {
		C.checkpoint_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
	} else if w.Type == ColshapeObject {
		C.col_shape_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
	} else if w.Type == VehicleObject {
		C.vehicle_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
	} else if w.Type == BlipObject {
		C.blip_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
	}
}

func (w WorldObject) Dimension() int32 {
	var dimension int32

	if w.Type == PlayerObject {
		dimension = int32(C.player_get_dimension(w.Ptr))
	} else if w.Type == CheckpointObject {
		dimension = int32(C.checkpoint_get_dimension(w.Ptr))
	} else if w.Type == ColshapeObject {
		dimension = int32(C.col_shape_get_dimension(w.Ptr))
	} else if w.Type == VehicleObject {
		dimension = int32(C.vehicle_get_dimension(w.Ptr))
	} else if w.Type == BlipObject {
		dimension = int32(C.blip_get_dimension(w.Ptr))
	}

	return dimension
}

func (w WorldObject) SetDimension(dimension int32) {
	if w.Type == PlayerObject {
		C.player_set_dimension(w.Ptr, C.long(dimension))
	} else if w.Type == CheckpointObject {
		C.checkpoint_set_dimension(w.Ptr, C.long(dimension))
	} else if w.Type == ColshapeObject {
		C.col_shape_set_dimension(w.Ptr, C.long(dimension))
	} else if w.Type == VehicleObject {
		C.vehicle_set_dimension(w.Ptr, C.long(dimension))
	} else if w.Type == BlipObject {
		C.blip_set_dimension(w.Ptr, C.long(dimension))
	}
}
