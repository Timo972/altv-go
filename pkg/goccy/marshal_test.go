package goccy_test

import (
	"errors"
	"strconv"
	"sync"
	"testing"
	"unsafe"

	"github.com/goccy/go-reflect"
)

type token = byte

const (
	Int token = iota
	String
	BeginDict
	Field
	EndDict
	BeginArray
	EndArray
)

var (
	typeToEncoderMap sync.Map
	bufpool          = sync.Pool{
		New: func() interface{} {
			return &buffer{
				b: make([]byte, 0, 1024),
			}
		},
	}
)

type buffer struct {
	b []byte
}

type encoder func(*buffer, unsafe.Pointer) error

func Marshal(v interface{}) ([]byte, error) {

	// Technique 1.
	// Get type information and pointer from interface{} value without allocation.
	typ, ptr := reflect.TypeAndPtrOf(v)
	typeID := reflect.TypeID(v)

	// Technique 2.
	// Reuse the buffer once allocated using sync.Pool
	buf := bufpool.Get().(*buffer)
	buf.b = buf.b[:0]
	defer bufpool.Put(buf)

	// Technique 3.
	// builds a optimized path by typeID and caches it
	if enc, ok := typeToEncoderMap.Load(typeID); ok {
		if err := enc.(encoder)(buf, ptr); err != nil {
			return nil, err
		}

		// allocate a new buffer required length only
		b := make([]byte, len(buf.b))
		copy(b, buf.b)
		return b, nil
	}

	// First time,
	// builds a optimized path by type and caches it with typeID.
	enc, err := compile(typ)
	if err != nil {
		return nil, err
	}
	typeToEncoderMap.Store(typeID, enc)
	if err := enc(buf, ptr); err != nil {
		return nil, err
	}

	// allocate a new buffer required length only
	b := make([]byte, len(buf.b))
	copy(b, buf.b)
	return b, nil
}

func writeToken(buf *buffer, tok token) {
	buf.b = append(buf.b, '<')
	buf.b = strconv.AppendInt(buf.b, int64(tok), 10)
	buf.b = append(buf.b, '>')
}

func compile(typ reflect.Type) (encoder, error) {
	switch typ.Kind() {
	case reflect.Struct:
		return compileStruct(typ)
	case reflect.Int:
		return compileInt(typ)
	case reflect.String:
		return compileString(typ)
	}
	return nil, errors.New("unsupported type")
}

func compileStruct(typ reflect.Type) (encoder, error) {

	encoders := []encoder{}

	for i := 0; i < typ.NumField(); i++ {
		field := typ.Field(i)
		enc, err := compile(field.Type)
		if err != nil {
			return nil, err
		}
		offset := field.Offset
		encoders = append(encoders, func(buf *buffer, p unsafe.Pointer) error {
			writeToken(buf, Field)
			buf.b = append(buf.b, field.Name...)
			return enc(buf, unsafe.Pointer(uintptr(p)+offset))
		})
	}
	return func(buf *buffer, p unsafe.Pointer) error {
		writeToken(buf, BeginDict)
		for _, enc := range encoders {
			if err := enc(buf, p); err != nil {
				return err
			}
		}
		writeToken(buf, EndDict)
		return nil
	}, nil
}

func compileSlice(typ reflect.Type) (encoder, error) {
	return func(buf *buffer, p unsafe.Pointer) error {

		return nil
	}, nil
}

func compileInt(typ reflect.Type) (encoder, error) {
	return func(buf *buffer, p unsafe.Pointer) error {
		value := *(*int)(p)
		writeToken(buf, Int)
		buf.b = strconv.AppendInt(buf.b, int64(value), 10)
		return nil
	}, nil
}

func compileString(typ reflect.Type) (encoder, error) {
	return func(buf *buffer, p unsafe.Pointer) error {
		value := *(*string)(p)
		writeToken(buf, String)
		buf.b = append(buf.b, value...)
		return nil
	}, nil
}

func Benchmark_Marshal(b *testing.B) {
	b.ReportAllocs()
	for n := 0; n < b.N; n++ {
		bytes, err := Marshal(struct{ I int }{10})
		if err != nil {
			b.Fatal(err)
		}
		if string(bytes) != "<2><3>I<0>10<4>" {
			b.Fatalf("unexpected error: %s", string(bytes))
		}
		bytes2, err := Marshal(struct{ I, J int }{10, 20})
		if err != nil {
			b.Fatal(err)
		}
		if string(bytes2) != "<2><3>I<0>10<3>J<0>20<4>" {
			b.Fatalf("unexpected error: %s", string(bytes2))
		}
	}
}
