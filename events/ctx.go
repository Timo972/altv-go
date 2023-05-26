package events

import (
	"context"
	"sync"

	"github.com/goccy/go-reflect"
	"github.com/timo972/altv-go"
	"github.com/timo972/altv-go/mvalue"
)

// #include "capi.h"
import "C"

var ctxPool = sync.Pool{New: func() any {
	return &Ctx{}
}}

var clientCtxPool = sync.Pool{New: func() any {
	return &ClientCtx{Ctx: Ctx{}}
}}

// Ctx is used as the context of script event
type Ctx struct {
	bufs [][]byte
	cache []interface{}
	ctx  context.Context
}

type ClientCtx struct {
	Ctx
	p altv.Player
}

func (c *Ctx) reset() {
	c.ctx = nil
	c.bufs = nil
	c.cache = nil
}

func (c *Ctx) defaults() {
	c.ctx = context.Background()
}

func (c *Ctx) copyArgs(cargs C.struct_array) {
	size := int(cargs.size)
	c.bufs = make([][]byte, size)
	c.cache = make([]interface{}, size)
	cbufs := (*[1<<28]C.struct_array)(cargs.array)[:size:size]

	for i := 0; i < size; i++ {
		c.bufs[i] = C.GoBytes(cbufs[i].array, C.int(cbufs[i].size))
	}
}

func (c *Ctx) Context() context.Context {
	return c.ctx
}

// Value decodes the value at index i into v
func (c *Ctx) Value(i int, v interface{}) error {
	if len(c.bufs) >= i {
		return ErrArgOutOfBounds
	}

	if c.cache[i] != nil {
		reflect.ValueNoEscapeOf(v).Set(reflect.ValueOf(c.cache[i]))
		return nil
	}

	err := mvalue.Unmarshal(c.bufs[i], v)
	if err != nil {
		return err
	}
	c.cache[i] = v
	return nil
}

func (c *ClientCtx) reset() {
	c.Ctx.reset()
	c.p = nil
}

// Player returns the player that triggered the event
func (c *ClientCtx) Player() altv.Player {
	return nil
}
