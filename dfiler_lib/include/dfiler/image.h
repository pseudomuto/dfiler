#pragma once

#include <filesystem>

#include "action.h"

namespace dfiler {
/**
 * An image describes a directory structure of the desired target state.
 *
 * For example, if all of your reference dot files are in `~/home/dotfiles` then this would be the *image* directory.
 * This image can then be applied to your target directory (which is typically `~/`).
 */
class Image {
 public:
  /**
   * Creates new Image with the supplied directory.
   * @param imageDir the image directory
   */
  explicit Image(const std::filesystem::path& imageDir) : imageDir_(imageDir) {}

  /**
   * Determines the missing actions (via {@see Image.Diff}) and applies them to the target directory.
   *
   * @param targetDir the target to apply the {@see Action}s to
   * @return the set of {@see Action}s that were applied
   */
  ActionSet Apply(const std::filesystem::path& targetDir) const;

  /**
   * Runs a diff between the image dir and the target dir to see which {@see Action}s should be taken. No changes are
   * made to the target dir here.
   *
   * @param targetDir the target to diff against
   * @return the set of {@see Action}s to be applied.
   */
  ActionSet Diff(const std::filesystem::path& targetDir) const;

 private:
  const std::filesystem::path imageDir_;

  std::filesystem::path RebasePath(const std::filesystem::path& newBase, const std::filesystem::path& path) const;
};
}  // namespace dfiler
