#include <filesystem>

#include "symlink.h"

namespace fs = std::filesystem;

void dfiler::io::Symlink::Create() const { fs::create_symlink(target_, link_); }

bool dfiler::io::Symlink::Exists() const { return fs::is_symlink(link_); }

bool dfiler::io::Symlink::IsFile() const { return fs::is_regular_file(target_); }

bool dfiler::io::Symlink::IsDirectory() const { return fs::is_directory(target_); }