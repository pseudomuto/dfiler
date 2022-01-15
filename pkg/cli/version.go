package cli

import (
	"github.com/spf13/cobra"
)

// Version returns a new command for displaying version info
func Version() *cobra.Command {
	return &cobra.Command{
		Use:   "version",
		Short: "show version info",
		Long:  "show version details about this executable",
		Run: func(cmd *cobra.Command, _ []string) {
			writeln(cmd, "Version: %s", cmd.Annotations["version"])
			writeln(cmd, "Build SHA: %s", cmd.Annotations["sha"])
			writeln(cmd, "Build date: %s", cmd.Annotations["date"])
		},
	}
}
