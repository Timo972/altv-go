package mvalue

import (
	"encoding/json"
	"fmt"
	"github.com/timo972/altv-go/api/alt"
	"testing"
	"unsafe"
)

type MyStruct struct {
	Name   string
	Model  uint
	Price  int
	Real   bool
	Child  MyStruct2
	Color  alt.RGBA
	Player *alt.Player
	// More  []MyStruct
}

type MyStruct2 struct {
	Name  string
	Model uint
	Price int
	Real  bool
	//Child MyStruct
	// More  []MyStruct
}

var exampleData = &MyStruct{
	Color:  alt.RGBA{R: 255, G: 255, B: 255, A: 255},
	Player: alt.NewPlayer(unsafe.Pointer(uintptr(1))),
	Name:   "adder",
	Model:  010101,
	Price:  99999,
	Real:   false,
	Child: MyStruct2{
		Name:  "bugatti",
		Model: 10101,
		Price: 3500000,
		Real:  true,
	},
}

func BenchmarkMarshal(b *testing.B) {
	// b.ReportAllocs()

	data, err := Marshal(exampleData)
	if err != nil {
		b.Error(err)
	}

	// var msg pb.MValue
	// err = proto.Unmarshal(data, &msg)
	// if err != nil {
	// 	b.Error(err)
	// }

	// fmt.Println(msg.String())

	fmt.Printf("Result: %s \n", string(data))
}

func BenchmarkMarshalJson(b *testing.B) {
	// b.ReportAllocs()

	data, err := json.Marshal(exampleData)
	if err != nil {
		b.Error(err)
	}

	fmt.Printf("Result: %s \n", string(data))
}
