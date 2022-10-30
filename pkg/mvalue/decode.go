package mvalue

import "C"

type MValueReader struct {
}

func Decode(data C.struct_goValue, out interface{}) error {
	return nil
}
