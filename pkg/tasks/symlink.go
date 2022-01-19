package tasks

import (
	"fmt"
	"path/filepath"

	"github.com/pseudomuto/dfiler/pkg/system"
)

// NewSymlinkDir returns a task list including tasks for each file under target.
func NewSymlinkDir(fs system.FS, target, link string, force bool) (*TaskList, error) {
	paths, err := fs.Files(target)
	if err != nil {
		return nil, err
	}

	tasks := make([]Task, len(paths))
	for i, path := range paths {
		tasks[i] = NewSymlink(
			fs,
			filepath.Join(target, path),
			filepath.Join(link, path),
			force,
		)
	}

	return &TaskList{
		Name:  "Symlink dotfiles",
		Tasks: tasks,
	}, nil
}

// NewSymlink returns a Task that creates symlinks by creating the link path that points to the target path.
func NewSymlink(fs system.FS, target, link string, force bool) Task {
	return &symlink{
		fs:     fs,
		target: target,
		link:   link,
		force:  force,
	}
}

// symlink is a Task that will symlink a file
type symlink struct {
	fs     system.FS
	target string
	link   string
	force  bool
}

func (s *symlink) String() string {
	return fmt.Sprintf("Symlink %s to %s", s.link, s.target)
}

func (s *symlink) Do() error {
	return s.fs.Symlink(s.target, s.link, s.force)
}

func (s *symlink) Undo() error {
	if s.IsDone() {
		return s.fs.Remove(s.link)
	}

	return nil
}

func (s *symlink) IsDone() bool {
	dest, err := s.fs.SymlinkTarget(s.link)
	if err != nil {
		return false
	}

	return dest == s.fs.Abs(s.target)
}
