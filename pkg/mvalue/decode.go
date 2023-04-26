package mvalue

import "C"

type Reader interface {
}

func Decode(data C.struct_goValue, out interface{}) error {
	return nil
}
