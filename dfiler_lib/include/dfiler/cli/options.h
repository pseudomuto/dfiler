#pragma once

#include <memory>
#include <string>

namespace dfiler::cli {
class Options {
 public:
  explicit Options(const std::string& name, const std::string& description) : name_(name), description_(description){};

  std::unique_ptr<Command> Parse(int argc, char**& argv);

 private:
  const std::string name_;
  const std::string description_;
};
}  // namespace dfiler::cli
