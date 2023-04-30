package altv

// #include "capi.h"
import "C"

type HeadOverlay struct {
	Index            uint8
	Opacity          float32
	ColorType        uint8
	ColorIndex       uint8
	SecondColorIndex uint8
}

func newHeadOverlay(cHeadOverlay C.struct_headOverlay) HeadOverlay {
	return HeadOverlay{
		Index:            uint8(cHeadOverlay.index),
		Opacity:          float32(cHeadOverlay.opacity),
		ColorType:        uint8(cHeadOverlay.colorType),
		ColorIndex:       uint8(cHeadOverlay.colorIndex),
		SecondColorIndex: uint8(cHeadOverlay.secondColorIndex),
	}
}
