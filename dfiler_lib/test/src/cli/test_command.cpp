#include <gtest/gtest.h>                       // for AssertionResult, Suite...
#include <initializer_list>                    // for initializer_list
#include <memory>                              // for unique_ptr
#include <string>                              // for string
#include "../../../src/cli/help_command.h"     // for HelpCommand
#include "../../../src/cli/symlink_command.h"  // for SymlinkCommand
#include "../utils/args.h"                     // for Args
#include "dfiler/cli/command.h"                // for Command
#include "dfiler/cli/options.h"                // for Options

namespace {
class CommandTest : public ::testing::Test {
 public:
  static auto ParseCommand(std::initializer_list<const char*> args) {
    auto mainArgs = dfiler::utils::Args(args);
    auto options = dfiler::cli::Options("dfiler", "tag line");
    options.Parse(mainArgs.Argc(), mainArgs.Argv());

    return dfiler::cli::Command::FromOptions(options);
  }
};
}  // namespace

namespace dfiler::cli {
TEST_F(CommandTest, ParsesHelpCommand) {
  auto cmd = dynamic_cast<HelpCommand*>(ParseCommand({"dfiler", "-h"}).get());
  EXPECT_GT(cmd->HelpText().length(), 0);
  EXPECT_FALSE(cmd->IsError());

  cmd = dynamic_cast<HelpCommand*>(ParseCommand({"dfiler", "--help"}).get());
  EXPECT_GT(cmd->HelpText().length(), 0);
  EXPECT_FALSE(cmd->IsError());

  cmd = dynamic_cast<HelpCommand*>(ParseCommand({"dfiler", "help"}).get());
  EXPECT_GT(cmd->HelpText().length(), 0);
  EXPECT_FALSE(cmd->IsError());
}

TEST_F(CommandTest, ParsesUnknownToHelpCommand) {
  auto cmd = dynamic_cast<HelpCommand*>(ParseCommand({"dfiler", "wtfisthis"}).get());
  EXPECT_TRUE(cmd->IsError());
}

TEST_F(CommandTest, ParsesSymlinkCommand) {
  auto args = {"dfiler", "symlink", "-s", "source", "-t", "target", "--dryrun"};
  auto cmd = dynamic_cast<SymlinkCommand*>(ParseCommand(args).get());
  EXPECT_EQ("source", cmd->SourceDir());
  EXPECT_EQ("target", cmd->TargetDir());
  EXPECT_TRUE(cmd->IsDryRun());
}
}  // namespace dfiler::cli
