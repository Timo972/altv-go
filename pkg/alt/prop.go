package alt

import "fmt"

type Prop struct {
	DrawableId uint16
	TextureId  uint8
}

type DlcProp struct {
	Dlc        uint32
	DrawableId uint16
	TextureId  uint8
}

func (p *Prop) String() string {
	return fmt.Sprintf("Prop{DrawableId: %d, TextureId: %d}", p.DrawableId, p.TextureId)
}

func (p *DlcProp) String() string {
	return fmt.Sprintf("DlcProp{Dlc: %d, DrawableId: %d, TextureId: %d}", p.Dlc, p.DrawableId, p.TextureId)
}
