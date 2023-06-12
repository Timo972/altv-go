package altnet

import (
	"bytes"
	"fmt"
	"sync"

	"github.com/timo972/altv-go"
	"github.com/timo972/altv-go/events"
)

const DefaultEventName = "altv-go:net"

var rwcs = sync.Map{}

type PlayerReadWriteCloser struct {
	p   altv.Player
	buf bytes.Buffer
}

func PlayerRWC(p altv.Player) *PlayerReadWriteCloser {
	if rwc, ok := rwcs.Load(p.ID()); ok {
		return rwc.(*PlayerReadWriteCloser)
	}

	rwc := &PlayerReadWriteCloser{
		p:   p,
		buf: bytes.Buffer{},
	}

	rwcs.Store(p.ID(), rwc)
	return rwc
}

func (rwc *PlayerReadWriteCloser) Read(b []byte) (n int, err error) {
	return rwc.buf.Read(b)
}

func (rwc *PlayerReadWriteCloser) onData(b []byte) error {
	_, err := rwc.buf.Write(b)
	return err
}

func (rwc *PlayerReadWriteCloser) Write(b []byte) (n int, err error) {
	// TODO:
	// events.EmitClientRaw(c.p, DefaultEventName, b)
	return len(b), nil
}

func (rwc *PlayerReadWriteCloser) Close() error {
	return nil
}

func init() {
	events.On.ClientEvent(DefaultEventName, func(ctx *events.ClientCtx) {
		if num := ctx.NumValue(); num != 1 {
			altv.LogWarning(fmt.Sprintf("[Go][Net] Invalid number of arguments (%d) for net event, skipping", num))
			return
		}

		var data []byte
		if err := ctx.Value(0, &data); err != nil {
			altv.LogWarning(fmt.Sprintf("[Go][Net] Invalid argument type for net event, skipping: %s", err.Error()))
			return
		}

		rwc := PlayerRWC(ctx.Player())
		if err := rwc.onData(data); err != nil {
			altv.LogWarning(fmt.Sprintf("[Go][Net] Error while writing data to rwc buffer: %s", err.Error()))
			return
		}
	})
}
