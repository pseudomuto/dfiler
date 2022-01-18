package ui

import (
	"fmt"
	"strings"
	"time"
)

const (
	vertical   = "┃"
	horizontal = "━"
	topLeft    = "┏"
	bottomLeft = "┗"
)

// WithFrame creates a framed box that will surround the content.
func WithFrame(text string, f func(*Frame)) {
	frame := &Frame{
		startTime: time.Now(),
		tWidth:    terminalWidth(),
	}

	defer frame.Close()
	frame.Open(text)
	f(frame)
}

// Frame describes a framed UI.
type Frame struct {
	startTime time.Time
	tWidth    int
}

func frameOffset() int {
	return frameDepth * len(framePrefix)
}

// Open creates a new frame with the supplied text as a header
func (f *Frame) Open(text string) {
	out := fmt.Sprintf("%s%s %s ", Cyan(topLeft), Cyan(strings.Repeat(horizontal, 2)), Green(text))
	out = fmt.Sprintf("%s%s", out, Cyan(strings.Repeat(horizontal, f.tWidth-frameOffset()-strLen(out))))
	Println(out)

	frameDepth++
}

// Close renders the bottom of the frame including the duration it took for all code in the frame to run.
func (f *Frame) Close() {
	frameDepth--

	text := fmt.Sprintf(
		" (%s) %s",
		time.Since(f.startTime),
		Cyan(strings.Repeat(horizontal, 2)),
	)

	Print(
		"%s%s%s\n",
		Cyan(bottomLeft),
		Cyan(strings.Repeat(horizontal, f.tWidth-strLen(text)-len(bottomLeft)-frameOffset()+1)),
		text,
	)
}
