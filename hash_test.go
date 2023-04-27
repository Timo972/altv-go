package altv

import "testing"

func TestHash(t *testing.T) {
	testCases := []struct {
		input  []byte
		output uint32
	}{
		{[]byte(""), 0},
		{[]byte("a"), 0xCA2E9442},
		{[]byte("abc"), 0xED131F5B},
		{[]byte("message digest"), 0x81D3C49B},
		{[]byte("abcdefghijklmnopqrstuvwxyz"), 0xB9F5ED0A},
		{[]byte("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), 0xf1f9a0f2},
		{[]byte("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), 0x899C6E0D},
	}

	for _, testCase := range testCases {
		result := Hash(testCase.input)
		if result != testCase.output {
			t.Errorf("Hash(%q) = 0x%x; want 0x%x", testCase.input, result, testCase.output)
		}
	}
}
