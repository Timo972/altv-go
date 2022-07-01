package alt

import "C"
import "fmt"

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

func newCRGBA(rgba RGBA) C.struct_rgba {
	return C.struct_rgba{
		r: C.uchar(rgba.R),
		g: C.uchar(rgba.G),
		b: C.uchar(rgba.B),
		a: C.uchar(rgba.A),
	}
}

func (rgba RGBA) String() string {
	return fmt.Sprintf("RGBA{%d, %d, %d, %d}", rgba.R, rgba.G, rgba.B, rgba.A)
}
