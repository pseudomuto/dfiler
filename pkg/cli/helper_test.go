package cli_test

import (
	"bytes"

	. "github.com/pseudomuto/dfiler/pkg/cli"
)

const (
	testDate    = "right now"
	testSHA     = "123abc"
	testVersion = "0.1.0-alpha"
)

func run(args ...string) ([]byte, error) {
	return runWithOpts([]Option{}, args...)
}

func runWithOpts(opts []Option, args ...string) ([]byte, error) {
	out := bytes.NewBufferString("")
	// set some sane defaults for testing. These ones can't be overridden so
	// this list should be just the absolute essentials
	opts = append(
		opts,
		WithArgs(args...),
		WithBuildDate(testDate),
		WithBuildSHA(testSHA),
		WithVersion(testVersion),
		WithOut(out),
	)

	if err := Run(opts...); err != nil {
		return nil, err
	}

	return out.Bytes(), nil
}
