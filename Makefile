# stamp variables
DOCKER_REGISTRY ?= k3d-registry.localhost:5000
DOCKER_REPOSITORY ?= pseudomuto/decked
VERSION ?= $(shell cat version.txt)
DOCKER_TAG ?= v$(VERSION)

BOLD = \033[1m
CLEAR = \033[0m
CYAN = \033[36m

help: ## Display this help
	@awk '\
		BEGIN {FS = ":.*##"; printf "Usage: make $(CYAN)<target>$(CLEAR)\n"} \
		/^[a-z0-9]+([\/][a-z0-9]+)?(-%)?:.*? ##/ { printf "  $(CYAN)%-15s$(CLEAR) %s\n", $$1, $$2 } \
		/^##@/ { printf "\n$(BOLD)%s$(CLEAR)\n", substr($$0, 5) }' \
		$(MAKEFILE_LIST)

##@: Build
.PHONY: build
build: ## Build the dfiler binary
	VERSION=$(VERSION) BUILD_DATE="$(shell date)" bazel build --stamp //cmd/dfiler

################################################################################
# Bazel targets for keeping things in sync
################################################################################
##@: Bazel
sync: sync/deps sync/files ## Sync dependencies and bazel files

sync/deps: ## Sync dependencies
	@go mod tidy
	@bazel run //:gazelle-update-repos

sync/files: ## Sync files (gazelle + kazel)
	@bazel run //:gazelle -- fix -external=external -go_naming_convention go_default_library
	@bazel run //build:kazel

################################################################################
# Development targets
################################################################################
##@: Dev

################################################################################
# Test targets
################################################################################
##@: Test
test: ## Run all tests
	@bazel test //...

test/pkg-%: PKG=$*
test/pkg-%: ## run tests for the specified package only
	@bazel test //pkg/$(PKG):go_default_test
