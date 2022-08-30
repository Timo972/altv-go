package alt

import (
	"reflect"

	"github.com/timo972/altv-go/internal/pb"
)

func mapToProto(rt reflect.Type, rv reflect.Value) *pb.MValue {
	keys := rv.MapKeys()
	size := len(keys)

	dict := make(map[string]*pb.MValue, size)

	//stringKeys := make([]string, size)
	//mvalues := make([]*pb.MValue, size)

	for _, key := range keys {
		//stringKeys[i] = key.String()
		/*mvalues[i]*/
		dict[key.String()] = newProtoMValue(rv.MapIndex(key).Interface())
	}

	return &pb.MValue{
		Dict: dict,
	}
}
