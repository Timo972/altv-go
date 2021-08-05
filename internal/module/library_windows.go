// +build windows

package module

import (
	"fmt"
	"syscall"
)

var dll = syscall.NewLazyDLL("go-module.dll")

func GetFunc(name string, a ...uintptr) (uintptr, uintptr) {
	proc := dll.NewProc(name)
	r1, r2, err := proc.Call(a...)

	if err == nil {
		fmt.Println(err)
	}

	return r1, r2
}
