#include <gtest/gtest.h>
#include <cstring>
#include <initializer_list>
#include <memory>
#include "../../../src/cli/help_command.h"
#include "../../../src/cli/symlink_command.h"
#include "dfiler/cli/options.h"

namespace {
struct Args {
  explicit Args(std::initializer_list<const char*> args)
      : argv_(new char*[args.size()]), argc_(static_cast<int>(args.size())) {
    auto i = 0;
    for (const auto& arg : args) {
      argv_.get()[i++] = strdup(arg);
    }
  }

  auto Argc() { return argc_; }
  auto Argv() { return argv_.get(); }

 private:
  int argc_;
  std::unique_ptr<char*[]> argv_;
};

class OptionsTest : public ::testing::Test {
 public:
  static auto ParseCommand(std::initializer_list<const char*> args) {
    auto mainArgs = Args(args);
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
