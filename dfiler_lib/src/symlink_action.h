#pragma once

#include <chrono>           // for filesystem
#include <filesystem>       // for path
#include <string>           // for string
#include "dfiler/action.h"  // for Action, ActionType

namespace dfiler {
namespace fs = std::filesystem;

class SymlinkAction : public Action {
 public:
  SymlinkAction(const fs::path& link, const fs::path& target) : link_(link), target_(target) {}

  ActionType Type() const noexcept override;
  std::string Description() const noexcept override;
  bool IsApplied() const override;
  void Apply() const override;
  void Undo() const override;

 private:
  const fs::path link_;
  const fs::path target_;
};
}  // namespace dfiler
