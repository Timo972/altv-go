package ctype

type Type string

const (
	Void    Type = "void"
	VoidPtr Type = "void *"
	UInt    Type = "unsigned int"
	Int     Type = "int"
)

func (t Type) GoType() string {
	switch t {
	case Void:
		return ""
	default:
		return ""
	}
}
