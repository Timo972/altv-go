// +build windows

package alt

import (
	"fmt"
	"syscall"
)

var dll = syscall.NewLazyDLL("go-module.dll")

func GetLibrary() *syscall.LazyDLL {
	return dll
}

func GetFunc(name string, a ...uintptr) {
	proc := dll.NewProc(name)
	_, _, err := proc.Call(a...)

	if err == nil {
		fmt.Println(err)
	}
}
