package cutil

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
