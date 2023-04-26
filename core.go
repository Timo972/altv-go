package altv

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"

func StopServer() {
	C.core_stop_server()
}
