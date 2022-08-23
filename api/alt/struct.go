package alt

import (
	"reflect"
)

func getFieldName(t reflect.StructField) string {
	var name string

	name, ok := t.Tag.Lookup("alt")
	if !ok {
		name = t.Name
	}

	return name
}

func structToProto(rt reflect.Type(), rv reflect.Value) *pb.MValue {
var protoValue *pb.MValue

structName := rt.Name()

if structName == "RGBA" {
protoValue = &pb.MValue{
Value: &pb.MValue_RgbaValue{
RgbaValue: &pb.RGBA{
R: proto.Uint32(uint32(rv.FieldByName("R").Uint())),
G: proto.Uint32(uint32(rv.FieldByName("G").Uint())),
B: proto.Uint32(uint32(rv.FieldByName("B").Uint())),
A: proto.Uint32(uint32(rv.FieldByName("A").Uint())),
},
},
}
} else if structName == "Vector2" {
protoValue = &pb.MValue{
Value: &pb.MValue_Vector2Value{
Vector2Value: &pb.Vector2{
X: proto.Float32(float32(rv.FieldByName("X").Float())),
Y: proto.Float32(float32(rv.FieldByName("Y").Float())),
},
},
}
} else if structName == "Vector3" {
protoValue = &pb.MValue{
Value: &pb.MValue_Vector3Value{
Vector3Value: &pb.Vector3{
X: proto.Float32(float32(rv.FieldByName("X").Float())),
Y: proto.Float32(float32(rv.FieldByName("Y").Float())),
Z: proto.Float32(float32(rv.FieldByName("Z").Float())),
},
},
}
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
mvalues[i] = newProtoMValue(field.Interface())

}

// export methods
for i := fieldCount; i < allCount; i++ {
method := rt.Method(i)
// this enabled means you can not export methods in camelCase - only PascalCase
// if !method.IsExported() {
// 	continue
// }
keys[i] = method.Type().Name()
mvalues[i] = newProtoMValue(method.Func.Interface())
}

protoValue = &pb.MValue{
Dict: keys,
List: mvalues,
}
}

return protoValue
}
