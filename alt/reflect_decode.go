package alt

import "C"
import (
	"fmt"
	"reflect"

	"github.com/timo972/altv-go-pkg/pb"
	"google.golang.org/protobuf/proto"
)

type ReflectDecoder struct {
	Buffer []byte
	MValue *pb.MValue
}

func newReflectDecoder(data []byte) *ReflectDecoder {
	return &ReflectDecoder{
		Buffer: data,
	}
}

func decodeReflect(arr C.struct_array) (reflect.Value, error) {
	bytes := C.GoBytes(arr.array, C.int(arr.size))
	d := newReflectDecoder(bytes)
	return d.Decode()
}

func (d *ReflectDecoder) Decode() (reflect.Value, error) {
	if d.MValue == nil && len(d.Buffer) == 0 {
		return reflect.ValueOf(nil), nil
	}

	err := d.unmarshalBytes()
	if err != nil {
		return reflect.Value{}, err
	}

	return d.decode()
}

func (d *ReflectDecoder) unmarshalBytes() error {
	if d.MValue == nil && len(d.Buffer) > 0 {
		d.MValue = &pb.MValue{}
		return proto.Unmarshal(d.Buffer, d.MValue)
	}

	return nil
}

func (d *ReflectDecoder) decode() (reflect.Value, error) {
	var rv reflect.Value

	// d.MValue.

	raw := d.MValue.GetValue()

	if _, ok := raw.(*pb.MValue_NoneValue); ok {
		LogWarning("MValue_NoneValue will not be decoded")
	} else if _, ok := raw.(*pb.MValue_NilValue); ok {
		rv = reflect.ValueOf(nil)
	} else if v, ok := raw.(*pb.MValue_BoolValue); ok {
		rv = reflect.ValueOf(v.BoolValue)
	} else if v, ok := raw.(*pb.MValue_IntValue); ok {
		rv = reflect.ValueOf(v.IntValue)
	} else if v, ok := raw.(*pb.MValue_UintValue); ok {
		rv = reflect.ValueOf(v.UintValue)
	} else if v, ok := raw.(*pb.MValue_DoubleValue); ok {
		rv = reflect.ValueOf(v.DoubleValue)
	} else if v, ok := raw.(*pb.MValue_StringValue); ok {
		rv = reflect.ValueOf(v.StringValue)
	} else if v, ok := raw.(*pb.MValue_BaseObjectValue); ok {
		v, err := baseObjectToReflectValue(v.BaseObjectValue, false)
		if err != nil {
			return rv, err
		}

		rv = reflect.ValueOf(v)
	} else if v, ok := raw.(*pb.MValue_ExternFunctionValue); ok {
		ptr, err := parsePointer(v.ExternFunctionValue.GetPtr())
		if err != nil {
			return rv, fmt.Errorf("failed to parse imported function pointer: %v", err.Error())
		}

		rv = reflect.ValueOf(ExternFunction{
			Ptr: ptr,
		})
	} else if v, ok := raw.(*pb.MValue_Vector3Value); ok {
		rv = reflect.ValueOf(Vector3{
			X: v.Vector3Value.GetX(),
			Y: v.Vector3Value.GetY(),
			Z: v.Vector3Value.GetZ(),
		})
	} else if v, ok := raw.(*pb.MValue_RgbaValue); ok {
		rv = reflect.ValueOf(RGBA{
			R: uint8(v.RgbaValue.GetR()),
			G: uint8(v.RgbaValue.GetG()),
			B: uint8(v.RgbaValue.GetB()),
			A: uint8(v.RgbaValue.GetA()),
		})
	} else if v, ok := raw.(*pb.MValue_BytesValue); ok {
		rv = reflect.ValueOf(v.BytesValue)
	} else if v, ok := raw.(*pb.MValue_Vector2Value); ok {
		rv = reflect.ValueOf(Vector2{
			X: v.Vector2Value.GetX(),
			Y: v.Vector2Value.GetY(),
		})
	} else if len(d.MValue.GetDict()) > 0 {
		keys := d.MValue.GetDict()
		values := d.MValue.GetList()

		data := make(map[string]interface{})

		for i, key := range keys {
			valueDecoder := &ReflectDecoder{
				MValue: values[i],
			}

			value, err := valueDecoder.decode()
			if err != nil {
				return rv, err
			}

			data[key] = value.Interface()
		}

		rv = reflect.ValueOf(data)
	} else if len(d.MValue.GetList()) > 0 {
		values := d.MValue.GetList()
		data := make([]interface{}, len(values))

		for i, value := range values {
			valueDecoder := &ReflectDecoder{
				MValue: value,
			}

			value, err := valueDecoder.decode()
			if err != nil {
				return rv, err
			}

			data[i] = value.Interface()
		}

		rv = reflect.ValueOf(data)
	}

	return rv, nil
}
