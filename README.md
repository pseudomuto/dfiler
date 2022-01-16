# Dfiler

[![CI](https://github.com/pseudomuto/dfiler/actions/workflows/ci.yaml/badge.svg?branch=main)](https://github.com/pseudomuto/dfiler/actions/workflows/ci.yaml)

A tool for managing dotfiles, packages, and settings for 'nix systems. This is very much a WIP.

## Contributing

In order to contribute you'll need bazel installed. The rest should be handled for you.

* View make targets - `make help`
* Run tests - `make test`
* Test a package under ./pkg - `make test/pkg-<name>` (e.g make `test/pkg-cli`)
