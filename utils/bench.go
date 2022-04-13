package utils

import "time"
import "github.com/timo972/altv-go-pkg/alt"

type Benchmark struct {
	Name    string
	Begin   time.Time
	End     time.Time
	Elapsed time.Duration
}

func NewBenchmark(name string) *Benchmark {
	return &Benchmark{
		Name: name,
	}
}

func (b *Benchmark) Start() {
	b.Begin = time.Now()
}

func (b *Benchmark) Stop() {
	b.End = time.Now()

	b.Elapsed = b.End.Sub(b.Begin)
}

func (b *Benchmark) Print() {
	ms := b.Elapsed.Milliseconds()
	alt.LogColored("~ly~[BENCH] ", b.Name, " took: ", ms, "ms")
}
