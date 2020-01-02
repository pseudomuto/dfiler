#include <stddef.h>             // for size_t
#include <memory>               // for shared_ptr, unique_ptr
#include <set>                  // for set
#include <type_traits>          // for move
#include "dfiler/action.h"      // for Action, ActionType
#include "dfiler/action_set.h"  // for ActionSet

namespace dfiler {

size_t ActionSet::Size() const noexcept { return actions_.size(); }

void ActionSet::Add(std::unique_ptr<Action> action) noexcept { actions_.insert(std::move(action)); }

std::set<std::shared_ptr<Action>> ActionSet::ForType(ActionType type) const noexcept {
  auto results = std::set<std::shared_ptr<Action>>();

  for (const auto& action : actions_) {
    if (action->Type() != type) {
      continue;
    }

    results.insert(action);
  }

  return results;
}

}  // namespace dfiler
