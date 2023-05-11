package altv

import (
	"testing"

	"github.com/timo972/altv-go/mvalue"
)

func TestVector2Marshal(t *testing.T) {
	v := Vector2{
		X: 1,
		Y: 2,
	}

	data, err := mvalue.Marshal(v)
	if err != nil {
		t.Error(err)
	}

	if string(data) != `{"$type":14,"x":1,"y":2}` {
		t.Error("wrong json data")
	}
}

func TestVector2Unmarshal(t *testing.T) {
	v := Vector2{}

	err := mvalue.Unmarshal([]byte(`{"$type":14,"x":1,"y":2}`), &v)
	if err != nil {
		t.Error(err)
	}

	if v.X != 1 || v.Y != 2 {
		t.Error("wrong vector data")
	}
}

func TestVector3Marshal(t *testing.T) {
	v := Vector3{
		X: 1,
		Y: 2,
		Z: 3,
	}

	data, err := mvalue.Marshal(v)
	if err != nil {
		t.Error(err)
	}

	if string(data) != `{"$type":11,"x":1,"y":2,"z":3}` {
		t.Error("wrong json data")
	}
}

func TestVector3Unmarshal(t *testing.T) {
	v := Vector3{}

	err := mvalue.Unmarshal([]byte(`{"$type":11,"x":1,"y":2,"z":3}`), &v)
	if err != nil {
		t.Error(err)
	}

	if v.X != 1 || v.Y != 2 || v.Z != 3 {
		t.Error("wrong vector data")
	}
}
