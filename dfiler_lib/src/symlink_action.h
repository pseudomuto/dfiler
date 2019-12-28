#pragma once

#include <filesystem>
#include <dfiler/dfiler.h>

namespace dfiler {
namespace fs = std::filesystem;

class SymlinkAction : public Action {
 public:
  SymlinkAction(const fs::path& link, const fs::path& target) : link_(link), target_(target) {}

  ActionType Type() const noexcept override;
  std::string Description() const noexcept override;
  bool IsMet() const override;
  void Meet() const override;

 private:
  const fs::path link_;
  const fs::path target_;
};
}  // namespace dfiler
