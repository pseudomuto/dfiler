#include <gtest/gtest.h>            // for AssertionResult, SuiteApiResolver
#include <filesystem>               // for path
#include <string>                   // for allocator, operator+
#include "../src/symlink_action.h"  // for SymlinkAction
#include "dfiler/action.h"          // for ActionType, ActionType::Symlink
#include "utils/image_test.h"       // for ImageTest

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

TEST_F(SymlinkActionTest, Undo) {
  auto link = TargetPath(".gitignore");
  auto target = ImagePath(".gitignore");
  auto action = SymlinkAction(link, target);

  action.Apply();
  EXPECT_TRUE(action.IsApplied());

  action.Undo();
  EXPECT_FALSE(action.IsApplied());
}

TEST_F(SymlinkActionTest, UndoWhenNotApplied) {
  auto link = TargetPath(".gitignore");
  auto target = ImagePath(".gitignore");
  auto action = SymlinkAction(link, target);

  EXPECT_FALSE(action.IsApplied());

  // not an error condition
  action.Undo();
  EXPECT_FALSE(action.IsApplied());
}
}  // namespace dfiler
