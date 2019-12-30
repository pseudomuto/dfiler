#include <dfiler/dfiler.h>
#include <gtest/gtest.h>

#include "../src/symlink_action.h"

namespace dfiler {
TEST(ActionSet, Add) {
  auto actionMap = ActionSet();
  actionMap.Add(std::make_unique<SymlinkAction>("tmp/.file1", ".file1"));
  actionMap.Add(std::make_unique<SymlinkAction>("tmp/.file2", ".file2"));

  EXPECT_EQ(2, actionMap.Size());
}

TEST(ActionSet, ForType) {
  auto actionMap = ActionSet();
  actionMap.Add(std::make_unique<SymlinkAction>("tmp/.file1", ".file1"));
  actionMap.Add(std::make_unique<SymlinkAction>("tmp/.file2", ".file2"));

  EXPECT_EQ(2, actionMap.ForType(ActionType::Symlink).size());
}
}  // namespace dfiler
