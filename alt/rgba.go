package alt

import "C"

type RGBA struct {
	R uint8
	G uint8
	B uint8
	A uint8
}

func newRGBA(cRGBA C.struct_rgba) RGBA {
	return RGBA{
		R: uint8(cRGBA.r),
		G: uint8(cRGBA.g),
		B: uint8(cRGBA.b),
		A: uint8(cRGBA.a),
	}
}
