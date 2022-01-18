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
		/^[a-z0-9]+([\/]%)?([\/](%-)?[a-z0-9]+)?:.*? ##/ { printf "  $(CYAN)%-15s$(CLEAR) %s\n", $$1, $$2 } \
		/^##@/ { printf "\n$(BOLD)%s$(CLEAR)\n", substr($$0, 5) }' \
		$(MAKEFILE_LIST)

##@: Run
run: release/snapshot ## Run an interactive shell
	@docker run --rm -it \
		-v "$(PWD)/testdata/dotfiles:/source:ro" \
		pseudomuto/dfiler:latest-debug

run/release: release/snapshot ## Run the (to be released) docker image with the link command
	@docker run --rm \
		-v "$(PWD)/testdata/dotfiles:/source:ro" \
		pseudomuto/dfiler:latest \
		link

################################################################################
# Release targets for building and releasing dfiler
################################################################################
##@: Release

release/snapshot: ## Create a local release snapshot
	@bazel run //bin:goreleaser -- --snapshot --rm-dist

release/validate: ## Run goreleaser checks
	@bazel run //bin:goreleaser -- check

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
# Test targets
################################################################################
##@: Test
test: ## Run all tests
	@bazel test //...

test/%: PKG=$*
test/%: ## run tests for the specified package only (pkg/%)
	@bazel test //pkg/$(PKG):go_default_test

test/%-record: PKG=$*
test/%-record: ## run tests for the specified package and (re)record golden files (pkg/%)
	@bazel run //pkg/$(PKG):go_default_test
