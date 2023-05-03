package altv

import (
	"testing"

	"github.com/timo972/altv-go/mvalue"
)

func TestRGBAMarshal(t *testing.T) {
	testCases := []struct {
		input  RGBA
		output string
	}{
		{RGBA{R: 1, G: 2, B: 3, A: 4}, `{"$type":12,"r":1,"g":2,"b":3,"a":4}`},
	}

	for _, testCase := range testCases {
		result, err := mvalue.Marshal(testCase.input)
		if err != nil {
			t.Error(err)
			continue
		}

		if string(result) != testCase.output {
			t.Errorf("mvalue.Marshal(%+v) = %s; want %s", testCase.input, string(result), testCase.output)
		}
	}
}

func TestRGBAUnmarshal(t *testing.T) {
	testCases := []struct {
		input  string
		output RGBA
	}{
		{`{"r":1,"g":2,"b":3,"a":4}`, RGBA{R: 1, G: 2, B: 3, A: 4}},
	}

	for _, testCase := range testCases {
		var color RGBA

		err := mvalue.Unmarshal([]byte(testCase.input), &color)
		if err != nil {
			t.Error(err)
			continue
		}

		if color != testCase.output {
			t.Errorf("mvalue.Unmarshal(%s) = %+v; want %+v", testCase.input, color, testCase.output)
		}
	}
}
