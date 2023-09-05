package main

import (
	"fmt"
	"strings"

	"github.com/timo972/altv-go/internal/casing"
	"github.com/timo972/altv-go/internal/cast"
	"github.com/timo972/altv-go/internal/cast/ctype"
)

type tmplMethod struct {
	*cast.Method
}

func (m *tmplMethod) Returns() bool {
	return m.ReturnType != ctype.Void
}

func (m *tmplMethod) CName() string {
	return casing.ToSnake(strings.ReplaceAll(m.Name, "_", ""))
}

func (m *tmplMethod) CArgs() string {
	if len(m.Args) == 0 {
		return ""
	}

	args := make([]string, len(m.Args))
	for i, arg := range m.Args {
		args[i] = fmt.Sprintf("%s %s", arg.Type, arg.Name)
	}

	return strings.Join(args, ", ")
}

func (m *tmplMethod) CArgNames() string {
	names := make([]string, len(m.Args))
	for i, arg := range m.Args {
		names[i] = arg.Name
	}

	return strings.Join(names, ",")
}

// capi.h
// method.CTypedef()
// method.CHead()

// capi.c
// method.CInit()
// method.CLoad() - inside load_module function
// method.CBody()

func (m *tmplMethod) CTypedef() string {
	// fmt.Printf("typedef: ")
	// fmt.Printf("%s", m.ReturnType)
	// fmt.Printf("%s", m.CName())
	// fmt.Printf("%v", m.Args)
	// fmt.Printf("typedef %s (*capi_%s)(%s);\n", m.ReturnType, m.CName(), m.CArgs())
	return fmt.Sprintf("typedef %s (*capi_%s)(%s);", m.ReturnType, m.CName(), m.CArgs())
}

func (m *tmplMethod) CHead() string {
	return fmt.Sprintf("%s %s(%s);", m.ReturnType, m.CName(), m.CArgs())
}

func (m *tmplMethod) CInit() string {
	return fmt.Sprintf("capi_%s g_call_%s;", m.CName(), m.CName())
}

func (m *tmplMethod) CLoad() string {
	return fmt.Sprintf("g_call_%s = GET_FUNC(module, %q, capi_%s);", m.CName(), m.Name, m.CName())
}

func (m *tmplMethod) CBody() string {
	var tmpl string
	if m.Returns() {
		tmpl = "%s %s(%s)\n{\nreturn g_call_%s(%s);\n}"
	} else {
		tmpl = "%s %s(%s)\n{\ng_call_%s(%s);\n}"
	}

	return fmt.Sprintf(tmpl, m.ReturnType, m.CName(), m.CArgs(), m.CName(), m.CArgNames())
}
