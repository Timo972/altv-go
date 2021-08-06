package alt

type BaseObjectType = uint8

const (
	PlayerObject BaseObjectType = iota
	VehicleObject
	BlipObject
	WebviewObject
	VoiceChannelObject
	ColshapeObject
	CheckpointObject
	WebSocketClientObject
	HttpClientObject
	AudioObject
	LocalPlayerObject
)

type BaseObject struct { }

type Base interface {
	GetType() BaseObjectType
	HasMetaData(key string) bool
	GetMetaData(key string)
	SetMetaData(key string, value interface{})
	DeleteMetaData(key string)
}

func (b BaseObject) GetType() BaseObjectType {
	panic("implement me")
}

func (b BaseObject) HasMetaData(key string) bool {
	panic("implement me")
}

func (b BaseObject) GetMetaData(key string) {
	panic("implement me")
}

func (b BaseObject) SetMetaData(key string, value interface{}) {
	panic("implement me")
}

func (b BaseObject) DeleteMetaData(key string) {
	panic("implement me")
}
