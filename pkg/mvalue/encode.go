package mvalue

import (
	"runtime"
	"unsafe"
)

type IMValue interface{}

type MultiMValue interface {
	AddValue(v interface{}) error
}

type MValueDict struct {
	Keys   []string
	Values []IMValue
}

type MValueList struct {
	Values []IMValue
}

type MValue struct {
	Type string
	Val  unsafe.Pointer
}

type MValueWriter struct {
	root    IMValue
	i       int
	depth   int
	current IMValue
}

func (w *MValueWriter) BeginObject() {
	if w.depth < 0 {
		// root object
		w.root = MValueDict{
			Keys:   make([]string, 0),
			Values: make([]IMValue, 0),
		}

		w.current = w.root
	} else {
		// append object

		w.current = MValueDict{
			Keys:   make([]string, 0),
			Values: make([]IMValue, 0),
		}
	}

	w.depth++
}

func (w *MValueWriter) Name(key string) {
	// append key at depth & index
}

func (w *MValueWriter) Value(v interface{}) error {
	mv, err := NewMValue(v)
	if err != nil {
		return err
	}

	// FIXME: use interface to push a value and skip this type switch (because we are basically doing the same here)
	if d, ok := w.current.(MValueDict); ok {
		d.Values = append(d.Values, mv)
	} else if l, ok := w.current.(MValueList); ok {
		l.Values = append(l.Values, mv)
	}

	// append value at depth & index
	return nil
}

func (w *MValueWriter) pushParent() *IMValue {
	// get parent
	parent := new(IMValue)
	for i := 0; i <= w.depth; i++ {

	}

	return nil
}

func (w *MValueWriter) EndObject() {
	// push w.current to parent
	w.pushParent()

	w.depth--

	if w.depth < 0 {
		// writer finished
	}
}

func (w *MValueWriter) BeginArray() {
	if w.depth < 0 {
		w.root = MValueList{
			Values: make([]IMValue, 0),
		}
		w.current = w.root
	} else {
		// append mvalue list at depth & index
		w.current = MValueList{
			Values: make([]IMValue, 0),
		}
	}

	w.depth++
}

func (w *MValueWriter) EndArray() {
	// push w.current to parent

	// end mvalue list
	/*w.depth--

	if w.depth < 0 {
		// writer finished
	}*/

	// should be the same?
	w.EndObject()
}

type MValueReader struct {
}

type Serializable interface {
	Read(reader *MValueReader)
	OnWrite(writer *MValueWriter)
}

func NewWriter() *MValueWriter {
	return &MValueWriter{
		depth: -1,
		i:     -1,
	}
}

func NewMValue(v interface{}) (MValue, error) {
	if w, ok := v.(Serializable); ok {
		// use the writer
		wr := NewWriter()
		w.OnWrite(wr)
	}

	// call this for every value
	runtime.KeepAlive(v)
	// runtime.KeepAlive()
	// runtime.SetFinalizer() ?

	return MValue{}, nil
}

func (m *MValue) Release() {
	// free the pointer
	// m.Val
}
