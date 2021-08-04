package alt

import (
	alt "github.com/shockdev04/altv-go-pkg/alt/objects"
)

type PlayerConnectListener = func(p *alt.Player)

type eventManager struct {

}

type Listener interface {
	PlayerConnect(listener PlayerConnectListener)
}

var On = &eventManager{}

func (e eventManager) PlayerConnect(listener PlayerConnectListener) {

}
