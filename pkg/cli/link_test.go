package cli_test

import (
	"errors"
	"fmt"
	"path/filepath"
	"testing"

	"github.com/golang/mock/gomock"
	. "github.com/pseudomuto/dfiler/pkg/cli"
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
	for _, file := range files {
		require.Contains(t, out, fmt.Sprintf(
			"Symlink %s to %s...done",
			filepath.Join(targetDir, file),
			filepath.Join(sourceDir, file),
		))
	}
}
