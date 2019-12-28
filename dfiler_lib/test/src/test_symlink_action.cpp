#include <gtest/gtest.h>
#include <filesystem>

#include "../src/symlink_action.h"
#include "utils/image_test.h"

namespace {
class SymlinkActionTest : public dfiler::utils::ImageTest {};
}  // namespace

namespace dfiler {
TEST_F(SymlinkActionTest, Type) {
  auto action = SymlinkAction(TargetPath(".gitignore"), ImagePath(".gitignore"));
  EXPECT_EQ(ActionType::Symlink, action.Type());
}

TEST_F(SymlinkActionTest, Description) {
  auto link = TargetPath(".gitignore");
  auto target = ImagePath(".gitignore");

  auto action = SymlinkAction(link, target);
  EXPECT_EQ("Symlink " + link.string() + " to " + target.string(), action.Description());
}

TEST_F(SymlinkActionTest, Apply) {
  auto link = TargetPath(".gitignore");
  auto target = ImagePath(".gitignore");

  auto action = SymlinkAction(link, target);
  EXPECT_FALSE(action.IsApplied());

  action.Apply();
  EXPECT_TRUE(action.IsApplied());
}

TEST_F(SymlinkActionTest, IsApplied) {
  auto link = TargetPath(".gitignore");
  auto target = ImagePath(".gitignore");
  MakeSymlink(link, target);

  auto action = SymlinkAction(link, target);
  EXPECT_TRUE(action.IsApplied());
}

TEST_F(SymlinkActionTest, IsAppliedWhenNotExists) {
  auto action = SymlinkAction(ImagePath(".gitignore"), TargetPath(".gitignore"));
  EXPECT_FALSE(action.IsApplied());
}

TEST_F(SymlinkActionTest, IsAppliedWhenExistsButNotSymlink) {
  auto target = TargetPath(".gitignore");
  WriteFile(target, "# gitignore file");

  auto action = SymlinkAction(ImagePath(".gitignore"), target);
  EXPECT_FALSE(action.IsApplied());
}

TEST_F(SymlinkActionTest, IsAppliedWhenExistsButLinkedToDifferentFile) {
  auto link = TargetPath(".gitignore");
  auto target = ImagePath(".gitignore");
  MakeSymlink(link, ImagePath("dir/subdir/.file"));

  auto action = SymlinkAction(link, target);
  EXPECT_FALSE(action.IsApplied());
}
}  // namespace dfiler
