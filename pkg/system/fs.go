package system

import (
	"errors"
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
	"strings"
)

// FS defines an interface for the file system. The main purpose is to be
// able to pass in a mock when testing.
type FS interface {
	Abs(path string) string
	Exists(path string) bool
	Files(dir string) ([]string, error)
	Remove(path string) error
	Symlink(target, link string, force bool) error
	SymlinkTarget(path string) (string, error)
}

// NewFS returns an FS instance that uses the os' underlying filesystem.
func NewFS() FS {
	return &osFS{}
}

type osFS struct{}

func (o *osFS) Abs(path string) string {
	p, _ := filepath.Abs(path)
	return p
}

func (o *osFS) Exists(path string) bool {
	_, err := os.Stat(path)
	return err == nil
}

func (o *osFS) Files(dir string) ([]string, error) {
	files := []string{}

	err := filepath.WalkDir(dir, func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			return err
		}

		if !d.IsDir() {
			// add the path without the dir/ prefix
			files = append(files, strings.TrimPrefix(path, dir)[1:])
		}

		return nil
	})

	return files, wrapErr(err, "failed to walk dirctory")
}

func (o *osFS) Remove(path string) error {
	return wrapErr(os.Remove(path), "failed to remove file")
}

func (o *osFS) Symlink(target, link string, force bool) error {
	target = o.Abs(target)
	link = o.Abs(link)

	if force {
		if err := o.Remove(link); err != nil && !errors.Is(err, fs.ErrNotExist) {
			return err
		}
	}

	if err := os.MkdirAll(filepath.Dir(link), os.ModePerm); err != nil {
		return wrapErr(err, "failed to create direcrtory")
	}

	return wrapErr(os.Symlink(target, link), "failed to create symlink")
}

func (o *osFS) SymlinkTarget(path string) (string, error) {
	p, err := os.Readlink(path)
	return p, wrapErr(err, "failed to read symlink")
}

func wrapErr(err error, msg string) error {
	if err == nil {
		return nil
	}

	return fmt.Errorf(msg+": %w", err)
}
