package cli_test

import (
	"testing"

	"github.com/stretchr/testify/require"
)

func TestVersion(t *testing.T) {
	out, err := run("version")
	require.NoError(t, err)
	require.Contains(t, out, "Version: 0.1.0-alpha")
	require.Contains(t, out, "Build SHA: 123abc")
	require.Contains(t, out, "Build date: right now")
}
