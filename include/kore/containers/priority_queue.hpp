// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <algorithm>
#include <functional>
#include <limits>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <type_traits>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/containers/utility.hpp>
#include <kore/managed_ptr.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore {

template<class T, class TComparator = std::less<T>, class TAllocator = std::allocator<T>>
class k_priority_queue {
 public:
  using value_type = T;
  using allocator_type = TAllocator;
  using size_type = std::size_t;

  k_priority_queue() noexcept;

  T&& top();

  const T& peek() const;

  void insert(T&& value);

  template<class... TArgs>
  void emplace(TArgs&&... args);

  bool contains(const T& value) const noexcept
    requires std::equality_comparable<T>;

  bool remove(const T& value)
    requires std::equality_comparable<T>;

  bool update(const T& value)
    requires std::equality_comparable<T>;

  template<class... TArgs>
  bool update(const T& value)
    requires std::equality_comparable<T>;

  const size_type size() const noexcept;

  const bool empty() const noexcept;

 private:
};

} // namespace kore