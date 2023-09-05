package cast

import (
	"fmt"
	"testing"

	"github.com/timo972/altv-go/internal/cast/ctype"
)

func compArgs(args1, args2 []*Arg) error {
	for i, arg1 := range args1 {
		if arg1.Name != args2[i].Name {
			return fmt.Errorf("arg name at index %d unequal: %v - %v", i, arg1.Name, args2[i].Name)
		}

		if arg1.Type != args2[i].Type {
			return fmt.Errorf("arg type at index %d unequal: %v - %v", i, arg1.Type, args2[i].Type)
		}
	}

	return nil
}

func TestParseArgs(t *testing.T) {
	cases := []struct {
		expected []*Arg
		input    string
	}{
		{
			expected: []*Arg{{Name: "b", Type: ctype.VoidPtr}},
			input:    "void *b",
		},
		{
			expected: []*Arg{{Name: "b", Type: ctype.VoidPtr}},
			input:    "void* b",
		},
		{
			expected: []*Arg{{Name: "b", Type: ctype.Void}},
			input:    "void b",
		},
		{
			expected: []*Arg{{Name: "b", Type: ctype.VoidPtr}, {Name: "opacity", Type: ctype.UInt}, {Name: "duration", Type: ctype.UInt}},
			input:    "void *b, unsigned int opacity, unsigned int duration",
		},
		{
			expected: []*Arg{},
			input:    "",
		},
		{
			expected: []*Arg{},
			input:    " ",
		},
	}

	for _, c := range cases {
		args := parseArgs(c.input)

		if err := compArgs(c.expected, args); err != nil {
			t.Error(err)
		}
	}
}
