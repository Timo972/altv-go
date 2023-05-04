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
