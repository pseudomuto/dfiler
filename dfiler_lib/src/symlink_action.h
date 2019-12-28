#pragma once

#include <dfiler/dfiler.h>
#include <filesystem>

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
