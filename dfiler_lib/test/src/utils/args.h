#pragma once

#include <cstring>           // for strdup
#include <initializer_list>  // for initializer_list
#include <memory>            // for unique_ptr

namespace dfiler::utils {
struct Args {
  explicit Args(std::initializer_list<const char*> args)
      : argv_(new char*[args.size()]), argc_(static_cast<int>(args.size())) {
    auto i = 0;
    for (const auto& arg : args) {
      argv_.get()[i++] = strdup(arg);
    }
  }

  auto Argc() { return argc_; }
  auto Argv() { return argv_.get(); }

 private:
  int argc_;
  std::unique_ptr<char*[]> argv_;
};
}  // namespace dfiler::utils
