package system_test

import (
	"path/filepath"
	"sort"
	"testing"

	. "github.com/pseudomuto/dfiler/pkg/system"
	"github.com/stretchr/testify/require"
)

func TestFSSymlink(t *testing.T) {
	dir := t.TempDir()
	fs := NewFS()

	tests := []struct {
		name   string
		target string
	}{
		{name: "top-level file", target: filepath.Join("testdata", "target.txt")},
		{name: "nested file", target: filepath.Join("testdata", "sub", "sub", "test.txt")},
	}

	for _, tt := range tests {
		link := filepath.Join(dir, tt.name)
		require.False(t, fs.Exists(link))

		require.NoError(t, fs.Symlink(tt.target, link, false))
		require.True(t, fs.Exists(link))

		target, err := fs.SymlinkTarget(link)
		require.NoError(t, err)
		require.Equal(t, fs.Abs(tt.target), target)
	}

	t.Run("with force", func(t *testing.T) {
		target := filepath.Join("testdata", "target.txt")
		link := filepath.Join(dir, "oops")
		require.NoError(t, fs.Symlink(target, link, true))
		require.Error(t, fs.Symlink(target, link, false))

		target = filepath.Join("testdata", "sub", "sub", "test.txt")
		require.NoError(t, fs.Symlink(target, link, true))
	})
}

func TestFSFiles(t *testing.T) {
	expected := []string{
		"target.txt",
		"sub/sub/test.txt",
	}

	// implementation detail: WalkDir walks files in lexical order
	// https://pkg.go.dev/path/filepath#WalkDir
	sort.Strings(expected)

	files, err := NewFS().Files("testdata")
	require.NoError(t, err)
	require.Equal(t, expected, files)
}
