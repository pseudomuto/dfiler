package cli

import (
	"context"
	"fmt"

	"github.com/spf13/cobra"
)

type contextKey string

const (
	fsKey contextKey = "fs"
)

// Run runs the CLI
func Run(options ...Option) error {
	opts := buildOptions(options)

	cmd := &cobra.Command{
		Use:   opts.app,
		Short: "Do something with dfiler",
		Long:  "Defile your filesystem",
		Args:  cobra.MinimumNArgs(1),
		PersistentPreRun: func(cmd *cobra.Command, _ []string) {
			if cmd.Annotations == nil {
				cmd.Annotations = make(map[string]string)
			}

			cmd.Annotations["date"] = opts.buildDate
			cmd.Annotations["sha"] = opts.buildSHA
			cmd.Annotations["version"] = opts.version
		},
	}

	cmd.AddCommand(Link(), Version())
	cmd.SetArgs(opts.args)
	cmd.SetOut(opts.out)

	ctx := context.WithValue(context.Background(), fsKey, opts.fs)
	return cmd.ExecuteContext(ctx)
}

func write(cmd *cobra.Command, msg string, args ...interface{}) {
	fmt.Fprintf(cmd.OutOrStdout(), msg, args...)
}

func writeln(cmd *cobra.Command, msg string, args ...interface{}) {
	write(cmd, msg+"\n", args...)
	fmt.Fprintf(cmd.OutOrStdout(), msg+"\n", args...)
}
