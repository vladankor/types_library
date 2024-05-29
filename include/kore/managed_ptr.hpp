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
class k_managed_ptr final {
public:
  constexpr k_managed_ptr(std::nullptr_t) noexcept : m_ptr__{nullptr} {};
  explicit constexpr k_managed_ptr(T* ptr) noexcept : m_ptr__{ptr} {}

  explicit constexpr operator bool() const noexcept { return m_ptr__; }

  T* operator->() const { return m_ptr__; }
  T* operator->() { return m_ptr__; }

  T& operator*() const { return *m_ptr__; }
  T& operator*() { return *m_ptr__; }

private:
  T* m_ptr__;
};

template<typename T>
constexpr k_managed_ptr<T> make_k_managed_ptr(T* ptr) noexcept {
  return k_managed_ptr<T>{ptr};
}

} // namespace kore