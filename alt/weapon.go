package alt

// #cgo CFLAGS: -I../c-api/build/Release
// #cgo LDFLAGS: -L../c-api/build/Release -lcapi
// #include <stdlib.h>
// #include "../c-api/capi.h"
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
