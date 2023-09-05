package cgoruntime

import (
	"bytes"
	"fmt"
	"io"
	"log"
	"os"
	"path"

	"github.com/timo972/altv-go/internal/cast"
)

func Parse(runtimePath string) (*cast.Header, []*cast.Header, error) {
	if _, err := os.Stat(runtimePath); os.IsNotExist(err) {
		return nil, nil, fmt.Errorf("runtime CAPI folder does not exist: %s", runtimePath)
	} else if err != nil {
		return nil, nil, fmt.Errorf("error checking runtime CAPI folder: %s", err)
	}

	entry := path.Join(runtimePath, "Main.h")
	capi := path.Join(runtimePath, "capi")

	// parse runtime structs
	runtimeStructs, err := os.Open(entry)
	defer runtimeStructs.Close()
	if err != nil {
		return nil, nil, fmt.Errorf("error opening runtime Main.h file: %s", err)
	}

	structbuf := &bytes.Buffer{}
	if _, err := io.Copy(structbuf, runtimeStructs); err != nil {
		return nil, nil, fmt.Errorf("error copying runtime structs to buffer: %s", err)
	}
	mainh, err := cast.ParseHeader(structbuf.Bytes(), "Main.h")
	if err != nil {
		log.Fatalf("error parsing runtime structs: %s", err)
	}

	// parse runtime capi
	headers, err := cast.ParseDirs([]string{capi})
	if err != nil {
		return nil, nil, fmt.Errorf("error parsing headers: %v", err)
	}

	return mainh, headers, nil
}
