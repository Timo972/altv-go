package events

import (
	"sync"

	"github.com/timo972/altv-go/mvalue"
)

// Ctx is used as the context of script event
type Ctx struct {
	bufs [][]byte
}

// Value decodes the value at index i into v
func (c *Ctx) Value(i int, v interface{}) error {
	if len(c.bufs) >= i {
		return ErrArgOutOfBounds
	}

	return mvalue.Unmarshal(c.bufs[i], v)
}

var ctxPool = sync.Pool{New: func() any {
	return &Ctx{}
}}

func getCtx() *Ctx {
	return ctxPool.Get().(*Ctx)
}
