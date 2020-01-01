#include <gtest/gtest.h>                    // for Test, EXPECT_EQ, Message
#include <sstream>                          // for basic_ostringstream, ostr...
#include "../../../src/cli/help_command.h"  // for HelpCommand

namespace dfiler::cli {
TEST(HelpCommand, WhenCalledExplicitly) {
  auto out = std::ostringstream();
  auto err = std::ostringstream();
  auto code = HelpCommand("helpText").Execute(out, err);

  EXPECT_EQ(0, code);
  EXPECT_EQ("helpText\n", out.str());
  EXPECT_EQ("", err.str());
}

TEST(HelpCommand, WhenCalledDueToError) {
  auto out = std::ostringstream();
  auto err = std::ostringstream();
  auto code = HelpCommand("helpText", true).Execute(out, err);

  EXPECT_EQ(1, code);
  EXPECT_EQ("", out.str());
  EXPECT_EQ("helpText\n", err.str());
}
}  // namespace dfiler::cli
