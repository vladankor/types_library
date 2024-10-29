// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <cstddef>
// ------------------------------------------------------------------------------------------------

namespace kore {

/**
 * @brief A pointer that hasn't an owner. You must free memory by yourself.
 *
 * @tparam T
 */
template<class T>
class k_raw_ptr final {
 public:
  constexpr k_raw_ptr(std::nullptr_t) noexcept : m_ptr__(nullptr){};
  explicit constexpr k_raw_ptr(T* ptr) noexcept : m_ptr__{ptr} {}

  explicit constexpr operator bool() const noexcept { return m_ptr__; }

  T* operator->() const { return m_ptr__; }
  T* operator->() { return m_ptr__; }

  T& operator*() const { return *m_ptr__; }
  T& operator*() { return *m_ptr__; }

 private:
  T* m_ptr__;
};

template<class T>
constexpr k_raw_ptr<T> make_k_raw_ptr(T* ptr) noexcept {
  return k_raw_ptr<T>{ptr};
}

} // namespace kore