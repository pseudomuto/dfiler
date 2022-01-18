package cli

import (
	"context"

	"github.com/pseudomuto/dfiler/pkg/ui"
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
		Long:  "Dfile your system",
		Args:  cobra.MinimumNArgs(1),
		PersistentPreRun: func(cmd *cobra.Command, _ []string) {
			if cmd.Annotations == nil {
				cmd.Annotations = make(map[string]string)
			}

			cmd.Annotations["date"] = opts.buildDate
			cmd.Annotations["sha"] = opts.buildSHA
			cmd.Annotations["version"] = opts.version

			if dryRun, _ := cmd.Flags().GetBool("dryrun"); dryRun {
				ui.Println("")
				ui.Println("DRYRUN...nothing will be updated")
				ui.Println("")
			}
		},
		PersistentPostRun: func(cmd *cobra.Command, _ []string) {
			if dryRun, _ := cmd.Flags().GetBool("dryrun"); dryRun {
				ui.Println("")
				ui.Println("DRYRUN...nothing was updated")
			}
		},
	}

	cmd.PersistentFlags().BoolP("dryrun", "n", false, "If set, just pretend to update things")
	cmd.AddCommand(Link(), Version())
	cmd.SetArgs(opts.args)

	ui.SetOut(opts.out)
	cmd.SetOut(ui.GetOut())

	ctx := context.WithValue(context.Background(), fsKey, opts.fs)
	return cmd.ExecuteContext(ctx)
}
