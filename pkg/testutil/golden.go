package testutil

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"github.com/stretchr/testify/require"
)

// RequireMatch ensures that the given content matches what's found in the golden file. The golden
// file's name is determined based on asset in the form `testdata/{{.asset}}.{{.testname}}.golden`.
//
// To update golden files, simply use bazel run instead of bazel test (see Makefile).
func RequireMatch(t *testing.T, asset string, content []byte, adapters ...func(in string) string) {
	update := false
	path := "testdata"

	if dir, ok := os.LookupEnv("BUILD_WORKSPACE_DIRECTORY"); ok {
		update = true
		bin := os.Getenv("TEST_BINARY")
		path = filepath.Join(
			dir,
			bin[:strings.Index(bin, "go_default_test_/")],
			path,
		)
	}

	path = filepath.Join(path, fmt.Sprintf("%s.%s.golden", t.Name(), asset))
	path = strings.Replace(path, "..", ".", -1)

	if update {
		require.NoError(t, os.MkdirAll(filepath.Dir(path), os.ModePerm))
		require.NoError(t, os.WriteFile(path, content, 0644))
	}

	raw, err := os.ReadFile(path)
	require.NoError(t, err)

	exp := string(raw)
	act := string(content)
	for _, adapter := range adapters {
		exp = adapter(exp)
		act = adapter(act)
	}

	require.Equal(t, exp, act)
}

// StripCloseFrame removes closing frame lines since they include durations
// which will cause flakiness in tests
func StripCloseFrame(out string) string {
	return out[:strings.Index(out, "┗")]
}
