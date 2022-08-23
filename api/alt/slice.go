package alt

import (
	"reflect"
)

func sliceToProto(rt reflect.Type(), rv reflect.Value) *pb.MValue {
var protoValue *pb.MValue

// list
sliceName := rt.Elem().Name()

// byte array
if sliceName == "uint8" || sliceName == "byte" {
bytes := rv.Bytes()

protoValue = &pb.MValue{
Value: &pb.MValue_BytesValue{
BytesValue: bytes,
},
}
} else {
size := rv.Len()
mvalues := make([]*pb.MValue, size)

for i := 0; i < size; i++ {
item := rv.Index(i)
mvalues[i] = newProtoMValue(item.Interface())
}

protoValue = &pb.MValue{
List: mvalues,
}
}

return protoValue
}
