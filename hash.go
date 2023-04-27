package altv

import (
	"crypto/sha256"
)

// HashSHA256 hashes the given data using the sha256 algorithm.
func HashSHA256(data []byte) []byte {
	h := sha256.New()
	return h.Sum(data)
}

// Hash uses the case sensitive joaat algorithm to hash the given data.
func Hash(data []byte) uint32 {
	hash := uint32(0)

	for _, c := range data {
		hash += uint32(c)
		hash += hash << 10
		hash ^= hash >> 6
	}

	hash += hash << 3
	hash ^= hash >> 11
	hash += hash << 15

	return hash
}
