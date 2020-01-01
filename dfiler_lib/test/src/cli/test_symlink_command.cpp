#include <gtest/gtest.h>
#include "../../../src/cli/symlink_command.h"

namespace dfiler::cli {
TEST(SymlinkCommand, NormalCall) {
  auto out = std::ostringstream();
  auto err = std::ostringstream();
  auto code = SymlinkCommand("source", "target").Execute(out, err);

  EXPECT_EQ(0, code);
  EXPECT_EQ("Creating symlinks\n", out.str());
  EXPECT_EQ("", err.str());
}

TEST(SymlinkCommand, DryRun) {
  auto out = std::ostringstream();
  auto err = std::ostringstream();
  auto code = SymlinkCommand("source", "target", true).Execute(out, err);

  EXPECT_EQ(0, code);
  EXPECT_EQ("Creating symlinks\nDRY RUN: No symlinks will be created.\n", out.str());
  EXPECT_EQ("", err.str());
}
}  // namespace dfiler::cli
