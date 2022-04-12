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

func newVector3(v C.struct_pos) Vector3 {
	return Vector3{
		X: float32(v.x),
		Y: float32(v.y),
		Z: float32(v.z),
	}
}
