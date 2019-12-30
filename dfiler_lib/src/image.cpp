#include <chrono>               // for filesystem
#include <filesystem>           // for path, operator/, recursive_directory_...
#include <iosfwd>               // for string
#include <memory>               // for make_unique, shared_ptr, unique_ptr
#include <set>                  // for set
#include <string>               // for basic_string
#include <type_traits>          // for move
#include <vector>               // for vector
#include "dfiler/action.h"      // for Action, ActionType, ActionType::Symlink
#include "dfiler/action_set.h"  // for ActionSet
#include "dfiler/image.h"       // for Image
#include "symlink_action.h"     // for SymlinkAction

namespace fs = std::filesystem;

namespace {
auto Files(const fs::path& dir) {
  auto files = std::vector<fs::path>();

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
    action->Apply();
  }

  return actions;
}

ActionSet Image::Diff(const fs::path& targetDir) const {
  auto actionMap = ActionSet();

  for (const auto& path : Files(imageDir_)) {
    auto action = std::make_unique<SymlinkAction>(RebasePath(targetDir, path), path);
    if (!action->IsApplied()) {
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
