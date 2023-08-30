package event

import (
	"context"
	"log"
	"sync"

	"github.com/goccy/go-reflect"
	"github.com/timo972/altv-go/entity"
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
	bufs  [][]byte
	cache []interface{}
	ctx   context.Context
}

type ClientCtx struct {
	Ctx
	p entity.Player
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
	log.Printf("event::ctx::copyArgs -> array size %d", size)
	cbufs := (*[1 << 28]C.struct_array)(cargs.array)[:size:size]

	for i := 0; i < size; i++ {
		c.bufs[i] = C.GoBytes(cbufs[i].array, C.int(cbufs[i].size))
		log.Printf("event::ctx::copyArgs -> array[%d]: %+v = %s size %d === %d", i, c.bufs[i], c.bufs[i], len(c.bufs[i]), cbufs[i].size)
	}
}

func (c *Ctx) Context() context.Context {
	return c.ctx
}

// Value decodes the value at index i into v
func (c *Ctx) Value(i int, v interface{}) error {
	if len(c.bufs) <= i {
		return ErrArgOutOfBounds
	}

	if c.cache[i] != nil {
		log.Printf("event::ctx::Value (cached) -> %d: %v", i, c.cache[i])
		reflect.ValueNoEscapeOf(v).Set(reflect.ValueNoEscapeOf(c.cache[i]))
		return nil
	}

	err := mvalue.Unmarshal(c.bufs[i], v)
	if err != nil {
		return err
	}
	c.cache[i] = v

	log.Printf("event::ctx::Value -> %d: %v", i, v)

	return nil
}

// NumValue returns the number of values in the context
func (c *Ctx) NumValue() int {
	return len(c.bufs)
}

func (c *ClientCtx) reset() {
	c.Ctx.reset()
	c.p = nil
}

// Player returns the player that triggered the event
func (c *ClientCtx) Player() entity.Player {
	return c.p
}
