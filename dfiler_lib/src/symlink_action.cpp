#include <iostream>

#include "symlink_action.h"

namespace dfiler {
const ActionType SymlinkAction::Type() const noexcept { return ActionType::Symlink; }

const std::string SymlinkAction::Description() const noexcept {
  return "Symlink " + link_.string() + " to " + target_.string();
}

bool SymlinkAction::IsMet() const {
  if (!fs::is_symlink(link_)) {
    return false;
  }

  auto target = fs::read_symlink(link_);
  return target.compare(target_) == 0;
}

void SymlinkAction::Meet() const {
  fs::create_directories(link_.parent_path());
  fs::create_symlink(target_, link_);
}
}  // namespace dfiler
