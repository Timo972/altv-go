package ast

type ValueType = string

type Func struct {
	// function name
	Name string

	// return value
	ReturnValue ValueType

	// arg types
	Args []ValueType
}

type Method struct {
	Func
	// method parent
	Class string
}

type Tree struct {
	Methods []Method
	Funcs   []Func
}

func NewTree() Tree {
	return Tree{
		Methods: make([]Method, 0),
		Funcs:   make([]Func, 0),
	}
}
