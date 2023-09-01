package main

import (
	"embed"
	"io"
	"log"
	"text/template"
)

//go:embed *.tmpl
var tmplfs embed.FS

type templateData struct {
	Methods []*method
	Structs []typedef
}

func tmplData(structs []typedef, capi map[string][]*method) *templateData {
	data := &templateData{
		Methods: make([]*method, 0),
		Structs: structs,
	}

	for _, file := range capi {
		data.Methods = append(data.Methods, file...)
	}

	return data
}

func genCHead(dst io.Writer, structs []typedef, capi []*method) error {
	tmpl, err := template.New("head.tmpl").ParseFS(tmplfs, "head.tmpl")
	if err != nil {
		return err
	}

	data := &templateData{Methods: capi, Structs: structs}
	log.Printf("writing %d typedefs and %d methods to header", len(data.Structs), len(data.Methods))

	return tmpl.Execute(dst, data)
}

func genCBody(dst io.Writer, capi []*method) error {
	tmpl, err := template.New("body.tmpl").ParseFS(tmplfs, "body.tmpl")
	if err != nil {
		return err
	}

	data := &templateData{Methods: capi}
	log.Printf("writing %d methods to body", len(data.Methods))

	return tmpl.Execute(dst, data)
}
