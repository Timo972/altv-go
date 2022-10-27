package mvalue

import "unsafe"

type Serializable interface {
	OnRead(reader *MValueReader)
	OnWrite(writer *MValueWriter)
}

type MultiMValue interface {
	AddValue(v *MValue) error
}

type MValueDict struct {
	MValueList
	Keys []string
}

func newMValueDict() *MValue {
	return &MValue{
		Type: "dict",
		Dict: &MValueDict{
			Keys: make([]string, 0),
			MValueList: MValueList{
				Values: make([]*MValue, 0),
			},
		},
	}
}

type MValueList struct {
	Values []*MValue
}

func newMValueList() *MValue {
	return &MValue{
		Type: "list",
		List: &MValueList{
			Values: make([]*MValue, 0),
		},
	}
}

type MValue struct {
	Type string
	Val  unsafe.Pointer

	Dict       *MValueDict
	List       *MValueList
	ByteLength int
}
