package altv

// #cgo CFLAGS: -I./internal/c-api/lib
// #cgo linux LDFLAGS: -L./internal/c-api/lib/linux -lcapi -ldl -g
// #cgo windows LDFLAGS: -L./internal/c-api/lib/win32 -lcapi -ldl -g
// #cgo CXXFLAGS: -std=c++14
// #include <stdlib.h>
// #include "capi.h"
import "C"
