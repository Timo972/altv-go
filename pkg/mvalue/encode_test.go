package mvalue

// import "C"
import (
	"testing"
)

type simpleStruct struct {
	Writable
	test bool
}

func (s *simpleStruct) OnWrite(writer Writer) {
	writer.BeginObject()
	writer.Name("test")
	writer.Value(s.test)
	writer.EndObject()
}

func TestNewWriter(t *testing.T) {
	w := NewWriter()

	if w.depth != -1 {
		t.Errorf("wrong depth %v, expected %v", w.depth, -1)
	}
	if len(w.current) != 1 {
		t.Errorf("mvalue stack root not allocated")
	}
}

func TestNewMValue(t *testing.T) {
	tests := []struct {
		name     string
		arg      any
		wantType MValueType
	}{
		{
			name:     "int",
			arg:      -3,
			wantType: Int,
		},
		{
			name:     "uint",
			arg:      uint(3),
			wantType: Uint,
		},
		{
			name:     "string",
			arg:      "altvrocks",
			wantType: String,
		},
		{
			name:     "bool",
			arg:      true,
			wantType: Bool,
		},
		{
			name:     "double",
			arg:      float64(3.6),
			wantType: Double,
		},
		/*{
			name:     "simple struct",
			arg:      &simpleStruct{},
			wantType: "dict",
		},*/
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			res, err := NewMValue(tt.arg)
			if err != nil {
				t.Error(err)
			}

			if res.Type != tt.wantType {
				t.Errorf("got mvalue of type %v, want type %v", res, tt.wantType)
			}

			if v := res.testValue(); v != tt.arg {
				t.Errorf("invalid memory addres stored - got value %v, want %v", v, tt.arg)
			}
		})
	}
}
