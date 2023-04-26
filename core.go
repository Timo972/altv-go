package altv

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"

// StopServer stops the server and it's resources.
func StopServer() {
	C.core_stop_server()
}
