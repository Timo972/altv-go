package mvalue

import (
	"fmt"
	"testing"
)

func TestByteArrayMarshal(t *testing.T) {
	data, err := Marshal([]byte{0, 1, 2, 3, 4, 5})
	if err != nil {
		t.Error(err)
	}

	fmt.Println(string(data))
}

func TestIntMarshal(t *testing.T) {
	data, err := Marshal(42)
	if err != nil {
		t.Error(err)
	}

	fmt.Printf("%s\n", data)

	var i int
	if err = Unmarshal(data, &i); err != nil {
		t.Error(err)
	}

	if i != 42 {
		t.Error("i != 42")
	}
}
