package main

import "fmt"

// build variables set by ldflags
var (
	buildDate = ""
	version   = "undefined"
)

func main() {
	fmt.Println(version)
	fmt.Println(buildDate)
}
