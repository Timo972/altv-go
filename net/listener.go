package altnet

import (
	"errors"
	"net"

	"github.com/timo972/altv-go"
	"github.com/timo972/altv-go/events"
)

type altListener struct {
	connch chan net.Conn
}

func (l *altListener) Accept() (net.Conn, error) {
	return <-l.connch, nil
}

func (l *altListener) Addr() net.Addr {
	return &net.IPAddr{}
}

func (l *altListener) Close() error {
	return errors.New("altListener cannot be closed")
}

func (l *altListener) addConn(c *PlayerConn) {
	l.connch <- c
}

var Listener net.Listener

func init() {
	l := &altListener{
		connch: make(chan net.Conn, 1),
	}

	events.On.PlayerConnect(func(p altv.Player) {
		c := NewPlayerConn(p)
		l.addConn(c)
	})

	Listener = l
}
