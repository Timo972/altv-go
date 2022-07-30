package alt

import "unsafe"

type BaseObjectFactory struct {
}

func (b *BaseObjectFactory) Create(ptr unsafe.Pointer, t BaseObjectType) *BaseObject {
	if ptr == nil {
		return nil
	}

	o := &BaseObject{
		ptr:  ptr,
		Type: t,
	}
	o.ClearData()

	return o
}
