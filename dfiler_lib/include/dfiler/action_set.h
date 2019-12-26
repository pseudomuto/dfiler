#pragma once

#include <set>

#include "action.h"

namespace dfiler {
/**
 * A set of actions.
 */
class ActionSet {
 public:
  /**
   * @return the number of items in the set
   */
  size_t Size() const noexcept;

  /**
   * Adds an item to the set.
   * @param action the unique pointer to the {@see Action}
   */
  void Add(std::unique_ptr<Action> action) noexcept;

  /**
   * Filters the set for the supplied type and returns the set of {@see Action}s
   * @param type the {@see ActionType} to filter for
   * @return the filtered set of actions
   */
  const std::set<std::shared_ptr<Action>> ForType(ActionType type) const noexcept;

 private:
  std::set<std::shared_ptr<Action>> actions_;
};
}  // namespace dfiler
