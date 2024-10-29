// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <exception>
#include <format>
#include <stdexcept>
#include <type_traits>
// ------------------------------------------------------------------------------------------------

namespace kore {

/**
 * @brief A pointer that has an owner. You shouldn't do memory management.
 *
 * @tparam T
 */
template<class T, bool VNullAllowed = true>
class k_managed_ptr final {
 public:
  template<std::enable_if_t<VNullAllowed, bool> = true>
  constexpr k_managed_ptr(std::nullptr_t) noexcept : m_ptr__{nullptr} {}

  explicit constexpr k_managed_ptr(T* ptr) noexcept(VNullAllowed) : m_ptr__{ptr} {
    if constexpr (!VNullAllowed) {
      if (!m_ptr__) {
        throw std::invalid_argument(
            std::format("{}:{}: Null pointer value unavailable", __FILE__, __LINE__));
      }
    }
  }

  explicit constexpr operator bool() const noexcept { return m_ptr__; }

  T* operator->() const { return m_ptr__; }
  T* operator->() { return m_ptr__; }

  T& operator*() const { return *m_ptr__; }
  T& operator*() { return *m_ptr__; }

 private:
  T* m_ptr__;
}; // classs k_managed_ptr

template<typename T, bool VNullAllowed = true>
constexpr k_managed_ptr<T, VNullAllowed> make_k_managed_ptr(T* ptr) noexcept {
  return k_managed_ptr<T, VNullAllowed>{ptr};
}

} // namespace kore