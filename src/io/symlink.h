#pragma once

#include <string>

namespace dfiler::io {
/**
 * Symlink describes a soft link from the link to the target.
 *
 * <pre>{@code
 * auto link = Symlink("./VERSION.txt", "/<user>/home/.VERSION.txt");
 * link.Create();
 *
 * link.Exists();     // true
 * link.IsFile();     // true
 * link.IsDirectory() // false
 * }</pre>
 */
class Symlink {
 public:
  Symlink(const std::string& target, const std::string& link) : target_(target), link_(link) {}

  /**
   * Creates the symlink on the filesystem. Will not overwrite existing
   * symlinks.
   */
  void Create() const;

  /**
   * Checks to see if this link already Exists.
   * @return true when Exists
   */
  bool Exists() const;

  /**
   * Checks whether or not the target is a file.
   * @return True if Exists and is a file
   */
  bool IsFile() const;

  /**
   * Checks whether or not the target is a directory.
   * @return True is exists and is a directory
   */
  bool IsDirectory() const;

 private:
  const std::string& target_;
  const std::string& link_;
};
}  // namespace dfiler::io
