package cli

import (
	"os"

	"github.com/pseudomuto/dfiler/pkg/system"
	"github.com/pseudomuto/dfiler/pkg/tasks"
	"github.com/spf13/cobra"
)

// Link defines a command for symlinking all files in a directory recursively.
func Link() *cobra.Command {
	cmd := &cobra.Command{
		Use:   "link",
		Short: "Symlink dotfiles",
		Long:  "Symlink files under target dir in link dir",
		RunE: func(cmd *cobra.Command, _ []string) error {
			source, _ := cmd.Flags().GetString("source")
			target, _ := cmd.Flags().GetString("target")
			dryRun, _ := cmd.Flags().GetBool("dryrun")
			force, _ := cmd.Flags().GetBool("force")

			fs := cmd.Context().Value(fsKey).(system.FS)
			links, err := tasks.NewSymlinkDir(fs, source, target, force)
			if err != nil {
				return err
			}

			for _, t := range links.PendingTasks() {
				write(cmd, "%s...", t.String())
				if !dryRun {
					if err := t.Do(); err != nil {
						return err
					}
				}

				write(cmd, "done\n")
			}

			return nil
		},
	}

	cmd.Flags().BoolP("dryrun", "n", false, "If set, don't create links, just pretend to")
	cmd.Flags().BoolP("force", "f", false, "Force overwriting files")
	cmd.Flags().StringP("source", "s", ".", "The source directory containing the files")
	cmd.Flags().StringP("target", "t", os.Getenv("HOME"), "The directory to put symlinks into")

	return cmd
}
