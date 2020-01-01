#pragma once

#include <filesystem>            // for path
#include <iosfwd>                // for ostream
#include "dfiler/cli/command.h"  // for Command

namespace dfiler::cli {
class SymlinkCommand : public Command {
 public:
  SymlinkCommand(const std::filesystem::path& sourceDir, const std::filesystem::path& targetDir_, bool dryRun = false)
      : sourceDir_(sourceDir), targetDir_(targetDir_), dryRun_(dryRun) {}

  int Execute(std::ostream& out, std::ostream& err) const override;

 private:
  bool dryRun_;
  std::filesystem::path sourceDir_;
  std::filesystem::path targetDir_;
};
}  // namespace dfiler::cli
