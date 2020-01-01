#include <gtest/gtest.h>            // for Test, SuiteApiResolver, TestInfo ...
#include <memory>                   // for make_unique
#include <set>                      // for set
#include "../src/symlink_action.h"  // for SymlinkAction
#include "dfiler/action.h"          // for Action, ActionType, ActionType::S...
#include "dfiler/action_set.h"      // for ActionSet

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
