package module
import "C"
import "unsafe"

// Bool2int Temporary
func Bool2int(b bool) int {
	// The compiler currently only optimizes this form.
	var i int
	if b {
		i = 1
	} else {
		i = 0
	}
	return i
}

func MakeStringArray(cSize C.ulonglong, cArray **C.char) []string {
	size := int(cSize)
	cStrings := (*[1 << 28]*C.char)(unsafe.Pointer(cArray))[:size:size]

	array := make([]string, size)

	for i, cString := range cStrings {
		array[i] = C.GoString(cString)
	}

	return array
}