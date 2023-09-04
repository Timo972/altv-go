package cast

import "fmt"

type Header struct {
	Methods  []*Method
	Typedefs []*Typedef
}

func ParseHeader(src []byte) (*Header, error) {
	header := &Header{}

	if err := parseTypedefs(src, header); err != nil {
		return header, fmt.Errorf("error parsing typedefs: %w", err)
	}

	if err := parseMethods(src, header); err != nil {
		return header, fmt.Errorf("error parsing methods: %w", err)
	}

	return nil, nil
}
