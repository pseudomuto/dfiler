#include <iostream>
#include <sstream>

#include "symlink_action.h"

const std::string dfiler::SymlinkAction::Description() const noexcept {
  auto ss = std::stringstream();
  ss << "Symlink " << link_ << " to " << target_;
  return ss.str();
}

bool dfiler::SymlinkAction::IsMet() const {
  if (!fs::is_symlink(link_)) {
    return false;
  }

  auto target = fs::read_symlink(link_);
  return target.compare(target_) == 0;
}

void dfiler::SymlinkAction::Meet() const { fs::create_symlink(target_, link_); }
