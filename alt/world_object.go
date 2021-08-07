package alt

type WorldObject struct {
	BaseObject
}

type World interface {
	GetPosition()
	SetPosition()
	GetDimension() int32
	SetDimension()
}

func (w WorldObject) GetPosition() {
	panic("implement me")
}

func (w WorldObject) SetPosition() {
	panic("implement me")
}

func (w WorldObject) GetDimension() int32 {
	panic("implement me")
}

func (w WorldObject) SetDimension() {
	panic("implement me")
}
