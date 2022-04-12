package alt

import "fmt"

type Cloth struct {
	DrawableId uint16
	TextureId  uint8
	PaletteId  uint8
}

type DlcCloth struct {
	Dlc        uint32
	DrawableId uint16
	TextureId  uint8
	PaletteId  uint8
}

func (c Cloth) String() string {
	return fmt.Sprintf("Cloth{DrawableId: %d, TextureId: %d, PaletteId: %d}", c.DrawableId, c.TextureId, c.PaletteId)
}

func (c DlcCloth) String() string {
	return fmt.Sprintf("DlcCloth{Dlc: %d, DrawableId: %d, TextureId: %d, PaletteId: %d}", c.Dlc, c.DrawableId, c.TextureId, c.PaletteId)
}
