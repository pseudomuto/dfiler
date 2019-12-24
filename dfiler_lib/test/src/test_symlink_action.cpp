#include <gtest/gtest.h>
#include <filesystem>

#include "../src/symlink_action.h"
#include "utils/image_test.h"

namespace {
class SymlinkActionTest : public dfiler::utils::ImageTest {};
}  // namespace

namespace dfiler {
TEST_F(SymlinkActionTest, Meet) {
  auto link = TargetPath(".gitignore");
  auto target = ImagePath(".gitignore");

  auto action = SymlinkAction(link, target);
  EXPECT_FALSE(action.IsMet());

  action.Meet();
  EXPECT_TRUE(action.IsMet());
}

TEST_F(SymlinkActionTest, IsMet) {
  auto link = TargetPath(".gitignore");
  auto target = ImagePath(".gitignore");
  MakeSymlink(link, target);

  auto action = SymlinkAction(link, target);
  EXPECT_TRUE(action.IsMet());
}

TEST_F(SymlinkActionTest, IsMetWhenNotExists) {
  auto action = SymlinkAction(ImagePath(".gitignore"), TargetPath(".gitignore"));
  EXPECT_FALSE(action.IsMet());
}

TEST_F(SymlinkActionTest, IsMetWhenExistsButNotSymlink) {
  auto target = TargetPath(".gitignore");
  WriteFile(target, "# gitignore file");

  auto action = SymlinkAction(ImagePath(".gitignore"), target);
  EXPECT_FALSE(action.IsMet());
}

TEST_F(SymlinkActionTest, IsMetWhenExistsButLinkedToDifferentFile) {
  auto link = TargetPath(".gitignore");
  auto target = ImagePath(".gitignore");
  MakeSymlink(link, ImagePath("dir/subdir/.file"));

  auto action = SymlinkAction(link, target);
  EXPECT_FALSE(action.IsMet());
}
}  // namespace dfiler
