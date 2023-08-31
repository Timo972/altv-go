package main

import (
	"io"
	"regexp"
)

type typedef string

func (t typedef) String() string {
	return string(t)
}

func parseTypedefs(src io.Reader) ([]typedef, error) {
	data, err := io.ReadAll(src)
	if err != nil {
		return nil, err
	}

	r := regexp.MustCompile(`(?m)typedef\s[a-z]+\s[a-zA-Z0-9\s]+{[^}]+}[\s]{0,1}[a-zA-Z0-9]+;`)
	matches := r.FindAllSubmatch(data, -1)
	typedefs := make([]typedef, len(matches))
	for i, match := range matches {
		typedefs[i] = typedef(match[0])
	}

	return typedefs, nil
}
