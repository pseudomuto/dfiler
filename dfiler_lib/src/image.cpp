#include <iostream>
#include <map>
#include <vector>

#include "dfiler/dfiler.h"
#include "symlink_action.h"

namespace fs = std::filesystem;

namespace {
auto Files(const fs::path& dir) {
  auto files = std::vector<const fs::path>();

  for (const auto& entry : fs::recursive_directory_iterator(dir)) {
    if (!entry.is_regular_file()) {
      continue;
    }

    files.push_back(entry.path());
  }

  return files;
}
}  // namespace

namespace dfiler {
ActionSet Image::Apply(const fs::path& targetDir) const {
  auto actions = Diff(targetDir);

  for (const auto& action : actions.ForType(ActionType::Symlink)) {
    action->Meet();
  }

  return actions;
}

ActionSet Image::Diff(const fs::path& targetDir) const {
  auto actionMap = ActionSet();

  for (const auto& path : Files(imageDir_)) {
    auto action = std::make_unique<SymlinkAction>(RebasePath(targetDir, path), path);
    if (!action->IsMet()) {
      actionMap.Add(std::move(action));
    }
  }

  return actionMap;
}

fs::path Image::RebasePath(const std::filesystem::path& newBase, const std::filesystem::path& path) const {
  auto sourceDirPrefix = imageDir_.string();
  auto relativePath = path.string().substr(sourceDirPrefix.length() + 1);
  return newBase / relativePath;
}
}  // namespace dfiler
