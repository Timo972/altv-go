package mvalue

import (
	"testing"
	"unsafe"
)

func TestFuncMarshal(t *testing.T) {
	testCases := []struct {
		input  ExportFunc
		output string
	}{
		{func(ctx *FuncCtx) any {
			return nil
		}, `{"$type":10,"id":0}`},
	}

	for _, testCase := range testCases {
		result, err := Marshal(testCase.input)
		if err != nil {
			t.Error(err)
			continue
		}

		if string(result) != testCase.output {
			t.Errorf("Marshal(Func) = %s; want %s", string(result), testCase.output)
		}
	}
}

func TestFuncUnmarshal(t *testing.T) {
	testCases := []struct {
		input  string
		output ImportFunc
	}{
		{`{"ptr":""}`, ImportFunc{ptr: unsafe.Pointer(uintptr(0))}},
	}

	for _, testCase := range testCases {
		var fn ImportFunc

		err := Unmarshal([]byte(testCase.input), &fn)
		if err != nil {
			t.Error(err)
			continue
		}

		if fn != testCase.output {
			t.Errorf("fn = nil; want %+v", testCase.output)
			continue
		}
	}
}

func TestFuncCall(t *testing.T) {
	fn := &ImportFunc{
		ptr: unsafe.Pointer(uintptr(0)),
	}

	CallFunc(fn)
}
