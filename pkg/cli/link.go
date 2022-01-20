package cli

import (
	"os"

	"github.com/pseudomuto/dfiler/pkg/system"
	"github.com/pseudomuto/dfiler/pkg/tasks"
	"github.com/pseudomuto/dfiler/pkg/ui"
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
			undo, _ := cmd.Flags().GetBool("undo")
			force, _ := cmd.Flags().GetBool("force")

			fs := cmd.Context().Value(fsKey).(system.FS)
			links, err := tasks.NewSymlinkDir(fs, source, target, force)
			if err != nil {
				return err
			}

			title := "Symlink dotfiles"
			if undo {
				title = "Remove symlinked dotfiles"
			}

			ui.WithFrame(title, func(f *ui.Frame) {
				err = tasks.RunTaskList(links, tasks.RunOptions{
					DryRun: dryRun,
					Undo:   undo,
					NoTasks: func() {
						ui.Println("Nothing to do here")
					},
					Before: func(t tasks.Task) error {
						ui.Print("%s %s...", ui.Yellow("*"), t.String())
						return nil
					},
					After: func(t tasks.Task, err error) error {
						if err != nil {
							ui.PrintlnRaw(ui.Red("FAIL"))
							return err
						}

						ui.PrintlnRaw(ui.Green("done"))
						return nil
					},
				})
			})

			return err
		},
	}

	cmd.Flags().StringP("source", "s", ".", "The source directory containing the files")
	cmd.Flags().StringP("target", "t", os.Getenv("HOME"), "The directory to put symlinks into")
	cmd.Flags().BoolP("force", "f", false, "Force overwriting files")
	cmd.Flags().BoolP("undo", "u", false, "Undo linked files (remove symlinks)")

	return cmd
}
