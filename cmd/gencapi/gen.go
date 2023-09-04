package main

import (
	"embed"
	"io"
	"log"
	"text/template"

	"github.com/timo972/altv-go/internal/cast"
)

//go:embed *.tmpl
var tmplfs embed.FS

type templateData struct {
	Methods []*tmplMethod
	Structs []*cast.Typedef
}

func mapHeaders(hdrs []*cast.Header) []*tmplMethod {
	methods := make([]*tmplMethod, 0)
	for _, hdr := range hdrs {
		for _, m := range hdr.Methods {
			methods = append(methods, &tmplMethod{
				Method: m,
			})
		}
	}
	return methods
}

func genCHead(dst io.Writer, structs *cast.Header, capi []*cast.Header) error {
	tmpl, err := template.New("head.tmpl").ParseFS(tmplfs, "head.tmpl")
	if err != nil {
		return err
	}

	data := &templateData{Methods: mapHeaders(capi), Structs: structs.Typedefs}
	log.Printf("writing %d typedefs and %d methods to header", len(data.Structs), len(data.Methods))

	return tmpl.Execute(dst, data)
}

func genCBody(dst io.Writer, capi []*cast.Header) error {
	tmpl, err := template.New("body.tmpl").ParseFS(tmplfs, "body.tmpl")
	if err != nil {
		return err
	}

	data := &templateData{Methods: mapHeaders(capi)}
	log.Printf("writing %d methods to body", len(data.Methods))

	return tmpl.Execute(dst, data)
}
