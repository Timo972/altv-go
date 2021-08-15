package alt

// #include "Module.h"
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
	Position() *Position
	SetPosition()
	Dimension() int32
	SetDimension()
}

func (w WorldObject) Position() Position {
	var pos Position

	if w.Type == PlayerObject {
		cPos := C.player_get_position(w.Ptr)
		pos = Position{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
	} else if w.Type == CheckpointObject {
		cPos := C.checkpoint_get_position(w.Ptr)
		pos = Position{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
	} else if w.Type == ColshapeObject {
		cPos := C.col_shape_get_position(w.Ptr)
		pos = Position{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
	} else if w.Type == VehicleObject {
		cPos := C.vehicle_get_position(w.Ptr)
		pos = Position{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
	}

	return pos
}

func (w WorldObject) SetPosition(pos Position) {
	if w.Type == PlayerObject {
		C.player_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
	} else if w.Type == CheckpointObject {
		C.checkpoint_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
	} else if w.Type == ColshapeObject {
		C.col_shape_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
	} else if w.Type == VehicleObject {
		C.vehicle_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
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
	}
}
