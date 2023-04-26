package mvalue

import "C"
import (
	"errors"
	"reflect"
	"runtime"
	"unsafe"

	"github.com/timo972/altv-go/internal/module"
)

// FIXME: use compile pattern like goccy/go-json to improve conversion time for reoccurring objects & use C.struct_goValue instead of this weird shit

type Writer interface {
	BeginObject()
	EndObject()
	Name(name string)
	Value(value any)
	BeginArray()
	EndArray()
}

type Writable interface {
	ToMValue(writer Writer)
}

type writer struct {
	root    *MValue
	depth   int
	current []*MValue
}

func (w *writer) BeginObject() {
	if w.depth < 0 {
		// root object
		w.root = newMValueDict()

		w.current[0] = w.root
	} else {
		// prepend object
		w.current = append(w.current, newMValueDict())
	}

	w.depth++
}

func (w *writer) Name(key string) error {
	// append key at depth & index
	curr := w.current[len(w.current)-1]
	if curr == nil {
		return errors.New("")
	}
	if curr.Type != "dict" {
		return errors.New("")
	}

	curr.Dict.Keys = append(curr.Dict.Keys, key)

	return nil
}

func (w *writer) Value(v interface{}) error {
	curr := w.current[len(w.current)-1]
	if curr == nil {
		return errors.New("")
	}

	mv, err := NewMValue(v)
	if err != nil {
		return err
	}

	// FIXME: use interface to push a value and skip this type switch (because we are basically doing the same here)

	if curr.Type == "dict" {
		curr.Dict.Values = append(curr.Dict.Values, mv)
	} else if curr.Type == "list" {
		curr.List.Values = append(curr.List.Values, mv)
	} else {
		return errors.New("no parent for value")
	}

	return nil
}

func (w *writer) pushParent() {
	// get parent
	parent := w.current[w.depth]
	if parent == nil {
		return
	}

	curr := w.current[len(w.current)-1]

	if parent.Type == "dict" {
		parent.Dict.Values = append(parent.Dict.Values, curr)
	} else if parent.Type == "list" {
		parent.List.Values = append(parent.List.Values, curr)
	}
}

func (w *writer) EndObject() {
	// push w.current to parent
	w.pushParent()

	// remove finished object from current stack
	w.current = w.current[:len(w.current)-1]

	w.depth--

	if w.depth < 0 {
		// writer finished
	}
}

func (w *writer) BeginArray() {
	if w.depth < 0 {
		w.root = newMValueList()
		w.current[0] = w.root
	} else {
		// prepend mvalue list at depth & index
		w.current = append(w.current, newMValueList())
	}

	w.depth++
}

func (w *writer) EndArray() {
	// push w.current to parent

	// end mvalue list
	/*w.depth--

	if w.depth < 0 {
		// writer finished
	}*/

	// should be the same?
	w.EndObject()
}

func (wr *writer) Write(mv *MValue) {
	mv = wr.root
}

func NewWriter() *writer {
	return &writer{
		depth:   -1,
		current: make([]*MValue, 1),
	}
}

type SerializableValue interface {
	int | uint | string | float32 | float64 | bool | []byte
}

func Marshal[Value SerializableValue](value Value) ([]byte, error) {
	typ := reflect.TypeOf(value)
	k := typ.Kind()

	switch k {
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		return nil, nil
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		return nil, nil
	case reflect.String:
		return nil, nil
	case reflect.Float32, reflect.Float64:
		return nil, nil
	case reflect.Bool:
		return nil, nil
	case reflect.Slice:
		return nil, nil
	case reflect.Struct:
		return nil, nil
	case reflect.Ptr:
		return nil, nil

	}

	return nil, nil
}

func NewMValue(v any) (*MValue, error) {
	mv := &MValue{}
	switch t := v.(type) {
	case int:
		mv.Type = "int"
		mv.Val = unsafe.Pointer(&t)
	case uint:
		mv.Type = "uint"
		mv.Val = unsafe.Pointer(&t)
	case string:
		mv.Type = "string"
		mv.Val = unsafe.Pointer(C.CString(t))
	case bool:
		mv.Type = "bool"
		b := module.Bool2int(t)
		mv.Val = unsafe.Pointer(&b)
	case []byte:
		mv.Type = "byteArray"
		mv.Val = unsafe.Pointer(C.CBytes(t))
		mv.ByteLength = len(t)
	case float64:
		mv.Type = "double"
		mv.Val = unsafe.Pointer(&t)
	case nil:
		mv.Type = "nil"
	case Serializable:
		wr := NewWriter()
		t.OnWrite(wr)
		wr.Write(mv)
		// TODO: list, baseobject, function, vector2, vector3, rgba
	}

	// call this for every value
	runtime.KeepAlive(v)
	// runtime.KeepAlive()
	// runtime.SetFinalizer() ?

	return mv, nil
}

func (m *MValue) Release() {
	// free the pointer
	// m.Val
}

func (m *MValue) testValue() any {
	var v any

	switch m.Type {
	case "int":
		v = *(*int)(m.Val)
	case "uint":
		v = *(*uint)(m.Val)
	case "string":
		v = C.GoString((*C.char)(m.Val))
	case "bool":
		v = *(*int)(m.Val) == 1
	case "byteArray":
		v = C.GoBytes(m.Val, C.int(m.ByteLength))
	case "double":
		v = *(*float64)(m.Val)
	case "dict":
	case "list":
		x := make([]any, 0)
		for _, mv := range m.List.Values {
			x = append(x, mv.testValue())
		}
		v = x
	}

	return v
}
