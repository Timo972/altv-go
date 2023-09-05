package main

import (
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"path"
	"strings"

	"github.com/timo972/altv-go/internal/cast/cgoruntime"
)

type stringArrayFlag []string

func (strs *stringArrayFlag) String() string {
	return strings.Join(*strs, ";")
}

func (strs *stringArrayFlag) Set(v string) error {
	*strs = append(*strs, v)
	return nil
}

func ensureFileDirs(targets []string) error {
	for _, target := range targets {
		if err := os.MkdirAll(path.Dir(target), 0755); err != nil {
			return fmt.Errorf("error ensuring %s outpout folder: %w", target, err)
		}
	}
	return nil
}

func createDst(dsts []string) (io.Writer, func(), error) {
	writers := make([]io.Writer, len(dsts))

	for i, dst := range dsts {
		f, err := os.OpenFile(dst, os.O_CREATE|os.O_TRUNC|os.O_WRONLY, 0644)
		if err != nil {
			return nil, nil, fmt.Errorf("error opening %s: %w", dst, err)
		}

		writers[i] = f
	}

	return io.MultiWriter(writers...), func() {
		for _, w := range writers {
			if f, ok := w.(*os.File); ok {
				f.Close()
			}
		}
	}, nil
}

func main() {
	log.Printf("running gencapi")

	// flag.StringVar(&runtimeStructsPath, "structs", runtimeStructsPath, "struct definitions file path")

	var coutPaths stringArrayFlag = []string{}
	var houtPaths stringArrayFlag = []string{}
	flag.Var(&coutPaths, "cout", "c body output file path")
	flag.Var(&houtPaths, "hout", "c header output file path")

	flag.Parse()

	runtimePath := flag.Arg(0)

	if len(coutPaths)+len(houtPaths) == 0 {
		coutPaths = append(coutPaths, "capi.c")
		houtPaths = append(houtPaths, "capi.h")
	}

	log.Printf("runtime path: %s", runtimePath)
	log.Printf("capi header paths: %s", houtPaths)
	log.Printf("capi body paths: %s", coutPaths)

	if err := ensureFileDirs(coutPaths); err != nil {
		log.Fatal(err)
	}

	if err := ensureFileDirs(houtPaths); err != nil {
		log.Fatal(err)
	}

	log.Printf("generating based on runtime %s", runtimePath)

	mainh, headers, err := cgoruntime.Parse(runtimePath)
	if err != nil {
		log.Fatal(err)
	}

	log.Printf("parsed %d typedefs", len(mainh.Typedefs))

	log.Printf("parsed %d CAPI files", len(headers))

	log.Printf("capi header destinations: %v", houtPaths)
	hout, closeH, err := createDst(houtPaths)
	if err != nil {
		log.Fatalf("error creating hout: %v", err)
	}

	if err = genCHead(hout, mainh, headers); err != nil {
		closeH()
		log.Fatalf("error generating capi head: %v", err)
	}
	closeH()

	log.Printf("capi body destinations: %v", coutPaths)
	cout, closeC, err := createDst(coutPaths)
	if err != nil {
		log.Fatalf("error creating cout: %v", err)
	}

	if err = genCBody(cout, headers); err != nil {
		closeC()
		log.Fatalf("error generating capi body: %v", err)
	}
	closeC()
}
