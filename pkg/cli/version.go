package cli

import (
	"github.com/pseudomuto/dfiler/pkg/ui"
	"github.com/spf13/cobra"
)

// Version returns a new command for displaying version info
func Version() *cobra.Command {
	return &cobra.Command{
		Use:   "version",
		Short: "show version info",
		Long:  "show version details about this executable",
		Run: func(cmd *cobra.Command, _ []string) {
			ui.Println("Version: %s", cmd.Annotations["version"])
			ui.Println("Build SHA: %s", cmd.Annotations["sha"])
			ui.Println("Build date: %s", cmd.Annotations["date"])
		},
	}
}
