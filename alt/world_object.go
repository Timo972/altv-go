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

func (w WorldObject) Position() *Position {
	var pos *Position

	if w.Type == PlayerObject {
		cPos := C.player_get_position(w.Ptr)
		pos = &Position{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
	}

	return pos
}

func (w WorldObject) SetPosition(pos Position) {
	if w.Type == PlayerObject {
		C.player_set_position(w.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
	}
}

func (w WorldObject) Dimension() int32 {
	var dimension int32

	if w.Type == PlayerObject {
		dimension = int32(C.player_get_dimension(w.Ptr))
	}

	return dimension
}

func (w WorldObject) SetDimension(dimension int32) {
	if w.Type == PlayerObject {
		C.player_set_dimension(w.Ptr, C.long(dimension))
	}
}
