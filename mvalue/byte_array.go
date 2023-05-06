package mvalue

import "github.com/goccy/go-json"

// ByteArray is a wrapper for byte slices. Use this if you want to send byte slices to the client. If you send a byte slice without this wrapper, it will be converted to a string.
type ByteArray struct {
	json.Marshaler
	json.Unmarshaler

	Data []byte
}

type byteArray struct {
	SpecialType
	Data []byte `json:"data"`
}

var resourceName string

func (b ByteArray) MarshalJSON() ([]byte, error) {
	return json.Marshal(byteArray{
		Data: b.Data,
		SpecialType: SpecialType{
			Type: TypeByteArray,
		},
	})
}

func (b *ByteArray) UnmarshalJSON(raw []byte) error {
	var data byteArray
	if err := json.Unmarshal(raw, &data); err != nil {
		return err
	}

	b.Data = data.Data
	return nil
}
