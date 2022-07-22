package alt

/*
#cgo windows CFLAGS: -I../../c-api/lib
#cgo windows LDFLAGS: -L../../c-api/lib/win32 -lcapi

#cgo linux CFLAGS: -I../../c-api/lib
#cgo linux LDFLAGS: -g -L../../c-api/lib/linux -lcapi  -ldl

#ifndef GOLANG_APP
#define GOLANG_APP

#include <stdlib.h>
#include "capi.h"

#endif
*/
import "C"
import (
	"fmt"
	"github.com/timo972/altv-go/internal/pb"
	"math"
)

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

func (v Vector3) String() string {
	return fmt.Sprintf("Vector3{%f, %f, %f}", v.X, v.Y, v.Z)
}

func (v Vector2) String() string {
	return fmt.Sprintf("Vector2{%f, %f}", v.X, v.Y)
}

func (v Vector3) Add(v2 Vector3) Vector3 {
	return Vector3{
		X: v.X + v2.X,
		Y: v.Y + v2.Y,
		Z: v.Z + v2.Z,
	}
}

func (v Vector3) Sub(v2 Vector3) Vector3 {
	return Vector3{
		X: v.X - v2.X,
		Y: v.Y - v2.Y,
		Z: v.Z - v2.Z,
	}
}

func (v Vector3) Mul(v2 Vector3) Vector3 {
	return Vector3{
		X: v.X * v2.X,
		Y: v.Y * v2.Y,
		Z: v.Z * v2.Z,
	}
}

func (v Vector3) Div(v2 Vector3) Vector3 {
	return Vector3{
		X: v.X / v2.X,
		Y: v.Y / v2.Y,
		Z: v.Z / v2.Z,
	}
}

func (v Vector3) Dot(v2 Vector3) float32 {
	return v.X*v2.X + v.Y*v2.Y + v.Z*v2.Z
}

func (v Vector3) Cross(v2 Vector3) Vector3 {
	return Vector3{
		X: v.Y*v2.Z - v.Z*v2.Y,
		Y: v.Z*v2.X - v.X*v2.Z,
		Z: v.X*v2.Y - v.Y*v2.X,
	}
}

func (v Vector3) Negative() Vector3 {
	return Vector3{
		X: -v.X,
		Y: -v.Y,
		Z: -v.Z,
	}
}

func (v Vector3) Length() float64 {
	return math.Sqrt(float64(v.X*v.X + v.Y*v.Y + v.Z*v.Z))
}

func (v Vector3) Normalize() Vector3 {
	l := float32(v.Length())
	return Vector3{
		X: v.X / l,
		Y: v.Y / l,
		Z: v.Z / l,
	}
}

func (v Vector3) DistanceTo(v2 Vector3) float64 {
	return math.Sqrt(v.DistanceToSquared(v2))
}

func (v Vector3) DistanceToSquared(v2 Vector3) float64 {
	x := v.X - v2.X
	y := v.Y - v2.Y
	z := v.Z - v2.Z
	return float64(x*x + y*y + z*z)
}

func (v Vector3) AngleTo(v2 Vector3) (float64, bool) {
	posALength := math.Hypot(float64(v.X), float64(v.Y))
	posBLength := math.Hypot(float64(v2.X), float64(v2.Y))

	if posALength == 0 || posBLength == 0 {
		return 0, false
	}

	return math.Acos((float64(v.X*v2.X + v.Y*v2.Y)) / (posALength * posBLength)), true
}

func (v Vector3) AngleToDegrees(v2 Vector3) (float64, bool) {
	angle, ok := v.AngleTo(v2)
	if !ok {
		return 0, false
	}

	return angle * (180 / math.Pi), true
}

func (v Vector3) ToDegrees() Vector3 {
	return Vector3{
		X: v.X * (180 / math.Pi),
		Y: v.Y * (180 / math.Pi),
		Z: v.Z * (180 / math.Pi),
	}
}

func (v Vector3) ToRadians() Vector3 {
	return Vector3{
		X: (v.X * math.Pi) / 180,
		Y: (v.Y * math.Pi) / 180,
		Z: (v.Z * math.Pi) / 180,
	}
}

func (v Vector3) IsInRange(v2 Vector3, r float64) bool {
	x := math.Abs(float64(v.X - v2.X))
	y := math.Abs(float64(v.Y - v2.Y))
	z := math.Abs(float64(v.Z - v2.Z))

	return x <= r && y <= r && z <= r && x*x+y*y+z*z <= r*r
}

func (v Vector3) Lerp(v2 Vector3, ratio float32) Vector3 {
	return Vector3{
		X: v.X + (v2.X-v.X)*ratio,
		Y: v.Y + (v2.Y-v.Y)*ratio,
		Z: v.Z + (v2.Z-v.Z)*ratio,
	}
}

func (v Vector3) pb() *pb.Vector3 {
	return &pb.Vector3{
		X: &v.X,
		Y: &v.Y,
		Z: &v.Z,
	}
}
