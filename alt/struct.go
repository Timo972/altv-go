package alt

import (
	"reflect"

	"github.com/timo972/altv-go-pkg/pb"
)

func getFieldName(t reflect.StructField) string {
	var name string

	name, ok := t.Tag.Lookup("alt")
	if !ok {
		name = t.Name
	}

	return name
}

func structToProto(rt reflect.Type, rv reflect.Value) (*pb.MValue, MValueType) {
	var mValueType MValueType
	var protoValue *pb.MValue

	structName := rt.Name()

	if structName == "RGBA" {
		protoValue = &pb.MValue{
			RgbaValue: &pb.RGBA{
				R: uint32(rv.FieldByName("R").Uint()),
				G: uint32(rv.FieldByName("G").Uint()),
				B: uint32(rv.FieldByName("B").Uint()),
				A: uint32(rv.FieldByName("A").Uint()),
			},
		}
		mValueType = MValueRGBA
	} else if structName == "Vector2" {
		protoValue = &pb.MValue{
			Vector2Value: &pb.Vector2{
				X: float32(rv.FieldByName("X").Float()),
				Y: float32(rv.FieldByName("Y").Float()),
			},
		}
		mValueType = MValueVector2
	} else if structName == "Vector3" {
		protoValue = &pb.MValue{
			Vector3Value: &pb.Vector3{
				X: float32(rv.FieldByName("X").Float()),
				Y: float32(rv.FieldByName("Y").Float()),
				Z: float32(rv.FieldByName("Z").Float()),
			},
		}
		mValueType = MValueVector3
	} else {
		// user struct

		fieldCount := rv.NumField()
		allCount := fieldCount + rv.NumMethod()

		keys := make([]string, allCount)
		mvalues := make([]*pb.MValue, allCount)

		// export data
		for i := 0; i < fieldCount; i++ {
			field := rv.Field(i)
			fieldType := rt.Field(i)

			keys[i] = getFieldName(fieldType)
			mvalues[i], _ = newProtoMValue(field.Interface())

		}

		// export methods
		for i := fieldCount; i < allCount; i++ {
			method := rt.Method(i)
			// this enabled means you can not export methods in camelCase - only PascalCase
			// if !method.IsExported() {
			// 	continue
			// }
			keys[i] = method.Type.Name()
			mvalues[i], _ = newProtoMValue(method.Func.Interface())
		}

		protoValue = &pb.MValue{
			Dict: keys,
			List: mvalues,
		}
		mValueType = MValueDict
	}

	return protoValue, mValueType
}

func protoToStruct(p *pb.MValue, rt reflect.Type, rv reflect.Value) {

}
