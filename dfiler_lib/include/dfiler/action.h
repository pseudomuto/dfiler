#pragma once

#include <string>

namespace dfiler {
/**
 * Represents an action that must be taken to make the image complete.
 */
class Action {
 protected:
  explicit Action() {}

 public:
  /**
   * Describes the action to be taken.
   * @return A string representation of the action
   */
  virtual const std::string Description() const noexcept = 0;

  /**
   * Checks whether or not this action has already been taken.
   * @return true if nothing needs to be done
   */
  virtual bool IsMet() const = 0;

  /**
   * Performs the necessary steps to make this action complete.
   */
  virtual void Meet() const = 0;
};
}  // namespace dfiler
