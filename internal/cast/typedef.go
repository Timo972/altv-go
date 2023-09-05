package cast

import (
	"regexp"
)

type Typedef struct {
	Name string
	buf  []byte
}

func (t Typedef) String() string {
	return string(t.buf)
}

func parseTypedefs(src []byte, header *Header) error {
	r := regexp.MustCompile(`(?m)typedef\s[a-z]+\s[a-zA-Z0-9\s]+{[^}]+}[\s]{0,1}([a-zA-Z0-9]+);`)
	matches := r.FindAllSubmatch(src, -1)
	header.Typedefs = make([]*Typedef, len(matches))

	for i, match := range matches {
		header.Typedefs[i] = &Typedef{
			buf:  match[0],
			Name: string(match[1]),
		}
	}

	return nil
}
