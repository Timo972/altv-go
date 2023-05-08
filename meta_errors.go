package altv

import "fmt"

type metaNotExistError struct {
	key string
}

func (m *metaNotExistError) Error() string {
	return fmt.Sprintf("meta key %s does not exist", m.key)
}

func IsMetaNotExist(err error) bool {
	_, ok := err.(*metaNotExistError)
	return ok
}
