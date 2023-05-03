package mvalue

import (
	"unsafe"

	"github.com/goccy/go-json"
)

type FuncCtx struct{}

type ExportFunc func(ctx *FuncCtx) any
type ImportFunc struct {
	ptr unsafe.Pointer
}

type exportFuncData struct {
	SpecialType
	ID           int        `json:"id"`
	exportedFunc ExportFunc `json:"-"`
}

type importFuncData struct {
	SpecialType
	Ptr string `json:"ptr"`
}

var exported = make([]*exportFuncData, 0)

func (f ExportFunc) MarshalJSON() ([]byte, error) {
	data := &exportFuncData{
		SpecialType:  SpecialType{Type: TypeFunction},
		ID:           len(exported),
		exportedFunc: f,
	}
	exported = append(exported, data)
	return json.Marshal(data)
}

func (f *ImportFunc) UnmarshalJSON(raw []byte) error {
	var data importFuncData
	err := json.Unmarshal(raw, &data)
	if err != nil {
		return err
	}
	f.ptr, err = ParsePointer(data.Ptr)
	return err
}

func CallFunc(f *ImportFunc, args ...any) any {
	return nil
}
