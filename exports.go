package altv

// Export exports a value which can be imported by other resources, no matter which language. See mvalue serialization for more information about supported values.
func Export(name string, value any) error {
	return nil
}

// Import imports a value exported by another resource, no matter which language. See mvalue serialization for more information about supported values.
func Import(resourceName string, name string, out any) error {
	return nil
}
