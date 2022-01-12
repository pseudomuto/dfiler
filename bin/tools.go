//go:build tools
// +build tools

package bin

import (
	_ "k8s.io/klog/v2" // used for kazel (build time only)
)
