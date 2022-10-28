package alt

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"
import (
	"fmt"
	"github.com/timo972/altv-go/internal/module"
)

type ColShape struct {
	WorldObject
}

func CreateColShapeCircle(x float32, y float32, z float32, radius float32) IColShape {
	ptr := C.core_create_col_shape_circle(C.float(x), C.float(y), C.float(z), C.float(radius))
	return getColShape(ptr)
}
func CreateColShapeCube(x1 float32, y1 float32, z1 float32, x2 float32, y2 float32, z2 float32) IColShape {
	ptr := C.core_create_col_shape_cube(C.float(x1), C.float(y1), C.float(z1), C.float(x2), C.float(y2), C.float(z2))
	return getColShape(ptr)
}
func CreateColShapeCylinder(x float32, y float32, z float32, radius float32, height float32) IColShape {
	ptr := C.core_create_col_shape_cylinder(C.float(x), C.float(y), C.float(z), C.float(radius), C.float(height))
	return getColShape(ptr)
}
func CreateColShapeRectangle(x1 float32, y1 float32, x2 float32, y2 float32, z float32) IColShape {
	ptr := C.core_create_col_shape_rectangle(C.float(x1), C.float(y1), C.float(x2), C.float(y2), C.float(z))
	return getColShape(ptr)
}
func CreateColShapeSphere(x float32, y float32, z float32, radius float32) IColShape {
	ptr := C.core_create_col_shape_sphere(C.float(x), C.float(y), C.float(z), C.float(radius))
	return getColShape(ptr)
}

func CreateColShapePolygon(minZ float32, maxZ float32, points []Vector2) IColShape {
	size := len(points)
	cPoints := C.malloc(C.size_t(size) * C.size_t(C.sizeof_Vector2))
	v2Array := (*[1 << 30]C.struct_vector2)(cPoints)
	defer C.free(cPoints)

	for i := 0; i < size; i++ {
		v2Array[i] = C.struct_vector2{
			x: C.float(points[i].X),
			y: C.float(points[i].Y),
		}
	}

	ptr := C.core_create_col_shape_polygon(C.float(minZ), C.float(maxZ), C.struct_array{
		size:  C.ulonglong(size),
		array: cPoints,
	})

	return getColShape(ptr)
}

func (c ColShape) String() string {
	return fmt.Sprintf("ColShape{}")
}

func (c ColShape) IsPlayersOnly() bool {
	if c.Type() == ColshapeObject {
		return int(C.col_shape_is_players_only(c.ptr)) == 1
	} else if c.Type() == CheckpointObject {
		return int(C.checkpoint_is_players_only(c.ptr)) == 1
	}
	return false
}

func (c ColShape) SetPlayersOnly(state bool) {
	if c.Type() == ColshapeObject {
		C.col_shape_set_players_only(c.ptr, C.int(module.Bool2int(state)))
	} else if c.Type() == CheckpointObject {
		C.checkpoint_set_players_only(c.ptr, C.int(module.Bool2int(state)))
	}
}

func (c ColShape) IsPointIn(pos Vector3) bool {
	if c.Type() == ColshapeObject {
		return int(C.col_shape_is_point_in(c.ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))) == 1
	} else if c.Type() == CheckpointObject {
		return int(C.checkpoint_is_point_in(c.ptr, C.float(pos.X), C.float(pos.Y), C.float(pos.Z))) == 1
	}
	return false
}

func (c ColShape) IsEntityIn(entity IEntity) bool {
	if c.Type() == ColshapeObject {
		return int(C.col_shape_is_entity_in(c.ptr, newCEntity(entity))) == 1
	} else if c.Type() == CheckpointObject {
		return int(C.checkpoint_is_entity_in(c.ptr, newCEntity(entity))) == 1
	}
	return false
}

func (c ColShape) ColShapeType() int8 {
	if c.Type() == ColshapeObject {
		return int8(C.col_shape_get_col_shape_type(c.ptr))
	} else if c.Type() == CheckpointObject {
		return int8(C.checkpoint_get_col_shape_type(c.ptr))
	}
	return 0
}

func (c ColShape) IsEntityIdIn(id uint16) bool {
	var x uint8
	if c.Type() == ColshapeObject {
		x = uint8(C.col_shape_is_entity_id_in(c.ptr, C.ushort(id)))
	} else if c.Type() == CheckpointObject {
		x = uint8(C.checkpoint_is_entity_id_in(c.ptr, C.ushort(id)))
	}

	return x == 1
}
