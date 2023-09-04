package main

import (
	"bytes"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"path"
	"strings"

	"github.com/timo972/altv-go/internal/cast"
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

	runtimeCAPIPath := flag.Arg(0)
	var runtimeStructsPath = path.Join(path.Dir(runtimeCAPIPath), "Main.h")

	if len(coutPaths)+len(houtPaths) == 0 {
		coutPaths = append(coutPaths, "capi.c")
		houtPaths = append(houtPaths, "capi.h")
	}

	log.Printf("runtime CAPI path: %s", runtimeCAPIPath)
	log.Printf("runtime structs path: %s", runtimeStructsPath)
	log.Printf("capi header paths: %s", houtPaths)
	log.Printf("capi body paths: %s", coutPaths)

	if _, err := os.Stat(runtimeCAPIPath); os.IsNotExist(err) {
		log.Fatalf("runtime CAPI folder does not exist: %s", runtimeCAPIPath)
	} else if err != nil {
		log.Fatalf("error checking runtime CAPI folder: %s", err)
	}

	if err := ensureFileDirs(coutPaths); err != nil {
		log.Fatal(err)
	}

	if err := ensureFileDirs(houtPaths); err != nil {
		log.Fatal(err)
	}

	log.Printf("generating CAPI files from %s and struct defs from %s", runtimeCAPIPath, runtimeStructsPath)

	// parse runtime structs
	runtimeStructs, err := os.Open(runtimeStructsPath)
	if err != nil {
		runtimeStructs.Close()
		log.Fatalf("error opening runtime structs file: %s", err)
	}

	structbuf := &bytes.Buffer{}
	if _, err := io.Copy(structbuf, runtimeStructs); err != nil {
		runtimeStructs.Close()
		log.Fatalf("error copying runtime structs to buffer: %s", err)
	}
	mainh, err := cast.ParseHeader(structbuf.Bytes(), "Main.h")
	if err != nil {
		log.Fatalf("error parsing runtime structs: %s", err)
	}
	log.Printf("parsed %d typedefs", len(mainh.Typedefs))

	// parse runtime capi
	headers, err := cast.ParseDirs([]string{runtimeCAPIPath})
	if err != nil {
		log.Fatalf("error parsing headers: %v", err)
	}
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
