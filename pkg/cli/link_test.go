package cli_test

import (
	"errors"
	"path/filepath"
	"regexp"
	"testing"

	"github.com/golang/mock/gomock"
	. "github.com/pseudomuto/dfiler/pkg/cli"
	"github.com/pseudomuto/dfiler/pkg/testutil"
	"github.com/stretchr/testify/require"
)

func TestLink(t *testing.T) {
	files := []string{
		".file1",
		"file2",
		"sub/path/file3.txt",
	}

	sourceDir := "/tmp/dotfiles"
	targetDir := t.TempDir()

	ctrl := gomock.NewController(t)
	fs := NewMockFS(ctrl)

	fs.EXPECT().Files(sourceDir).Return(files, nil)
	for _, file := range files {
		fs.EXPECT().SymlinkTarget(filepath.Join(targetDir, file)).Return("", errors.New("Boom"))
		fs.EXPECT().Symlink(filepath.Join(sourceDir, file), filepath.Join(targetDir, file), true).Return(nil)
	}

	out, err := runWithOpts(
		[]Option{WithFS(fs)},
		"link",
		"-s", sourceDir,
		"-t", targetDir,
		"-f",
	)

	require.NoError(t, err)
	testutil.RequireMatch(t, "", out, testutil.StripCloseFrame, func(in string) string {
		// tmpdirs won't match so fix those up
		r := regexp.MustCompile(`/tmp/TestLink(\d+)/001`)
		return string(r.ReplaceAll([]byte(in), []byte(targetDir)))
	})
}

func TestLinkNoFiles(t *testing.T) {
	sourceDir := "/tmp/dotfiles"
	targetDir := t.TempDir()

	ctrl := gomock.NewController(t)
	fs := NewMockFS(ctrl)

	fs.EXPECT().Files(sourceDir).Return([]string{}, nil)

	out, err := runWithOpts(
		[]Option{WithFS(fs)},
		"link",
		"-s", sourceDir,
		"-t", targetDir,
		"-f",
	)

	require.NoError(t, err)
	testutil.RequireMatch(t, "", out, testutil.StripCloseFrame)
}

func TestLinkUndo(t *testing.T) {
	files := []string{
		".file1",
		"file2",
		"sub/path/file3.txt",
	}

	sourceDir := "/tmp/dotfiles"
	targetDir := t.TempDir()

	ctrl := gomock.NewController(t)
	fs := NewMockFS(ctrl)

	fs.EXPECT().Files(sourceDir).Return(files, nil)
	for _, file := range files {
		sp := filepath.Join(sourceDir, file)
		tp := filepath.Join(targetDir, file)

		// Twice because CompletedTasks and Undo both call IsDone
		fs.EXPECT().SymlinkTarget(tp).Return(sp, nil).Times(2)
		fs.EXPECT().Abs(sp).Return(sp).Times(2)

		fs.EXPECT().Remove(tp).Return(nil)
	}

	out, err := runWithOpts(
		[]Option{WithFS(fs)},
		"link",
		"-s", sourceDir,
		"-t", targetDir,
		"-u",
	)

	require.NoError(t, err)
	testutil.RequireMatch(t, "", out, testutil.StripCloseFrame, func(in string) string {
		// tmpdirs won't match so fix those up
		r := regexp.MustCompile(`/tmp/TestLinkUndo(\d+)/001`)
		return string(r.ReplaceAll([]byte(in), []byte(targetDir)))
	})
}
