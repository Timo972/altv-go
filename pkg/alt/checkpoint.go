package alt

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"
import (
	"fmt"
)

type Checkpoint struct {
	ColShape
}

// CreateCheckpoint Create a checkpoint
// ! This method is unfinished in alt:V use at your own risk !
func CreateCheckpoint(checkpointType uint8, x float32, y float32, z float32, radius float32, height float32, color RGBA) ICheckpoint {
	e := C.core_create_checkpoint(C.uchar(checkpointType), C.float(x), C.float(y), C.float(z), C.float(radius), C.float(height), C.uchar(color.R), C.uchar(color.G), C.uchar(color.B), C.uchar(color.A))
	return getCheckpoint(e)
}

func (c Checkpoint) String() string {
	return fmt.Sprintf("Checkpoint{}")
}

func (c Checkpoint) CheckpointType() uint8 {
	return uint8(C.checkpoint_get_checkpoint_type(c.ptr))
}

func (c Checkpoint) Height() float32 {
	return float32(C.checkpoint_get_height(c.ptr))
}

func (c Checkpoint) Radius() float32 {
	return float32(C.checkpoint_get_radius(c.ptr))
}

func (c Checkpoint) Color() RGBA {
	cRGBA := C.checkpoint_get_color(c.ptr)
	return RGBA{R: uint8(cRGBA.r), G: uint8(cRGBA.g), B: uint8(cRGBA.b), A: uint8(cRGBA.a)}
}

func (c Checkpoint) NextPosition() Vector3 {
	cPos := C.checkpoint_get_next_position(c.ptr)
	return Vector3{X: float32(cPos.x), Y: float32(cPos.y), Z: float32(cPos.z)}
}

func (c Checkpoint) SetCheckpointType(checkpointType uint8) {
	C.checkpoint_set_checkpoint_type(c.ptr, C.uchar(checkpointType))
}

func (c Checkpoint) SetHeight(height float32) {
	C.checkpoint_set_height(c.ptr, C.float(height))
}

func (c Checkpoint) SetRadius(radius float32) {
	C.checkpoint_set_radius(c.ptr, C.float(radius))
}

func (c Checkpoint) SetColor(color RGBA) {
	C.checkpoint_set_color(c.ptr, C.uchar(color.R), C.uchar(color.G), C.uchar(color.B), C.uchar(color.A))
}

func (c Checkpoint) SetNextPosition(pos Vector3) {
	C.checkpoint_set_next_position(c.ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
}
