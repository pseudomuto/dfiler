#pragma once

#include <string>

namespace dfiler {
/**
 * An enumeration of the possible action types.
 */
enum class ActionType { Symlink };

/**
 * Represents an action that must be taken to make the image complete.
 */
class Action {
 protected:
  explicit Action() = default;

 public:
  Action(Action const&) = delete;
  Action(Action&&) = delete;
  virtual ~Action() = default;

  /**
   * The type of action this is.
   * @return the associated {@see ActionType}
   */
  virtual ActionType Type() const noexcept = 0;

  /**
   * Describes the action to be taken.
   * @return A string representation of the action
   */
  virtual std::string Description() const noexcept = 0;

  /**
   * Checks whether or not this action has already been taken.
   * @return true if nothing needs to be done
   */
  virtual bool IsApplied() const = 0;

  /**
   * Performs the necessary steps to make this action complete.
   */
  virtual void Apply() const = 0;

  /**
   * Undoes this action by removing the file/package/etc.
   */
  virtual void Undo() const = 0;
};
}  // namespace dfiler
