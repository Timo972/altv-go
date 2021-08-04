package alt

type PlayerConnectListener = func(p *Player)
type PlayerDisconnectListener = func(p *Player)

type eventManager struct {
	PlayerConnectEvents []PlayerConnectListener
}

type Listener interface {
	PlayerConnect(listener PlayerConnectListener)
}

var On = &eventManager{}

func (e eventManager) PlayerConnect(listener PlayerConnectListener) {
	On.PlayerConnectEvents = append(On.PlayerConnectEvents, listener)
}

