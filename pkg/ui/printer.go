package ui

import (
	"bytes"
	"fmt"
	"io"
	"os"
	"strings"
)

var (
	// frameDepth keeps track of how many frames we're in. Messages are prefixed
	// with the corresponding number of frame prefixes.
	frameDepth = 0

	framePrefix = fmt.Sprintf("%s ", vertical)

	// the writer to use for printing
	outWriter *printer = &printer{w: os.Stdout}
)

func GetOut() io.Writer {
	return outWriter
}

type printer struct {
	w io.Writer
}

func (p *printer) Write(content []byte) (int, error) {
	n := 0
	if bytes.Index(content, []byte("{{raw}}")) == 0 {
		content = content[len("{{raw}}"):]
	} else {
		if n, err := p.w.Write([]byte(strings.Repeat(framePrefix, frameDepth))); err != nil {
			return n, err
		}
	}

	m, err := p.w.Write(content)
	return n + m, err
}

func SetOut(w io.Writer) {
	outWriter = &printer{w: w}
}

func Print(msg string, args ...interface{}) {
	fmt.Fprintf(outWriter, msg, args...)
}

func Println(msg string, args ...interface{}) {
	Print(msg+"\n", args...)
}

func PrintRaw(msg string, args ...interface{}) {
	fmt.Fprintf(outWriter, "{{raw}}"+msg, args...)
}

func PrintlnRaw(msg string, args ...interface{}) {
	PrintRaw(msg+"\n", args...)
}
