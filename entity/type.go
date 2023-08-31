package entity

type BaseObjectType = uint8

const (
	TypePlayer BaseObjectType = iota
	TypeVehicle
	TypePed
	TypeNetworkObject
	TypeBlip
	TypeWebView
	TypeVoiceChannel
	TypeColShape
	TypeCheckpoint
	TypeWebSocketClient
	TypeHttpClient
	TypeAudio
	TypeRMLElement
	TypeRMLDocument
	TypeLocalPlayer
	TypeObject
	TypeVirtualEntity
	TypeVirtualEntityGroup
	TypeMarker
	TypeTextLabel
	TypeLocalPed
	TypeLocalVehicle
	TypeAudioFilter
	TypeSize
)
