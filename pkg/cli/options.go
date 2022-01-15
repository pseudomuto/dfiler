package cli

import (
	"io"
	"os"

	"github.com/pseudomuto/dfiler/pkg/system"
)

type options struct {
	app       string
	buildDate string
	buildSHA  string
	version   string

	args []string
	fs   system.FS
	out  io.Writer
}

// Option defines a configuration option for the cli
type Option interface {
	apply(*options)
}

type optFunc func(*options)

func (o optFunc) apply(opts *options) { o(opts) }

func buildOptions(given []Option) *options {
	opts := &options{
		app:       "dfiler",
		buildDate: "unknown",
		buildSHA:  "unknown",
		version:   "unknown",

		args: os.Args[1:],
		fs:   system.NewFS(),
		out:  os.Stdout,
	}

	for _, opt := range given {
		opt.apply(opts)
	}

	return opts
}

func WithApp(name string) Option {
	return optFunc(func(o *options) { o.app = name })
}

func WithArgs(args ...string) Option {
	return optFunc(func(o *options) { o.args = args })
}

func WithBuildDate(buildDate string) Option {
	return optFunc(func(o *options) { o.buildDate = buildDate })
}

func WithBuildSHA(sha string) Option {
	return optFunc(func(o *options) { o.buildSHA = sha })
}

func WithFS(fs system.FS) Option {
	return optFunc(func(o *options) { o.fs = fs })
}

func WithOut(w io.Writer) Option {
	return optFunc(func(o *options) { o.out = w })
}

func WithVersion(version string) Option {
	return optFunc(func(o *options) { o.version = version })
}
