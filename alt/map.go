package alt

import (
	"reflect"

	"github.com/timo972/altv-go-pkg/pb"
)

func mapToProto(rt reflect.Type, rv reflect.Value) (*pb.MValue, MValueType) {
	keys := rv.MapKeys()
	size := len(keys)

	stringKeys := make([]string, size)
	mvalues := make([]*pb.MValue, size)

	for i, key := range keys {
		stringKeys[i] = key.String()
		mvalues[i], _ = newProtoMValue(rv.MapIndex(key).Interface())
	}

	return &pb.MValue{
		Dict: stringKeys,
		List: mvalues,
	}, MValueDict
}
