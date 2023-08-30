package entity

import (
	"testing"

	"github.com/timo972/altv-go/mvalue"
)

func TestBaseObjectMarshal(t *testing.T) {
	testCases := []struct {
		id     uint32
		typ    BaseObjectType
		output string
	}{
		{13, BaseTypePlayer, `{"$type":0,"id":13,"type":0,"ptr":""}`},
	}

	for _, testCase := range testCases {
		x := newBaseObject(testCase.typ, nil, testCase.id)
		obj := BaseObject(&x)

		result, err := mvalue.Marshal(obj)
		if err != nil {
			t.Error(err)
			continue
		}

		if string(result) != testCase.output {
			t.Errorf("mvalue.Marshal(%+v) = %s; want %s", obj, string(result), testCase.output)
		}
	}
}

/*func TestBaseObjectUnmarshal(t *testing.T) {
	testCases := []struct {
		id    uint32
		typ   BaseObjectType
		input string
	}{
		{13, BaseTypePlayer, `{"id":13,"type":0,"ptr":""}`},
	}

	for _, testCase := range testCases {
		var objData BaseObjectData[Player]

		err := mvalue.Unmarshal([]byte(testCase.input), &objData)
		if err != nil {
			t.Error(err)
			continue
		}

		obj, err := objData.Obj()
		if err != nil {
			t.Error(err)
			continue
		}

		if obj.ID() != testCase.id {
			t.Errorf("id = %d; want %d", obj.ID(), testCase.id)
			continue
		}

		if obj.Type() != testCase.typ {
			t.Errorf("typ = %d; want %d", obj.Type(), testCase.typ)
			continue
		}

		if !obj.Valid() {
			t.Errorf("valid = false; want true")
			continue
		}
	}
}*/
