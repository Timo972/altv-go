package alt

import "fmt"

func TestResource() {
	fmt.Println("Test Resource")
	h, err = GetLibrary()

	if err != nil {
		panic(fmt.Sprintf("Failed: %v", err))
	}
}
