package mvalue

import (
	"github.com/goccy/go-json"
)

type MValueType uint8

const (
	TypeNone MValueType = iota
	TypeNil
	TypeBool
	TypeInt
	TypeUInt
	TypeDouble
	TypeString
	TypeList
	TypeDict
	TypeBaseObject
	TypeFunction
	TypeVector3
	TypeRGBA
	TypeByteArray
	TypeVector2
)

type SpecialType struct {
	Type MValueType `json:"$type"`
}

func Marshal(v any) ([]byte, error) {
	return json.Marshal(v)
}
