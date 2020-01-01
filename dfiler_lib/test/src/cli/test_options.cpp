#include <gtest/gtest.h>         // for AssertionResult, Message, TestPartRe...
#include <initializer_list>      // for initializer_list
#include <string>                // for string, basic_string
#include "../utils/args.h"       // for Args
#include "dfiler/cli/options.h"  // for Options

namespace {
class OptionsTest : public ::testing::Test {
 public:
  static auto ParseCommand(std::initializer_list<const char*> args) {
    auto mainArgs = dfiler::utils::Args(args);
    auto options = dfiler::cli::Options("dfiler", "tag line");
    options.Parse(mainArgs.Argc(), mainArgs.Argv());

    return options;
  }
};
}  // namespace

namespace dfiler::cli {
TEST_F(OptionsTest, HelpText) {
  auto cmd = ParseCommand({"dfiler", "-h"});
  EXPECT_GT(cmd.HelpText().size(), 0);
}

TEST_F(OptionsTest, HelpFlags) {
  auto cmd = ParseCommand({"dfiler", "-h"});
  EXPECT_TRUE(cmd.Help());
  EXPECT_EQ("", cmd.Command());
  EXPECT_EQ("", cmd.Source());
  EXPECT_EQ("", cmd.Target());
  EXPECT_FALSE(cmd.DryRun());
}

TEST_F(OptionsTest, HelpCommand) {
  auto cmd = ParseCommand({"dfiler", "help"});
  EXPECT_FALSE(cmd.Help());
  EXPECT_EQ("help", cmd.Command());
  EXPECT_EQ("", cmd.Source());
  EXPECT_EQ("", cmd.Target());
  EXPECT_FALSE(cmd.DryRun());
}

TEST_F(OptionsTest, SymlinkCommand) {
  auto cmd = ParseCommand({"dfiler", "symlink", "-s", "source", "-t", "target", "--dryrun"});
  EXPECT_EQ("symlink", cmd.Command());
  EXPECT_EQ("source", cmd.Source());
  EXPECT_EQ("target", cmd.Target());
  EXPECT_TRUE(cmd.DryRun());
  EXPECT_FALSE(cmd.Help());
}
}  // namespace dfiler::cli
