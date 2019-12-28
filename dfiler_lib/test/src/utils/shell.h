#pragma once

#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <string>

namespace dfiler::utils {
static std::string execute(const std::string& cmd) {
  char buffer[128];
  std::string result = "";

  auto pipe = popen(cmd.c_str(), "r");
  if (!pipe) {
    return "popen call failed!";
  }

  while (!std::feof(pipe)) {
    if (std::fgets(buffer, 128, pipe) != NULL) {
      result += buffer;
    }
  }

  pclose(pipe);
  while (!result.empty() && result[result.length() - 1] == '\n') {
    result.erase(result.length() - 1);
  }

  return result;
}
}  // namespace dfiler::utils
