package altnet

import (
	"errors"
	"net"
	"time"

	"github.com/timo972/altv-go"
)

type PlayerConn struct {
	*PlayerReadWriteCloser
}

func (c *PlayerConn) LocalAddr() net.Addr {
	return &net.IPAddr{}
}

func (c *PlayerConn) RemoteAddr() net.Addr {
	return &net.IPAddr{
		// TODO:
		// IP: c.p.IP(),
	}
}

// TODO: respect deadlines
func (c *PlayerConn) SetDeadline(t time.Time) error {
	return errors.New("SetDeadline not implemented")
}

func (c *PlayerConn) SetReadDeadline(t time.Time) error {
	return errors.New("SetReadDeadline not implemented")
}

func (c *PlayerConn) SetWriteDeadline(t time.Time) error {
	return errors.New("SetWriteDeadline not implemented")
}

func NewPlayerConn(p altv.Player) *PlayerConn {
	return &PlayerConn{
		PlayerReadWriteCloser: PlayerRWC(p),
	}
}
