// +build windows

package alt

import "syscall"

var (
	h, err  = syscall.LoadLibrary("go-module.dll")
	proc, _ = syscall.GetProcAddress(h, "Resource_Init")
)

func GetLibrary() (syscall.Handle, error) {
	return h, err
}
