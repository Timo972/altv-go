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
import "fmt"

type Weapon struct {
	Hash       uint32
	TintIndex  uint8
	Components []uint32
}

func newWeapon(w C.struct_weapon) Weapon {
	cComps, size := convertArray[C.uint](w.components)
	comps := make([]uint32, size)

	for i, comp := range cComps {
		comps[i] = uint32(comp)
	}

	return Weapon{
		Hash:       uint32(w.hash),
		TintIndex:  uint8(w.tintIndex),
		Components: comps,
	}
}

func (w Weapon) String() string {
	return fmt.Sprintf("Weapon{Hash: %d, TintIndex: %d, Components: %v}", w.Hash, w.TintIndex, w.Components)
}
