package cli_test

import (
	"testing"

	"github.com/pseudomuto/dfiler/pkg/testutil"
	"github.com/stretchr/testify/require"
)

func TestVersion(t *testing.T) {
	out, err := run("version")
	require.NoError(t, err)
	testutil.RequireMatch(t, "", out)
}
