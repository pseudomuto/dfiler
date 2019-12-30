#pragma once

#include <ostream>
#include <string>

namespace dfiler::cli {
/**
 * A base class for {@see Command} objects.
 */
class Command {
 protected:
  explicit Command() = default;

 public:
  Command(Command const&) = delete;
  Command(Command&&) = delete;
  virtual ~Command() = default;

  virtual int Execute(std::ostream& out, std::ostream& err) const = 0;
};
}  // namespace dfiler::main
