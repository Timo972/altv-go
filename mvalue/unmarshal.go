package mvalue

import "github.com/goccy/go-json"

func Unmarshal(data []byte, v interface{}) error {
	return json.Unmarshal(data, v)
}
