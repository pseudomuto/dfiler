#include <dfiler/dfiler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <initializer_list>
#include <memory>

#include "../../../src/cli/help_command.h"

namespace {
class OptionsTest : public ::testing::Test {
  static auto MakeArgs(std::initializer_list<const char*> args) {
    auto argc = static_cast<int>(args.size());
    auto argv = std::make_unique<char*[]>(args.size());

    auto i = 0;
    for (const auto& arg : args) {
      argv.get()[i++] = strdup(arg);
    }

    return std::make_pair(argc, argv.get());
  }

 public:
  static auto ParseCommand(std::initializer_list<const char*> args) {
    auto parsedArgs = MakeArgs(args);
    auto options = dfiler::cli::Options("dfiler", "tag line");
    return options.Parse(parsedArgs.first, parsedArgs.second);
  }
};  // namespace
}  // namespace

namespace dfiler::cli {
TEST_F(OptionsTest, HelpCommand) {
  for (const auto& opt : {"-h", "--help", "help"}) {
    auto cmd = ParseCommand({opt});
    EXPECT_TRUE(dynamic_cast<HelpCommand*>(cmd.get()));
  }
}
}  // namespace dfiler::cli
