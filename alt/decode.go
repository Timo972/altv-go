package alt

// #cgo CFLAGS: -I../c-api/build/Release
// #cgo LDFLAGS: -L../c-api/build/Release -lcapi
// #include <stdlib.h>
// #include <stdio.h>
// #include "../c-api/capi.h"
import "C"
import (
	"fmt"
	"reflect"
	"strconv"
	"unsafe"

	"github.com/timo972/altv-go-pkg/pb"
	"golang.org/x/exp/slices"
	"google.golang.org/protobuf/proto"
)

// type IDecoder interface {
// 	Decode(v interface{}) error
// }

type Decoder struct {
	Buffer    []byte
	RootValue reflect.Value
	RootType  reflect.Type
	MValue    *pb.MValue
}

func newDecoder(data []byte) *Decoder {
	return &Decoder{
		Buffer: data,
	}
}

func decode(arr C.struct_array, v interface{}) error {
	bytes := C.GoBytes(arr.array, C.int(arr.size))

	d := newDecoder(bytes)
	return d.Decode(v)
}

func decodeArgs(arr C.struct_array) ([]reflect.Value, error) {
	size := int(arr.size)
	if size == 0 {
		return nil, nil
	}

	data := make([]reflect.Value, size)

	cBytesArray := (*[1 << 30]C.struct_array)(arr.array)
	for i := 0; i < size; i++ {
		bytes := C.GoBytes(cBytesArray[i].array, C.int(cBytesArray[i].size))
		d := newReflectDecoder(bytes)

		val, err := d.Decode()
		if err != nil {
			return nil, err
		}

		data[i] = val
	}

	return data, nil
}

func parsePointer(ptrStr string) (unsafe.Pointer, error) {
	ptrUint, err := strconv.ParseUint(ptrStr, 10, 64)
	if err != nil {
		return nil, err
	}

	return unsafe.Pointer(uintptr(ptrUint)), nil

	//str := C.CString(ptrStr)
	//defer C.free(unsafe.Pointer(str))
	//var ptr unsafe.Pointer
	//C.sscanf(str, "%p", &ptr)
	//_, err := fmt.Sscanf(ptrStr, "%p", &ptr)

	//return ptr, err
}

func (d *Decoder) unmarshalBytes() error {
	if d.MValue == nil && len(d.Buffer) > 0 {
		d.MValue = &pb.MValue{}
		return proto.Unmarshal(d.Buffer, d.MValue)
	} else if d.MValue == nil && len(d.Buffer) == 0 {
		return fmt.Errorf("no data to decode")
	}

	return nil
}

func (d *Decoder) Decode(v interface{}) error {
	if reflect.TypeOf(v).Kind() != reflect.Ptr {
		return fmt.Errorf("root type must be a pointer")
	}

	err := d.unmarshalBytes()
	if err != nil {
		return err
	}

	d.RootValue = reflect.ValueOf(v).Elem()
	d.RootType = d.RootValue.Type()

	return d.decode()
}

func (d *Decoder) decode() error {
	switch d.RootType.Kind() {
	case reflect.Ptr:
		rt := d.RootType.Elem()
		rv := d.RootValue //.Elem()
		kind := rt.Kind()

		if kind == reflect.Struct {
			// struct pointer
			return d.decodeStruct(rt, rv)
		} else if kind == reflect.Slice || kind == reflect.Array {
			// slice / array pointer
			return d.decodeSlice(rt, rv)
		} else if kind == reflect.Map {
			// map pointer
			return d.decodeMap(rt, rv)
		}
	case reflect.String:
		d.RootValue.SetString(d.MValue.GetStringValue())
	case reflect.Bool:
		d.RootValue.SetBool(d.MValue.GetBoolValue())
	case reflect.Float32, reflect.Float64:
		d.RootValue.SetFloat(d.MValue.GetDoubleValue())
	case reflect.Func:
		// function
		f := d.MValue.GetExternFunctionValue()
		ptr, err := parsePointer(f.GetPtr())
		if err != nil {
			return err
		}

		d.RootValue.Set(reflect.ValueOf(ExternFunction{
			Ptr: ptr,
		}))
	// integers
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		d.RootValue.SetInt(d.MValue.GetIntValue())
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		d.RootValue.SetUint(d.MValue.GetUintValue())
	case reflect.Array, reflect.Slice:
		return d.decodeSlice(d.RootType, d.RootValue)
	case reflect.Struct:
		// vector3, rgba, vector2
		return d.decodeStruct(d.RootType, d.RootValue)
	case reflect.Map:
		// map
		return d.decodeMap(d.RootType, d.RootValue)
	default:
		return fmt.Errorf("unsupported type: %s", d.RootType.Kind())
	}

	return nil
}

func baseObjectToReflectValue(base *pb.BaseObject, isEntity bool) (reflect.Value, error) {
	t := BaseObjectType(base.GetType())
	ptr, err := parsePointer(base.GetPtr())
	var v reflect.Value

	if err != nil {
		return v, err
	}

	switch t {
	case PlayerObject:
		if isEntity {
			e := &Entity{}
			e.Ptr = ptr
			e.Type = t
			v = reflect.ValueOf(e)
		} else {
			v = reflect.ValueOf(newPlayer(ptr))
		}
	case VehicleObject:
		if isEntity {
			e := &Entity{}
			e.Ptr = ptr
			e.Type = t
			v = reflect.ValueOf(e)
		} else {
			v = reflect.ValueOf(newVehicle(ptr))
		}
	case ColshapeObject:
		v = reflect.ValueOf(newColShape(ptr))
	case CheckpointObject:
		v = reflect.ValueOf(newCheckpoint(ptr))
	case VoiceChannelObject:
		v = reflect.ValueOf(newVoiceChannel(ptr))
	case BlipObject:
		v = reflect.ValueOf(newBlip(ptr))
	}

	return v, nil
}

func (d *Decoder) decodeStruct(rt reflect.Type, rv reflect.Value) error {
	structName := rt.Name()

	if structName == "RGBA" {
		rgba := d.MValue.GetRgbaValue()

		rv.Set(reflect.ValueOf(RGBA{
			R: uint8(rgba.GetR()),
			G: uint8(rgba.GetG()),
			B: uint8(rgba.GetB()),
			A: uint8(rgba.GetA()),
		}))
	} else if structName == "Vector2" {
		v2 := d.MValue.GetVector2Value()

		rv.Set(reflect.ValueOf(Vector2{
			X: v2.GetX(),
			Y: v2.GetY(),
		}))
	} else if structName == "Vector3" {
		v3 := d.MValue.GetVector3Value()

		rv.Set(reflect.ValueOf(Vector3{
			X: v3.GetX(),
			Y: v3.GetY(),
			Z: v3.GetZ(),
		}))
	} else if structName == "Player" || structName == "Entity" || structName == "Vehicle" || structName == "ColShape" || structName == "Checkpoint" || structName == "VoiceChannel" || structName == "Blip" {
		base := d.MValue.GetBaseObjectValue()

		v, err := baseObjectToReflectValue(base, structName == "Entity")
		if err != nil {
			return err
		}

		rv.Set(v)
	} else {
		keys := d.MValue.GetDict()
		values := d.MValue.GetList()

		fieldCount := rv.NumField()

		for i := 0; i < fieldCount; i++ {
			field := rv.Field(i)
			fieldType := rt.Field(i)
			name := getFieldName(fieldType)

			i := slices.Index(keys, name)
			if i < 0 || i >= len(values) {
				// field is not set
				continue
			}

			valueDecoder := &Decoder{
				MValue:    values[i],
				RootValue: field,
				RootType:  field.Type(),
			}

			err := valueDecoder.decode()
			if err != nil {
				return err
			}
		}
	}

	return nil
}

func (d *Decoder) decodeMap(rt reflect.Type, rv reflect.Value) error {
	m := reflect.MakeMap(rt)

	keys := d.MValue.GetDict()
	values := d.MValue.GetList()

	for i, key := range keys {
		valueDecoder := &Decoder{
			MValue: values[i],
			// FIXME: ???
			RootValue: reflect.New(rt.Elem()),
			RootType:  rt.Elem(),
		}

		err := valueDecoder.decode()
		if err != nil {
			return err
		}

		m.SetMapIndex(reflect.ValueOf(key), valueDecoder.RootValue)
	}

	rv.Set(m)

	return nil
}

func (d *Decoder) decodeSlice(rt reflect.Type, rv reflect.Value) error {
	values := d.MValue.GetList()
	size := len(values)
	l := reflect.MakeSlice(rt, size, size)
	elemType := rt.Elem()

	// TODO: support byte array

	for i, pbVal := range values {
		valueDecoder := &Decoder{
			MValue:    pbVal,
			RootValue: l.Index(i),
			RootType:  elemType,
		}

		err := valueDecoder.decode()
		if err != nil {
			return err
		}
	}

	rv.Set(l)

	return nil
}
