package altv

// #include "capi.h"
import "C"
import (
	"github.com/goccy/go-json"
	"github.com/timo972/altv-go/mvalue"
)

type RGBA struct {
	json.Marshaler
	R uint8 `json:"r"`
	G uint8 `json:"g"`
	B uint8 `json:"b"`
	A uint8 `json:"a"`
}

type rgbaData struct {
	mvalue.SpecialType
	R uint8 `json:"r"`
	G uint8 `json:"g"`
	B uint8 `json:"b"`
	A uint8 `json:"a"`
}

func (c RGBA) MarshalJSON() ([]byte, error) {
	return json.Marshal(rgbaData{
		SpecialType: mvalue.SpecialType{Type: mvalue.TypeRGBA},
		R:           c.R,
		G:           c.G,
		B:           c.B,
		A:           c.A,
	})
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
