workspace(name = "com_github_pseudomuto_dfiler")

################################################################################
# Bazel macros for downloading deps
################################################################################
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "com_google_protobuf",
    sha256 = "d0f5f605d0d656007ce6c8b5a82df3037e1d8fe8b121ed42e536f569dec16113",
    strip_prefix = "protobuf-3.14.0",
    urls = [
        "https://mirror.bazel.build/github.com/protocolbuffers/protobuf/archive/v3.14.0.tar.gz",
        "https://github.com/protocolbuffers/protobuf/archive/v3.14.0.tar.gz",
    ],
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

http_archive(
    name = "com_github_bazelbuild_buildtools",
    sha256 = "a02ba93b96a8151b5d8d3466580f6c1f7e77212c4eb181cba53eb2cae7752a23",
    strip_prefix = "buildtools-3.5.0",
    urls = [
        "https://github.com/bazelbuild/buildtools/archive/3.5.0.tar.gz",
    ],
)

################################################################################
# External Go Rules and Gazelle
################################################################################

http_archive(
    name = "io_bazel_rules_go",
    sha256 = "2b1641428dff9018f9e85c0384f03ec6c10660d935b750e3fa1492a281a53b0f",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_go/releases/download/v0.29.0/rules_go-v0.29.0.zip",
        "https://github.com/bazelbuild/rules_go/releases/download/v0.29.0/rules_go-v0.29.0.zip",
    ],
)

http_archive(
    name = "bazel_gazelle",
    sha256 = "de69a09dc70417580aabf20a28619bb3ef60d038470c7cf8442fafcf627c21cb",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-gazelle/releases/download/v0.24.0/bazel-gazelle-v0.24.0.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/v0.24.0/bazel-gazelle-v0.24.0.tar.gz",
    ],
)

load("//build:repos.bzl", "go_dependencies")
load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")
load("@bazel_gazelle//:deps.bzl", "gazelle_dependencies")

go_rules_dependencies()

go_register_toolchains(version = "1.17.2")

gazelle_dependencies()

# gazelle:repository_macro build/repos.bzl%_go_dependencies
go_dependencies()

################################################################################
# Load kubernetes repo-infra for tools like kazel
################################################################################
http_archive(
    name = "io_k8s_repo_infra",
    sha256 = "ae75a3a8de9698df30dd5a177c61f31ae9dd3a5da96ec951f0d6e60b2672d5fe",
    strip_prefix = "repo-infra-0.2.2",
    urls = ["https://github.com/kubernetes/repo-infra/archive/v0.2.2.tar.gz"],
)

################################################################################
# Support for gomock
################################################################################
# This commit is tagged as v1.3
bazel_gomock_commit = "fde78c91cf1783cc1e33ba278922ba67a6ee2a84"

http_archive(
    name = "bazel_gomock",
    sha256 = "692421b0c5e04ae4bc0bfff42fb1ce8671fe68daee2b8d8ea94657bb1fcddc0a",
    strip_prefix = "bazel_gomock-{v}".format(v = bazel_gomock_commit),
    urls = [
        "https://github.com/jmhodges/bazel_gomock/archive/{v}.tar.gz".format(v = bazel_gomock_commit),
    ],
)

################################################################################
# Install binaries from bin/deps.bzl%install
################################################################################
load("//bin:deps.bzl", install_bins = "install")

install_bins()
