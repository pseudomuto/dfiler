package ui

import (
	"fmt"
	"os"
	"strings"

	"golang.org/x/term"
)

var (
	cyan   = ""
	green  = ""
	red    = ""
	reset  = ""
	yellow = ""
)

func init() {
	trm := term.NewTerminal(nil, "")
	cyan = string(trm.Escape.Cyan)
	green = string(trm.Escape.Green)
	red = string(trm.Escape.Red)
	reset = string(trm.Escape.Reset)
	yellow = string(trm.Escape.Yellow)
}

func Cyan(str string) string {
	return color(str, cyan)
}

func Green(str string) string {
	return color(str, green)
}

func Red(str string) string {
	return color(str, red)
}

func Yellow(str string) string {
	return color(str, yellow)
}

func strLen(str string) int {
	for _, code := range []string{cyan, green, yellow, reset} {
		str = strings.ReplaceAll(str, code, "")
	}

	return len(str)
}

func color(text string, code string) string {
	return fmt.Sprintf("%s%s%s", code, text, reset)
}

func terminalWidth() int {
	w, _, err := term.GetSize(int(os.Stdin.Fd()))
	if err != nil {
		return 80
	}

	return w
}
