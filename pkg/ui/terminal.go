package ui

import (
	"os"

	"golang.org/x/term"
)

func terminalWidth() int {
	w, _, err := term.GetSize(int(os.Stdin.Fd()))
	if err != nil {
		return 80
	}

	return w
}
