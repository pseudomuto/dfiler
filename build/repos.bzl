load("@bazel_gazelle//:deps.bzl", "go_repository")

def go_dependencies():
    _go_dependencies()

def _go_dependencies():
    go_repository(
        name = "com_github_go_logr_logr",
        build_file_generation = "on",
        build_file_proto_mode = "disable",
        importpath = "github.com/go-logr/logr",
        sum = "h1:QK40JKJyMdUDz+h+xvCsru/bJhvG0UxvePV0ufL/AcE=",
        version = "v1.2.0",
    )
    go_repository(
        name = "io_k8s_klog_v2",
        build_file_generation = "on",
        build_file_proto_mode = "disable",
        importpath = "k8s.io/klog/v2",
        sum = "h1:P4RRucWk/lFOlDdkAr3mc7iWFkgKrZY9qZMAgek06S4=",
        version = "v2.40.1",
    )
