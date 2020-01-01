#include "symlink_command.h"
#include <ostream>  // for endl, operator<<, basic_ostream

namespace dfiler::cli {
int SymlinkCommand::Execute(std::ostream& out, std::ostream& err) const {
  out << "Creating symlinks" << std::endl;

  if (dryRun_) {
    out << "DRY RUN: No symlinks will be created." << std::endl;
  }
  return 0;
}
}  // namespace dfiler::cli
