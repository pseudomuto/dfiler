package ui_test

import (
	"bytes"
	"testing"

	"github.com/pseudomuto/dfiler/pkg/testutil"
	. "github.com/pseudomuto/dfiler/pkg/ui"
)

func TestWithFrame(t *testing.T) {
	tests := []struct {
		name string
		fn   func()
	}{
		{
			name: "single",
			fn: func() {
				WithFrame("hello there", func(f *Frame) {
					Println("Content is properly indented")
				})
			},
		},
		{
			name: "nested",
			fn: func() {
				WithFrame("hello there", func(f *Frame) {
					Println("Content is properly indented")

					WithFrame("sub-frame", func(f *Frame) {
						Println("Sub frame content")
					})
				})
			},
		},
	}

	for _, tt := range tests {
		out := new(bytes.Buffer)
		SetOut(out)
		tt.fn()

		testutil.RequireMatch(t, tt.name, out.Bytes(), testutil.StripCloseFrame)
	}
}
