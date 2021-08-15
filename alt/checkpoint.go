package alt

// #include <stdlib.h>
// #include "Module.h"
import "C"

type Checkpoint struct {
	ColShape
}

// Create a checkpoint
// ! This method is unfinished in alt:V use at your own risk !
func CreateCheckpoint(checkpointType uint8, x float32, y float32, z float32, radius float32, height float32, color RGBA) *Checkpoint {
	ptr := C.core_create_checkpoint(C.ushort(checkpointType), C.float(x), C.float(y), C.float(z), C.float(radius), C.float(height), C.ushort(color.R), C.ushort(color.G), C.ushort(color.B), C.ushort(color.A))
	checkpoint := &Checkpoint{}
	checkpoint.Ptr = ptr
	checkpoint.Type = CheckpointObject
	return checkpoint
}

func (c Checkpoint) CheckpointType() uint8 {
	return uint8(C.checkpoint_get_checkpoint_type(c.Ptr))
}

func (c Checkpoint) Height() float32 {
	return float32(C.checkpoint_get_height(c.Ptr))
}

func (c Checkpoint) Radius() float32 {
	return float32(C.checkpoint_get_radius(c.Ptr))
}

func (c Checkpoint) Color() RGBA {
	cRGBA := C.checkpoint_get_color(c.Ptr)
	return RGBA{R:uint8(cRGBA.r),G:uint8(cRGBA.g),B:uint8(cRGBA.b),A:uint8(cRGBA.a)}
}

func (c Checkpoint) NextPosition() Position {
	cPos := C.checkpoint_get_next_position(c.Ptr)
	return Position{X:float32(cPos.x),Y:float32(cPos.y),Z:float32(cPos.z)}
}

func (c Checkpoint) SetCheckpointType(checkpointType uint8) {
	C.checkpoint_set_checkpoint_type(c.Ptr, C.uchar(checkpointType))
}

func (c Checkpoint) SetHeight(height float32) {
	C.checkpoint_set_height(c.Ptr, C.float(height))
}

func (c Checkpoint) SetRadius(radius float32) {
	C.checkpoint_set_radius(c.Ptr, C.float(radius))
}

func (c Checkpoint) SetColor(color RGBA) {
	C.checkpoint_set_color(c.Ptr, C.uchar(color.R), C.uchar(color.G), C.uchar(color.B), C.uchar(color.A))
}

func (c Checkpoint) SetNextPosition(pos Position) {
	C.checkpoint_set_next_position(c.Ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))
}