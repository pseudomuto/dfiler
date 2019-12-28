#include <iostream>

#include "symlink_action.h"

namespace dfiler {
ActionType SymlinkAction::Type() const noexcept { return ActionType::Symlink; }

std::string SymlinkAction::Description() const noexcept {
  return "Symlink " + link_.string() + " to " + target_.string();
}

bool SymlinkAction::IsApplied() const {
  if (!fs::is_symlink(link_)) {
    return false;
  }

  auto target = fs::read_symlink(link_);
  return target.compare(target_) == 0;
}

void SymlinkAction::Apply() const {
  fs::create_directories(link_.parent_path());
  fs::create_symlink(target_, link_);
}

void SymlinkAction::Undo() const {
  fs::remove(link_);
}
}  // namespace dfiler
