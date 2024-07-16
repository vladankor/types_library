// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <cstddef>
// ------------------------------------------------------------------------------------------------

namespace kore {

/**
 * @brief A pointer that has an owner. You shouldn't do memory management.
 *
 * @tparam T
 */
template<typename T>
class k_checked_ptr final {
 public:
  constexpr k_checked_ptr(std::nullptr_t) noexcept : m_ptr__{nullptr} {};
  explicit constexpr k_checked_ptr(T* ptr) noexcept : m_ptr__{ptr} {}

  explicit constexpr operator bool() const noexcept {
    m_checked__ = true;
    return m_ptr__;
  }

  T* operator->() const { return m_ptr__; }
  T* operator->() { return m_ptr__; }

  T& operator*() const { return *m_ptr__; }
  T& operator*() { return *m_ptr__; }

 private:
  mutable bool m_checked__ = false;
  T* m_ptr__;

  void check() const {}
};

template<typename T>
constexpr k_checked_ptr<T> make_k_checked_ptr(T* ptr) noexcept {
  return k_checked_ptr<T>{ptr};
}

} // namespace kore