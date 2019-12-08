#include <filesystem>

#include "../../src/io/symlink.h"
#include "gtest/gtest.h"

namespace {
namespace fs = std::filesystem;

class SymlinkTest : public ::testing::Test {
 protected:
  SymlinkTest() : projectDir_(fs::canonical("../../")), tmpDir_(fs::temp_directory_path() / "dfiler") {}

  void SetUp() override { fs::create_directories(tmpDir_); }

  void TearDown() override { fs::remove_all(tmpDir_); }

  std::string ProjectPath(const std::string& subPath) { return projectDir_ / subPath; }
  std::string TempPath(const std::string& subPath) { return tmpDir_ / subPath; }

 private:
  fs::path projectDir_;
  fs::path tmpDir_;
};
}  // namespace

namespace dfiler::io {
TEST_F(SymlinkTest, WhenExists) {
  auto target = ProjectPath("VERSION.txt");
  auto sLink = TempPath("VERSION.txt");
  auto link = Symlink(target, sLink);
  link.Create();

  EXPECT_TRUE(link.Exists());
}

TEST_F(SymlinkTest, WhenNotExists) {
  auto target = ProjectPath("VERSION.txt");
  auto sLink = TempPath("VERSION.txt");
  auto link = Symlink(target, sLink);
  EXPECT_FALSE(link.Exists());
}

TEST_F(SymlinkTest, FileSymlink) {
  auto target = ProjectPath(".gitignore");
  auto sLink = TempPath(".gitignore");
  auto link = Symlink(target, sLink);
  EXPECT_TRUE(link.IsFile());
  EXPECT_FALSE(link.IsDirectory());

  target = ProjectPath("cmake");
  sLink = TempPath("cmake");
  auto dirLink = Symlink(target, sLink);
  EXPECT_FALSE(dirLink.IsFile());
  EXPECT_TRUE(dirLink.IsDirectory());
}
}  // namespace dfiler::io