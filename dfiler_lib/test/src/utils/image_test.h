#pragma once

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "shell.h"

namespace dfiler::utils {
class ImageTest : public ::testing::Test {
 protected:
  ImageTest()
      : imageDir_(RootPath("test_data/image")), tmpDir_(std::filesystem::temp_directory_path() / "dfiler_sym") {}

  void SetUp() override { std::filesystem::create_directories(tmpDir_); }

  void TearDown() override { std::filesystem::remove_all(tmpDir_); }

  auto ImagePath(const std::string& subPath) const noexcept { return imageDir_ / subPath; }
  auto TargetPath(const std::string& subPath) const noexcept { return tmpDir_ / subPath; }

  void WriteFile(const std::filesystem::path& path, const std::string& contents) const {
    std::filesystem::create_directories(path);
    auto out = std::ofstream(path);
    out << contents;
  }

  void MakeSymlink(const std::filesystem::path& link, const std::filesystem::path& target) const {
    std::filesystem::create_symlink(target, link);
  }

 private:
  const std::filesystem::path imageDir_;
  const std::filesystem::path tmpDir_;

  static std::filesystem::path RootPath(std::string subPath) {
    auto gitRoot = execute("git rev-parse --show-toplevel");
    return std::filesystem::path(gitRoot) / subPath;
  }
};
}  // namespace dfiler::utils
