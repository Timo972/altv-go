package events

import (
	"context"
	"sync"

	"github.com/timo972/altv-go"
	"github.com/timo972/altv-go/mvalue"
)

var ctxPool = sync.Pool{New: func() any {
	return &Ctx{}
}}

var clientCtxPool = sync.Pool{New: func() any {
	return &ClientCtx{Ctx: Ctx{}}
}}

// Ctx is used as the context of script event
type Ctx struct {
	bufs [][]byte
	ctx  context.Context
}

type ClientCtx struct {
	Ctx
}

func (c *Ctx) reset() {
	c.ctx = nil
}

func (c *Ctx) defaults() {
	c.ctx = context.Background()
}

func (c *Ctx) Context() context.Context {
	return c.ctx
}

// Value decodes the value at index i into v
func (c *Ctx) Value(i int, v interface{}) error {
	if len(c.bufs) >= i {
		return ErrArgOutOfBounds
	}

	return mvalue.Unmarshal(c.bufs[i], v)
}

func (c *ClientCtx) reset() {
	c.Ctx.reset()
}

// Player returns the player that triggered the event
func (c *ClientCtx) Player() altv.Player {
	return nil
}
