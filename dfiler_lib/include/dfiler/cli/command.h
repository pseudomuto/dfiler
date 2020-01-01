#pragma once

#include <memory>   // for unique_ptr
#include <ostream>  // for ostream

namespace dfiler::cli {
class Options; // forward declaration
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

  /**
   * Create the correct {@see Command} class from the supplied options.
   * @param options the parsed options to use for construction
   * @return a unique pointer to the newly created command
   */
  static std::unique_ptr<Command> FromOptions(Options& options);

  /**
   * Executes this command
   * @param out the stream to write output to
   * @param err the stream to write error output to
   * @return the exit status for this command
   */
  virtual int Execute(std::ostream& out, std::ostream& err) const = 0;
};
}  // namespace dfiler::cli
