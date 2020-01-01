#pragma once

#include <string>       // for string
#include <type_traits>  // for move

namespace dfiler::cli {
class Options {
 public:
  explicit Options(std::string name, std::string description)
      : name_(std::move(name)),
        description_(std::move(description)),
        command_(""),
        source_(""),
        target_(""),
        helpText_(),
        help_(false),
        dryRun_(false){};

  void Parse(int argc, char** argv);

  auto Command() const noexcept { return command_; }
  auto Source() const noexcept { return source_; }
  auto Target() const noexcept { return target_; }
  auto HelpText() const noexcept { return helpText_; }
  auto Help() const noexcept { return help_; }
  auto DryRun() const noexcept { return dryRun_; }

 private:
  const std::string name_;
  const std::string description_;

  std::string command_;
  std::string source_;
  std::string target_;
  std::string helpText_;
  bool help_;
  bool dryRun_;
};
}  // namespace dfiler::cli
