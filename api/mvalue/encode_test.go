package mvalue

import (
	"testing"
)

type MyStruct struct {
	Name  string
	Model uint
	Price int
	Real  bool
	Child MyStruct2
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

func BenchmarkMarshal(b *testing.B) {
	b.ReportAllocs()

	m := &MyStruct{
		Name:  "adder",
		Model: 010101,
		Price: 99999,
		Real:  false,
		Child: MyStruct2{
			Name:  "bugatti",
			Model: 10101,
			Price: 3500000,
			Real:  true,
		},
	}

	_, err := Marshal(m)
	if err != nil {
		b.Error(err)
	}

	// var msg pb.MValue
	// err = proto.Unmarshal(data, &msg)
	// if err != nil {
	// 	b.Error(err)
	// }

	// fmt.Println(msg.String())
}
