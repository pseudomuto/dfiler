package main

import (
	"fmt"

	"github.com/pseudomuto/dfiler/pkg/cli"
)

// auto-populated via ldflags by goreleaser
var (
	version = "dev"
	commit  = "none"
	date    = "unknown"
)

func main() {
	err := cli.Run(
		cli.WithBuildDate(date),
		cli.WithBuildSHA(commit),
		cli.WithVersion(version),
	)

	if err != nil {
		fmt.Println(err.Error())
	}
}
