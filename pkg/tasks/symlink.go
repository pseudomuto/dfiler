package tasks

import (
	"fmt"

	"github.com/pseudomuto/dfiler/pkg/system"
)

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
	return s.fs.Remove(s.link)
}

func (s *symlink) IsDone() bool {
	dest, err := s.fs.SymlinkTarget(s.link)
	if err != nil {
		return false
	}

	return dest == s.fs.Abs(s.target)
}
