package main

import (
	"embed"
	"flag"
	"fmt"
	"log"
	"os"
	"strings"
	"text/template"

	"github.com/timo972/altv-go/internal/cast"
	"github.com/timo972/altv-go/internal/cast/cgoruntime"
)

//go:embed *.tmpl
var tmplfs embed.FS


func conventifyName(method string) string {
	var name string
	if strings.HasPrefix(method, "Get") {
		name = method[3:]
	} else {
		name = method
	}

	return name
}

type tmplMethod struct {
	*cast.Method
}

func (t *tmplMethod) StructName() string {
	parts := strings.SplitN(t.Name, "_", 2)
	return fmt.Sprintf("Alt%s", parts[0])
}

func (t *tmplMethod) FuncName() string {
	parts := strings.SplitN(t.Name, "_", 2)
	return conventifyName(parts[1])
}

func (t *tmplMethod) GoArgs() string {
	argstr := ""
	for _, arg := range t.Args {
		arg.
	}
}

func (t *tmplMethod) GoBody() string {

}

func (t *tmplMethod) Return() string {
	if !t.Returns() {
		return ""
	}

	return string(t.ReturnType)
}

func main() {
	log.Printf("running gentity - generate entity api")
	flag.Parse()

	runtimePath := flag.Arg(0)
	log.Printf("runtime path: %s", runtimePath)

	entityPkgPath := flag.Arg(1)
	log.Printf("entity pkg path: %s", entityPkgPath)

	structs, methods, err := cgoruntime.Parse(runtimePath)
	if err != nil {
		log.Fatal(err)
	}

	log.Printf("found %d structs and %d capi headers", len(structs.Typedefs), len(methods))

	for _, hdr := range methods {
		tmplMethods := make([]*tmplMethod, len(hdr.Methods))
		for i, method := range hdr.Methods {
			tmplMethods[i] = &tmplMethod{Method: method}
		}

		tmpl, err := template.New("entity.tmpl").ParseFS(tmplfs, "entity.tmpl")
		if err != nil {
			log.Fatal(err)
		}

		f, err := os.OpenFile(fmt.Sprintf("./entity/test/%s_gen.go", strings.ToLower(hdr.Name)), os.O_CREATE|os.O_TRUNC|os.O_WRONLY, 0644)
		if err != nil {
			f.Close()
			log.Fatal(err)
		}

		if err := tmpl.Execute(f, map[string]any{"Methods": tmplMethods}); err != nil {
			f.Close()
			log.Fatal(err)
		}
	}
}
