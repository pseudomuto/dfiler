#pragma once

#include <filesystem>            // for path
#include <iosfwd>                // for ostream
#include <type_traits>           // for move
#include "dfiler/cli/command.h"  // for Command

namespace dfiler::cli {
class SymlinkCommand : public Command {
 public:
  SymlinkCommand(std::filesystem::path sourceDir, std::filesystem::path targetDir_, bool dryRun = false)
      : sourceDir_(std::move(sourceDir)), targetDir_(std::move(targetDir_)), dryRun_(dryRun) {}

  int Execute(std::ostream& out, std::ostream& err) const override;

  auto IsDryRun() const noexcept { return dryRun_; }
  auto SourceDir() const noexcept { return sourceDir_; }
  auto TargetDir() const noexcept { return targetDir_; }

 private:
  bool dryRun_;
  std::filesystem::path sourceDir_;
  std::filesystem::path targetDir_;
};
}  // namespace dfiler::cli
