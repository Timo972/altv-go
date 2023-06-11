package loginflow

import (
	"github.com/timo972/altv-go"
	"golang.org/x/exp/slices"
)

type Step[Context any] func(p altv.Player, ctx Context) error

type stepEntry[Context any] struct {
	step     Step[Context]
	priority int
}

type Flow[Context any] struct {
	steps []*stepEntry[Context]
}

func New[Context any]() *Flow[Context] {
	return &Flow[Context]{steps: make([]*stepEntry[Context], 0)}
}

func (f *Flow[Context]) Add(step Step[Context]) {
	f.AddWithPriority(step, len(f.steps))
}

func (f *Flow[Context]) AddWithPriority(step Step[Context], priority int) {
	f.steps = append(f.steps, &stepEntry[Context]{step: step, priority: priority})
}

func sortSteps[Context any](a, b *stepEntry[Context]) bool {
	return a.priority < b.priority
}

func (f *Flow[Context]) sortSteps() {
	if slices.IsSortedFunc[*stepEntry[Context]](f.steps, sortSteps[Context]) {
		return
	}
	slices.SortFunc[*stepEntry[Context]](f.steps, sortSteps[Context])
}

func (f *Flow[Context]) Run(p altv.Player, initCtx Context) error {
	f.sortSteps()

	for _, entry := range f.steps {
		err := entry.step(p, initCtx)
		if err != nil {
			return err
		}
	}

	return nil
}
