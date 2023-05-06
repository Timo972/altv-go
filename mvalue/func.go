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
	ResourceName string     `json:"resourceName"`
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
		ResourceName: resourceName,
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

// CallFunc calls the exported function of another resource with the given arguments.
func CallFunc(f *ImportFunc, args ...any) any {
	return nil
}

// SetResourceName sets the resource name for the exported functions. Do not use this by yourself or you might break function exporting!
func SetResourceName(name string) {
	resourceName = name
}
