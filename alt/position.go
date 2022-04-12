package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
import "C"

type Vector3 struct {
	X float32
	Y float32
	Z float32
}

type Vector2 struct {
	X float32
	Y float32
}

func newVector2(v C.struct_vector2) Vector2 {
	return Vector2{
		X: float32(v.x),
		Y: float32(v.y),
	}
}

func newCVector2(v Vector2) C.struct_vector2 {
	return C.struct_vector2{
		x: C.float(v.X),
		y: C.float(v.Y),
	}
}

func newVector3(v C.struct_pos) Vector3 {
	return Vector3{
		X: float32(v.x),
		Y: float32(v.y),
		Z: float32(v.z),
	}
}

func newCPosition(v Vector3) C.struct_pos {
	return C.struct_pos{
		x: C.float(v.X),
		y: C.float(v.Y),
		z: C.float(v.Z),
	}
}

func newCRotation(v Vector3) C.struct_rot {
	return C.struct_rot{
		roll:  C.float(v.X),
		pitch: C.float(v.Y),
		yaw:   C.float(v.Z),
	}
}
