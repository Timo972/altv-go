package main

import (
	"fmt"
	"io"
	"io/fs"
	"log"
	"regexp"
	"strings"
)

type method struct {
	returnType  string
	className   string
	classMethod string
	args        []string
}

func (m *method) Returns() bool {
	return m.returnType != "void"
}

func (m *method) Name() string {
	return fmt.Sprintf("%s_%s", m.className, m.classMethod)
}

func (m *method) CName() string {
	return ToSnakeCase(m.className + m.classMethod)
}

func (m *method) CArgs() string {
	if len(m.args) == 0 {
		return ""
	}

	return strings.Join(m.args, ", ")
}

func (m *method) CArgNames() string {
	vnames := make([]string, len(m.args))
	for i, arg := range m.args {
		vname := arg[strings.LastIndex(arg, " ")+1:]
		if vname[0] == '*' {
			vname = vname[1:]
		}
		vnames[i] = vname
	}

	return strings.Join(vnames, ",")
}

// capi.h
// method.CTypedef()
// method.CHead()

// capi.c
// method.CInit()
// method.CLoad() - inside load_module function
// method.CBody()

func (m *method) CTypedef() string {
	return fmt.Sprintf("typedef %s (*capi_%s)(%s);", m.returnType, m.CName(), m.CArgs())
}

func (m *method) CHead() string {
	return fmt.Sprintf("%s %s(%s);", m.returnType, m.CName(), m.CArgs())
}

func (m *method) CInit() string {
	return fmt.Sprintf("capi_%s g_call_%s;", m.CName(), m.CName())
}

func (m *method) CLoad() string {
	return fmt.Sprintf("g_call_%s = GET_FUNC(module, %q, capi_%s);", m.CName(), m.Name(), m.CName())
}

func (m *method) CBody() string {
	var tmpl string
	if m.Returns() {
		tmpl = "%s %s(%s)\n{\nreturn g_call_%s(%s);\n}"
	} else {
		tmpl = "%s %s(%s)\n{\ng_call_%s(%s);\n}"
	}

	return fmt.Sprintf(tmpl, m.returnType, m.CName(), m.CArgs(), m.CName(), m.CArgNames())
}

func parseMethodArgs(argstr string) []string {
	argstr = strings.Trim(argstr, " ")
	if argstr == "" {
		return make([]string, 0)
	}
	return strings.Split(argstr, ",")
}

func parseMethods(src io.Reader) ([]*method, error) {
	data, err := io.ReadAll(src)
	if err != nil {
		return nil, err
	}

	r := regexp.MustCompile(`(?m)EXPORT\s([a-zA-Z0-9\s\*]{1,}[\s\*]{1,1})([A-Z]{1,1}[a-zA-Z]+)_([a-zA-Z0-9]+)\(([a-zA-Z0-9\s\*\,]{0,})\);`)

	matches := r.FindAllSubmatch(data, -1)

	methods := make([]*method, len(matches))
	for i, match := range matches {
		methods[i] = &method{
			returnType:  strings.Trim(string(match[1]), " "),
			className:   string(match[2]),
			classMethod: string(match[3]),
			args:        parseMethodArgs(string(match[4])),
		}
	}

	return methods, nil
}

func parseCAPIDir(runtimeCAPI fs.FS) (map[string][]*method, error) {
	capiMethods := make(map[string][]*method)
	if err := fs.WalkDir(runtimeCAPI, ".", func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			return err
		}

		if d.IsDir() {
			return nil
		}

		// only process headers
		if !strings.HasSuffix(path, ".h") {
			return nil
		}

		h, err := runtimeCAPI.Open(path)
		if err != nil {
			return fmt.Errorf("error opening %s: %w", path, err)
		}

		methods, err := parseMethods(h)
		if err != nil {
			return err
		}

		log.Printf("%s: %d methods", path, len(methods))
		capiMethods[path] = methods

		return nil
	}); err != nil {
		return nil, fmt.Errorf("error walking runtime CAPI folder: %s", err)
	}

	return capiMethods, nil
}
