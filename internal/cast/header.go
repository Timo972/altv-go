package cast

import (
	"bytes"
	"fmt"
	"io"
	"io/fs"
	"os"
	"path/filepath"
	"strings"
)

type Header struct {
	Name     string
	Methods  []*Method
	Typedefs []*Typedef
}

func ParseHeader(src []byte, name string) (*Header, error) {
	header := &Header{
		Name: name,
	}

	if err := parseTypedefs(src, header); err != nil {
		return header, fmt.Errorf("error parsing typedefs: %w", err)
	}

	if err := parseMethods(src, header); err != nil {
		return header, fmt.Errorf("error parsing methods: %w", err)
	}

	return header, nil
}

func ParseDirs(srcs []string) ([]*Header, error) {
	hdrs := make([]*Header, 0)
	for _, src := range srcs {
		if err := filepath.WalkDir(src, func(path string, d fs.DirEntry, err error) error {
			if !strings.HasSuffix(path, ".h") {
				return nil
			}

			// fmt.Printf("parsing header %s\n", path)

			f, err := os.Open(path)
			if err != nil {
				return err
			}

			buf := &bytes.Buffer{}
			if _, err := io.Copy(buf, f); err != nil {
				return err
			}

			hdr, err := ParseHeader(buf.Bytes(), d.Name())
			if err != nil {
				return err
			}

			hdrs = append(hdrs, hdr)

			return nil
		}); err != nil {
			return nil, err
		}
	}
	return hdrs, nil
}
