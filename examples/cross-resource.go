package examples

import "C"
import (
	"fmt"
	"github.com/timo972/altv-go-pkg/alt"
)

func main() {}

type ChatRegisterCmd = func(cmd string, description string, callback func(player *alt.Player, args ...[]string))

//export OnStart
func OnStart() {
	registerCmd := alt.Import[ChatRegisterCmd]("chat", "registerCmd")
	registerCmd("/test", "test", func(player *alt.Player, args ...[]string) {
		alt.LogInfo(fmt.Sprintf("%s: %s", player.Name(), args[0]))
	})
}

//export OnStop
func OnStop() {}
