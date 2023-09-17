package cast

import (
	"regexp"
	"strings"

	"github.com/timo972/altv-go/internal/cast/ctype"
)

type Method struct {
	ReturnType ctype.Type
	Name       string
	Args       []*Arg
}

type Arg struct {
	Type ctype.Type
	Name string
}

func (m *Method) Returns() bool {
	return m.ReturnType != ctype.Void
}

func parseArgs(argstr string) []*Arg {
	if argstr == "" {
		return make([]*Arg, 0)
	}
	argstrs := strings.Split(argstr, ",")
	args := make([]*Arg, len(argstrs))

	// fmt.Printf("parsing %d args: %s (%d)\n", len(argstrs), argstr, len(argstr))

	for i, arg := range argstrs {
		fields := strings.Fields(arg)
		lastIdx := len(fields) - 1
		name := fields[lastIdx]
		typ := strings.Join(fields[:lastIdx], " ")

		// fix star on name
		if name[0] == '*' {
			name = name[1:]
			typ += " *"
		}

		// fix ptr whitespace
		if strings.HasSuffix(typ, "*") && !strings.HasSuffix(typ, " *") {
			typ = typ[:len(typ)-1] + " *"
		}

		args[i] = &Arg{
			Name: name,
			Type: ctype.Type(typ),
		}
	}

	return args
}

func parseMethods(src []byte, header *Header) error {
	r := regexp.MustCompile(`(?m)EXPORT\s([a-zA-Z0-9\s\*]{1,}[\s\*]{1,1})([A-Z]{1,1}[a-zA-Z]+_[a-zA-Z0-9]+)\(([a-zA-Z0-9\s\*\,]{0,})\);`)

	matches := r.FindAllSubmatch(src, -1)
	header.Methods = make([]*Method, len(matches))

	for i, match := range matches {
		header.Methods[i] = &Method{
			ReturnType: ctype.Type(strings.Trim(string(match[1]), " \n")),
			Name:       string(match[2]),
			Args:       parseArgs(string(match[3])),
		}
	}

	return nil
}
