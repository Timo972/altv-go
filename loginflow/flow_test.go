package loginflow_test

import (
	"fmt"

	"github.com/timo972/altv-go"
	"github.com/timo972/altv-go/loginflow"
	"github.com/timo972/altv-go/test"
)

type MyCtx struct {
	Status int
}

func Example() {
	flow := loginflow.New[*MyCtx]()

	flow.Add(func(p altv.Player, ctx *MyCtx) error {
		fmt.Printf("Hello %d\n", p.ID())
		ctx.Status = 1
		return nil
	})

	flow.Add(func(p altv.Player, ctx *MyCtx) error {
		fmt.Printf("Checking if %d is banned, status: %d\n", p.ID(), ctx.Status)
		ctx.Status = 2
		return nil
	})

	p := test.NewPlayer(1)
	ctx := &MyCtx{}
	if err := flow.Run(p, ctx); err != nil {
		// p.Kick("Failed to login")
		fmt.Printf("Failed to login: %s\n", err)
	}
	fmt.Printf("Player %d logged in, status: %d\n", p.ID(), ctx.Status)

	// Output:
	// Hello 1
	// Checking if 1 is banned, status: 1
	// Player 1 logged in, status: 2
}
