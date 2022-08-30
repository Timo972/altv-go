package mvalue

import (
	"errors"
	"fmt"
	"github.com/goccy/go-reflect"
	"github.com/timo972/altv-go/api/alt"
	"github.com/timo972/altv-go/internal/pb"
	"google.golang.org/protobuf/proto"
	"sync"
	"unsafe"
)

//type buffer struct {
//	data []byte
//}

type encoder func(*pb.MValue, unsafe.Pointer) error

var (
	typeToEncoderMap sync.Map
	//bufPool          = sync.Pool{
	//	New: func() interface{} {
	//		return &buffer{data: make([]byte, 0, 1024)}
	//	},
	//}
)

// func TakeBuffer() *buffer {
// 	return bufPool.Get().(*buffer)
// }
//
// func ReleaseBuffer(b *buffer) {
// 	bufPool.Put(b)
// }

func Marshal(v interface{}) ([]byte, error) {
	typ, ptr := reflect.TypeAndPtrOf(v)
	typeID := reflect.TypeID(typ)

	// buf := TakeBuffer()
	// buf.data = buf.data[:0]
	// defer ReleaseBuffer(buf)
	buf := new(pb.MValue)

	if enc, ok := typeToEncoderMap.Load(typeID); ok {
		if err := enc.(encoder)(buf, ptr); err != nil {
			return nil, err
		}

		// b := make([]byte, len(buf.data))
		// copy(b, buf.data)

		return proto.Marshal(buf)
	}

	enc, err := compile(typ)
	if err != nil {
		return nil, err
	}

	typeToEncoderMap.Store(typeID, enc)
	if err = enc(buf, ptr); err != nil {
		return nil, err
	}

	//b := make([]byte, len(buf.data))
	//copy(b, buf.data)

	return proto.Marshal(buf) //b, nil
}

func compile(typ reflect.Type) (encoder, error) {
	kind := typ.Kind()
	isPtr := kind == reflect.Ptr
	// orgTyp := typ
	if isPtr {
		typ = typ.Elem()
	}

	switch typ.Kind() {
	// case reflect.Ptr:
	case reflect.Struct:
		return compileStruct(typ)
	case reflect.Map:
	case reflect.String:
		return compileString(typ)
	case reflect.Bool:
		return compileBool(typ)
	case reflect.Int:
		return compileInt(typ)
	case reflect.Uint:
		return compileUInt(typ)
	case reflect.Float32:
		return compileFloat(typ)
	case reflect.Float64:
		return compileDouble(typ)
	case reflect.Array, reflect.Slice:
		return compileSlice(typ)
	case reflect.Func:
	}

	return nil, errors.New("unsupported type")
}

func compileStruct(typ reflect.Type) (encoder, error) {
	if name := typ.Name(); name == "Player" /*|| name == "Vehicle" || name == "Entity" || name == "ColShape" || name == "Checkpoint" || name == "VoiceChannel" || name == "Blip"*/ {
		return func(buf *pb.MValue, p unsafe.Pointer) error {
			// player := (*alt.Player)(p)
			buf.Value = &pb.MValue_BaseObjectValue{
				BaseObjectValue: &pb.BaseObject{
					// TODO:
					Type: proto.Uint32(0),
					Ptr:  proto.String(fmt.Sprintf("%v", "ptr")),
				},
			}
			return nil
		}, nil
	} else if name == "RGBA" {
		return func(buf *pb.MValue, p unsafe.Pointer) error {
			c := (*alt.RGBA)(p)
			buf.Value = &pb.MValue_RgbaValue{
				RgbaValue: &pb.RGBA{
					R: proto.Uint32(uint32(c.R)),
					G: proto.Uint32(uint32(c.G)),
					B: proto.Uint32(uint32(c.B)),
					A: proto.Uint32(uint32(c.A)),
				},
			}

			return nil
		}, nil
	} else if name == "Vector3" {
		return func(buf *pb.MValue, p unsafe.Pointer) error {
			v := (*alt.Vector3)(p)
			buf.Value = &pb.MValue_Vector3Value{
				Vector3Value: &pb.Vector3{
					X: proto.Float32(v.X),
					Y: proto.Float32(v.Y),
					Z: proto.Float32(v.Z),
				},
			}
			return nil
		}, nil
	} else if name == "Vector2" {
		return func(buf *pb.MValue, p unsafe.Pointer) error {
			v := (*alt.Vector2)(p)
			buf.Value = &pb.MValue_Vector2Value{
				Vector2Value: &pb.Vector2{
					X: proto.Float32(v.X),
					Y: proto.Float32(v.Y),
				},
			}
			return nil
		}, nil
	} else {
		encoders := map[string]encoder{}

		for i := 0; i < typ.NumField(); i++ {
			field := typ.Field(i)
			enc, err := compile(field.Type)
			if err != nil {
				return nil, err
			}

			offset := field.Offset
			encoders[field.Name] = func(buf *pb.MValue, p unsafe.Pointer) error {
				return enc(buf, unsafe.Pointer(uintptr(p)+offset))
			}
		}

		return func(buf *pb.MValue, p unsafe.Pointer) error {
			buf.Dict = make(map[string]*pb.MValue)
			for key, enc := range encoders {
				buf.Dict[key] = &pb.MValue{}
				if err := enc(buf.Dict[key], p); err != nil {
					return err
				}
			}
			return nil
		}, nil
	}
}

func compileSlice(typ reflect.Type) (encoder, error) {
	elType := typ.Elem()
	if elType.Kind() == reflect.Interface {
		return nil, errors.New("[]interface{} not supported")
	}

	encoders := []encoder{}

	enc, err := compile(elType)
	if err != nil {
		return nil, err
	}
	for i := 0; i < typ.Len(); i++ {
		// FIXME: offset calculation may be incorrect
		offset := elType.Size() * uintptr(i)
		encoders = append(encoders, func(buf *pb.MValue, p unsafe.Pointer) error {
			return enc(buf, unsafe.Pointer(uintptr(p)+offset))
			// return nil
		})
	}

	return func(buf *pb.MValue, p unsafe.Pointer) error {
		buf.List = make([]*pb.MValue, len(encoders))
		for i, enc := range encoders {
			buf.List[i] = &pb.MValue{}
			if err = enc(buf.List[i], p); err != nil {
				return err
			}
		}
		return nil
	}, nil
}

func compileInt(typ reflect.Type) (encoder, error) {
	return func(buf *pb.MValue, p unsafe.Pointer) error {
		v := *(*int)(p)
		buf.Value = &pb.MValue_IntValue{IntValue: int64(v)}
		return nil
	}, nil
}

func compileUInt(reflect.Type) (encoder, error) {
	return func(buf *pb.MValue, p unsafe.Pointer) error {
		v := *(*uint)(p)
		buf.Value = &pb.MValue_UintValue{UintValue: uint64(v)}
		return nil
	}, nil
}

func compileFloat(reflect.Type) (encoder, error) {
	return func(buf *pb.MValue, p unsafe.Pointer) error {
		v := *(*float32)(p)
		buf.Value = &pb.MValue_DoubleValue{DoubleValue: float64(v)}
		return nil
	}, nil
}

func compileDouble(reflect.Type) (encoder, error) {
	return func(buf *pb.MValue, p unsafe.Pointer) error {
		v := *(*float64)(p)
		buf.Value = &pb.MValue_DoubleValue{DoubleValue: v}
		return nil
	}, nil
}

func compileBool(reflect.Type) (encoder, error) {
	return func(buf *pb.MValue, p unsafe.Pointer) error {
		v := *(*bool)(p)
		buf.Value = &pb.MValue_BoolValue{BoolValue: v}
		return nil
	}, nil
}

func compileString(reflect.Type) (encoder, error) {
	return func(buf *pb.MValue, p unsafe.Pointer) error {
		v := *(*string)(p)
		buf.Value = &pb.MValue_StringValue{StringValue: v}
		return nil
	}, nil
}
