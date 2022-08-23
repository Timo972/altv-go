package alt

import (
	"reflect"
)

func mapToProto(rt reflect.Type(), rv reflect.Value) *pb.MValue {
keys := rv.MapKeys()
size := len(keys)

stringKeys := make([]string, size)
mvalues := make([]*pb.MValue, size)

for i, key := range keys {
stringKeys[i] = key.String()
mvalues[i] = newProtoMValue(rv.MapIndex(key).Interface())
}

return &pb.MValue{
Dict: stringKeys,
List: mvalues,
}
}
