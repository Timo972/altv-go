package alt

import "C"
import "fmt"

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

func (h HeadOverlay) String() string {
	return fmt.Sprintf("HeadOverlay{Index: %d, Opacity: %f, ColorType: %d, ColorIndex: %d, SecondColorIndex: %d}", h.Index, h.Opacity, h.ColorType, h.ColorIndex, h.SecondColorIndex)
}
