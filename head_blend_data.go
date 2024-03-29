package altv

// #include "capi.h"
import "C"

type HeadBlendData struct {
	ShapeFirstID  uint32
	ShapeSecondID uint32
	ShapeThirdID  uint32
	SkinFirstID   uint32
	SkinSecondID  uint32
	SkinThirdID   uint32
	ShapeMix      float32
	SkinMix       float32
	ThirdMix      float32
}

func newHeadBlendData(cHBD C.struct_headBlendData) HeadBlendData {
	return HeadBlendData{
		ShapeFirstID:  uint32(cHBD.shapeFirstID),
		ShapeSecondID: uint32(cHBD.shapeSecondID),
		ShapeThirdID:  uint32(cHBD.shapeThirdID),
		SkinFirstID:   uint32(cHBD.skinFirstID),
		SkinSecondID:  uint32(cHBD.skinSecondID),
		SkinThirdID:   uint32(cHBD.skinThirdID),
		ShapeMix:      float32(cHBD.shapeMix),
		SkinMix:       float32(cHBD.skinMix),
		ThirdMix:      float32(cHBD.thirdMix),
	}
}
