load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_gazelle//:deps.bzl", "go_repository")

def install():
  _goreleaser()

def _goreleaser():
    deps = {
        "goreleaser_darwin": {
            "file": "goreleaser_Darwin_all.tar.gz",
            "sha": "d230c48bf680bfce1c70ac01a2fc29ba5fbf4ba319862cf6f1a5e3cca06f2518",
        },
        "goreleaser_linux": {
            "file": "goreleaser_Linux_x86_64.tar.gz",
            "sha": "0a05a4976b5c70c616a50ec3b823ff6745697c3b140ecfaec8f22b9d82088266",
        },
    }

    for k, v in deps.items():
      http_archive(
          name = k,
          sha256 = v["sha"],
          urls = ["https://github.com/goreleaser/goreleaser/releases/download/v1.2.5/{}".format(v["file"])],
          build_file_content = """
filegroup(
    name = "file",
    srcs = ["goreleaser"],
    visibility = ["//visibility:public"],
)
          """,
      )
