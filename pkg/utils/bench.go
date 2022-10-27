package utils

import (
	"time"

	"github.com/timo972/altv-go/pkg/alt"
)

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

// PrintMS prints the benchmark to the console in milliseconds
func (b *Benchmark) PrintMS() {
	ms := b.Elapsed.Milliseconds()
	alt.LogColored("~ly~[BENCH]", b.Name, "took:", ms, "ms")
}

// Print prints the benchmark to the console in microseconds
func (b *Benchmark) Print() {
	ms := b.Elapsed.Microseconds()
	alt.LogColored("~ly~[BENCH]", b.Name, "took:", ms, "microseconds")
}

// PrintNS prints the benchmark to the console in nanoseconds
func (b *Benchmark) PrintNS() {
	ms := b.Elapsed.Nanoseconds()
	alt.LogColored("~ly~[BENCH]", b.Name, "took:", ms, "nanoseconds")
}
