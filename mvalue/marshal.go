package mvalue

import "github.com/goccy/go-json"

func Marshal(v any) ([]byte, error) {
	return json.Marshal(v)
	// return nil, nil
}
