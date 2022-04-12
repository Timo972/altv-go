package alt

//#ifndef _WIN32
//#include <stdlib.h>
//#endif
// #include "Module.h"
import "C"
import (
	"encoding/json"
	"unsafe"

	"github.com/shockdev04/altv-go-pkg/internal/module"
)

type MValueType = uint8
type MValueFunc = func(args ...interface{}) interface{}

const (
	MValueNone MValueType = iota
	MValueNil
	MValueBool
	MValueInt
	MValueUInt
	MValueDouble
	MValueString
	MValueList
	MValueDict
	MValueBaseObject
	MValueFunction
	MValueVector3
	MValueRGBA
	MValueByteArray
	MValueVector2
)

var (
	mValueFuncCount = uint64(0)
	mValueFunctions = make(map[uint64]MValueFunc)
)

type MValue struct {
	Ptr   unsafe.Pointer
	Type  MValueType
	Value interface{}
}

func CreateMValue(value interface{}) *MValue {
	var mValuePtr unsafe.Pointer
	var mValueType MValueType

	switch value.(type) {
	case bool:
		mValuePtr = C.core_create_mvalue_bool(C.int(module.Bool2int(value.(bool))))
		mValueType = MValueBool
	case int, int8, int16, int32, int64:
		if val, ok := value.(int); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		} else if val, ok := value.(int8); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		} else if val, ok := value.(int16); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		} else if val, ok := value.(int32); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		} else if val, ok := value.(int64); ok {
			mValuePtr = C.core_create_mvalue_int(C.longlong(val))
		}
		mValueType = MValueInt
	case uint, uint8, uint16, uint32, uint64:
		if val, ok := value.(uint); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		} else if val, ok := value.(uint8); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		} else if val, ok := value.(uint16); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		} else if val, ok := value.(uint32); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		} else if val, ok := value.(uint64); ok {
			mValuePtr = C.core_create_mvalue_uint(C.ulonglong(val))
		}
		mValueType = MValueUInt
	case float32, float64:
		if val, ok := value.(float32); ok {
			mValuePtr = C.core_create_mvalue_double(C.double(val))
		} else if val, ok := value.(float64); ok {
			mValuePtr = C.core_create_mvalue_double(C.double(val))
		}
		mValueType = MValueDouble
	case string:
		cstr := C.CString(value.(string))
		defer C.free(unsafe.Pointer(cstr))

		mValuePtr = C.core_create_mvalue_string(cstr)
		mValueType = MValueString
	case []interface{}, []bool, []string, []int, []int8, []int16, []int32, []int64, []uint, []uint16, []uint32, []uint64, []float32, []float64:
		js, _ := json.Marshal(value)
		cJson := C.CString(string(js))
		defer C.free(unsafe.Pointer(cJson))
		size := len(value.([]interface{}))

		mValuePtr = C.core_create_mvalue_list(cJson, C.ulonglong(size))
		mValueType = MValueList
	case []byte:
		data := value.([]byte)
		size := len(data)
		arrayPtr := C.CBytes(data)
		defer C.free(arrayPtr)

		mValuePtr = C.core_create_mvalue_byte_array((*C.uchar)(arrayPtr), C.ulonglong(size))
		mValueType = MValueByteArray
	case RGBA:
		color := value.(RGBA)

		mValuePtr = C.core_create_mvalue_rgba(C.uchar(color.R), C.uchar(color.G), C.uchar(color.B), C.uchar(color.A))
		mValueType = MValueRGBA
	case Vector2:
		v2 := value.(Vector2)

		mValuePtr = C.core_create_mvalue_vector2(C.float(v2.X), C.float(v2.Y))
		mValueType = MValueVector3
	case Vector3:
		v3 := value.(Vector3)

		mValuePtr = C.core_create_mvalue_vector3(C.float(v3.X), C.float(v3.Y), C.float(v3.Z))
		mValueType = MValueVector3
	case *Player, *Vehicle, *ColShape, *Checkpoint, *VoiceChannel, *Blip, *Entity:
		var ptr unsafe.Pointer
		var _type BaseObjectType

		if player, ok := value.(*Player); ok {
			ptr = player.Ptr
			_type = player.Type
		}

		if vehicle, ok := value.(*Vehicle); ok {
			ptr = vehicle.Ptr
			_type = vehicle.Type
		}

		if colShape, ok := value.(*ColShape); ok {
			ptr = colShape.Ptr
			_type = colShape.Type
		}

		if checkpoint, ok := value.(*Checkpoint); ok {
			ptr = checkpoint.Ptr
			_type = checkpoint.Type
		}

		if voiceChannel, ok := value.(*VoiceChannel); ok {
			ptr = voiceChannel.Ptr
			_type = voiceChannel.Type
		}

		if blip, ok := value.(*Blip); ok {
			ptr = blip.Ptr
			_type = blip.Type
		}

		if entity, ok := value.(*Entity); ok {
			ptr = entity.Ptr
			_type = entity.Type
		}

		if ptr == nil {
			mValuePtr = nil
			mValueType = MValueNone
			break
		}

		mValuePtr = C.core_create_mvalue_base_object(C.uchar(_type), ptr)
		mValueType = MValueBaseObject
	case MValueFunc:
		mValueFunc := value.(MValueFunc)
		mValueFuncCount++
		id := mValueFuncCount
		mValueFunctions[id] = mValueFunc

		cResource := C.CString(Resource.Name)
		defer C.free(unsafe.Pointer(cResource))

		mValuePtr = C.create_mvalue_function(cResource, C.ulonglong(id))
		mValueType = MValueFunction
	default:
		mValuePtr = nil
		mValueType = MValueNone
	}

	return &MValue{Ptr: mValuePtr, Type: mValueType, Value: nil}
}

func (v MValue) GetValue() interface{} {
	switch v.Type {
	case MValueBool:
		v.Value = int(C.core_get_mvalue_bool(v.Ptr)) != 0
	case MValueInt:
		v.Value = int64(C.core_get_mvalue_int(v.Ptr))
	case MValueUInt:
		v.Value = uint64(C.core_get_mvalue_uint(v.Ptr))
	case MValueDouble:
		v.Value = float64(C.core_get_mvalue_double(v.Ptr))
	case MValueString:
		v.Value = C.GoString(C.core_get_mvalue_string(v.Ptr))
	case MValueBaseObject:
		entity := C.core_get_mvalue_base_object(v.Ptr)
		_type := uint8(entity.Type)
		if _type == PlayerObject {
			v.Value = newPlayer(entity.Ptr)
		} else if _type == VehicleObject {
			v.Value = newVehicle(entity.Ptr)
		} else if _type == ColshapeObject {
			v.Value = newColShape(entity.Ptr)
		} else if _type == CheckpointObject {
			v.Value = newCheckpoint(entity.Ptr)
		} else if _type == VoiceChannelObject {
			v.Value = newVoiceChannel(entity.Ptr)
		}
	case MValueVector2:
		v.Value = newVector2(C.core_get_mvalue_vector2(v.Ptr))
	case MValueVector3:
		v3 := C.core_get_mvalue_vector3(v.Ptr)
		v.Value = Vector3{X: float32(v3.x), Y: float32(v3.y), Z: float32(v3.z)}
	case MValueRGBA:
		color := C.core_get_mvalue_rgba(v.Ptr)
		v.Value = RGBA{R: uint8(color.r), G: uint8(color.g), B: uint8(color.g), A: uint8(color.a)}
	case MValueByteArray:
		arr := C.core_get_mvalue_byte_array(v.Ptr)
		v.Value = C.GoBytes(arr.array, C.int(arr.size))
	case MValueFunction:
		v.Value = func(args ...interface{}) interface{} {
			cArgPtr, cArgSize := newMValueArray(args)
			defer C.free(unsafe.Pointer(cArgPtr))

			cMeta := C.call_mvalue_function(v.Ptr, cArgPtr, cArgSize)
			mVal := &MValue{Ptr: cMeta.Ptr, Type: uint8(cMeta.Type)}

			value := mVal.GetValue()

			return value
		}
	default:
		v.Value = nil
	}

	return v.Value
}

func (v MValue) GetType() MValueType {
	return v.Type
}

//export altCallFunction
func altCallFunction(id C.ulonglong, cMValues unsafe.Pointer, cSize C.ulonglong) C.struct_data {
	listener := mValueFunctions[uint64(id)]

	if listener == nil {
		mVal := CreateMValue(nil)
		return C.struct_data{mValue: mVal.Ptr, Type: C.uint(mVal.Type)}
	}

	args := convertMValueArray(cMValues, cSize)

	returnValue := listener(args...)
	returnMValue := CreateMValue(returnValue)

	return C.struct_data{mValue: returnMValue.Ptr, Type: C.uint(returnMValue.Type)}
}
