// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <algorithm>
#include <functional>
#include <memory>
#include <type_traits>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/containers/utility.hpp>
#include <kore/managed_ptr.hpp>
#ifdef KORE_DEBUG_MODE
#include <kore/utility/string.hpp>
#endif
// ------------------------------------------------------------------------------------------------

namespace kore {

template<class TValue, class TComparator = std::greater<TValue>, std::size_t VBranchingFactor = 3,
         class TAllocator = std::allocator<TValue>>
class k_heap {
 public:
  static_assert(VBranchingFactor > 1, "Expected branching factor at least 2 to make a heap");

  using container_type = std::vector<TValue, TAllocator>;
  using value_type = typename container_type::value_type;
  using const_reference = typename container_type::const_reference;
  using size_type = typename container_type::size_type;
  using comparator_type = TComparator;

  static constexpr std::size_t s_branching_factor = VBranchingFactor;

#ifdef KORE_DEBUG_MODE
  const storage_type& storage() const noexcept { return m_storage__; }
#endif

  k_heap() noexcept(std::is_nothrow_default_constructible_v<container_type> &&
                    std::is_nothrow_default_constructible_v<comparator_type>) = default;

  value_type pop() noexcept(std::is_nothrow_move_constructible_v<value_type>) {
    return push_down__(0);
  }

  k_managed_ptr<const value_type> top() const noexcept {
    if (m_storage__.empty()) {
      return nullptr;
    }
    return make_k_managed_ptr(&m_storage__.front());
  }

  void insert(const value_type& value) {
    m_storage__.push_back(value);
    push_up__(m_storage__.size() - 1);
  }

  void insert(value_type&& value) {
    m_storage__.push_back(std::forward<value_type>(value));
    push_up__(m_storage__.size() - 1);
  }

  template<class... TArgs>
    requires std::constructible_from<value_type, TArgs...>
  decltype(auto) emplace(TArgs&&... args) {
    auto result = m_storage__.emplace_back(std::forward<TArgs>(args)...);
    push_up__(m_storage__.size() - 1);
    return result;
  }

  bool contains(const_reference value) const noexcept
    requires std::equality_comparable<value_type>
  {
    return utility::contains(m_storage__, value);
  }

  size_type remove(const_reference value)
    requires std::equality_comparable<value_type>
  {
    auto result = std::ranges::remove(m_storage__, value);
    m_storage__.erase(result.begin(), result.end());
    return result.size();
  }

  const size_type size() const noexcept { return m_storage__.size(); }

  const bool empty() const noexcept { return m_storage__.empty(); }

 private:
  inline size_type get_parent_index__(const size_type index) const noexcept {
    if (index <= 0) {
#ifdef KORE_DEBUG_MODE
      std::cout << "  Parent index for " << index << " is " << 0 << std::endl;
#endif
      return 0;
    }
#ifdef KORE_DEBUG_MODE
    std::cout << "  Parent index for " << index << " is " << (index - 1) / VBranchingFactor
              << std::endl;
#endif
    return (index - 1) / VBranchingFactor;
  }

  inline size_type get_left_child_index__(const size_type index) const noexcept {
    return std::min(index * VBranchingFactor + 1, m_storage__.size());
  }

  inline size_type get_right_child_index__(const size_type index) const noexcept {
    return std::min(index * VBranchingFactor + VBranchingFactor + 1, m_storage__.size());
  }

  inline size_type get_max_child_index__(const size_type index) const noexcept {
    const auto left = get_left_child_index__(index);
    const auto right = get_right_child_index__(index);
    if (left == right) {
      return m_storage__.size();
    }
    auto result = left;
    for (auto i = left; i < right - 1; ++i) {
      if (std::invoke(m_comparator__, m_storage__[i + 1], m_storage__[i])) {
        result = i + 1;
      }
    }
    return result;
  }

  value_type
  push_down__(const size_type index) noexcept(std::is_nothrow_move_constructible_v<value_type>) {
#ifdef KORE_DEBUG_MODE
    if (index < 0 || m_storage__.size() <= index) {
      std::cerr << "Bad index: " << index << std::endl;
    }
    std::cout << "Push down: " << m_storage__[index] << " at index " << index << std::endl;
#endif
    auto result = std::move(m_storage__[index]);
    if (m_storage__.size() > 1) {
      auto temp = std::move(m_storage__.back());
      m_storage__.pop_back();
      size_type current_index = 0;
      auto element_placement_index = get_max_child_index__(current_index);
      for (; element_placement_index < m_storage__.size();
           element_placement_index = get_max_child_index__(current_index)) {
        if (!std::invoke(m_comparator__, m_storage__[element_placement_index], temp)) {
          break;
        }
        m_storage__[current_index] = std::move(m_storage__[element_placement_index]);
        current_index = element_placement_index;
      }
      m_storage__[current_index] = std::move(temp);
    } else {
      m_storage__.pop_back();
    }
    return result;
  }

  void push_up__(const size_type index) noexcept(std::is_nothrow_move_constructible_v<value_type>) {
#ifdef KORE_DEBUG_MODE
    if (index < 0 || m_storage__.size() <= index) {
      std::cerr << "Bad index: " << index << std::endl;
    }
    std::cout << "Push up: " << m_storage__[index] << " at index " << index << std::endl;
#endif
    size_type i_destination = get_parent_index__(index);
    if (m_storage__.size() <= 1 ||
        !std::invoke(m_comparator__, m_storage__.back(), m_storage__[i_destination])) {
      return;
    }
    // Search for destination index
    for (; i_destination > 0; i_destination = get_parent_index__(i_destination)) {
#ifdef KORE_DEBUG_MODE
      std::cout << "  Compare " << m_storage__.back() << " and " << m_storage__[i_destination]
                << " with result " << m_comparator__(m_storage__.back(), m_storage__[i_destination])
                << std::endl;
#endif
      if (!std::invoke(m_comparator__, m_storage__.back(), m_storage__[i_destination])) {
        break;
      }
    }
#ifdef KORE_DEBUG_MODE
    std::cout << "  Result destination for value: " << i_destination << std::endl;
#endif
    auto value = std::move(m_storage__.back());
    auto i_current = m_storage__.size() - 1;
    while (i_current != i_destination) {
      const auto i_next = get_parent_index__(i_current);
      m_storage__[i_current] = std::move(m_storage__[i_next]);
      i_current = i_next;
    }
    m_storage__[i_destination] = std::move(value);
#ifdef KORE_DEBUG_MODE
    std::cout << "Result: " << utility::to_string(m_storage__) << std::endl;
#endif
  }

  container_type m_storage__;
  comparator_type m_comparator__;
};

} // namespace kore