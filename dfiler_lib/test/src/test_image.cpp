#include <gtest/gtest.h>        // for AssertionResult, Message, TestPartResult
#include <memory>               // for shared_ptr
#include <set>                  // for set
#include "dfiler/action.h"      // for Action, ActionType, ActionType::Symlink
#include "dfiler/action_set.h"  // for ActionSet
#include "dfiler/image.h"       // for Image
#include "utils/image_test.h"   // for ImageTest

namespace {
class ImageTest : public ::dfiler::utils::ImageTest {};
}  // namespace

namespace dfiler {
TEST_F(ImageTest, Symlinks) {
  auto image = Image(ImagePath(""));
  auto actions = image.Apply(TargetPath(""));

  EXPECT_GT(actions.Size(), 0);

  for (const auto& action : actions.ForType(ActionType::Symlink)) {
    EXPECT_TRUE(action->IsApplied());
  }

  auto remainingActions = image.Apply(TargetPath(""));
  EXPECT_EQ(remainingActions.Size(), 0);
}

TEST_F(ImageTest, Diff) {
  auto image = Image(ImagePath(""));
  auto actions = image.Diff(TargetPath(""));
  auto symlinks = actions.ForType(ActionType::Symlink);

  EXPECT_GT(symlinks.size(), 0);
  EXPECT_LE(symlinks.size(), actions.Size());

  for (const auto& action : symlinks) {
    EXPECT_FALSE(action->IsApplied());
  }
}
}  // namespace dfiler
