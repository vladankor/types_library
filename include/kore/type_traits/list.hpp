// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- kore ------------------------------------------------------------------------------------------
#include <kore/type_traits/base/undefined_type.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::type_traits {

//-------------------------------------------------------------------------------------------------
// struct list_type
//-------------------------------------------------------------------------------------------------

template<class... TTypes>
struct list_type {
 public:
  static consteval std::size_t size() noexcept { return sizeof...(TTypes); }

  static consteval bool empty() noexcept { return sizeof...(TTypes) == 0; }

  template<class T>
  static consteval bool contains() noexcept {
    return (std::is_same_v<T, TTypes> || ...);
  }

  template<class T>
  static consteval std::size_t count() noexcept {
    return (static_cast<std::size_t>(std::is_same_v<T, TTypes>) + ...);
  }

  template<class... TPushTypes>
  static consteval list_type<TPushTypes..., TTypes...> push_front() noexcept {
    return list_type<TPushTypes..., TTypes...>();
  }

  template<class... TPushTypes>
  static consteval list_type<TTypes..., TPushTypes...> push_back() noexcept {
    return list_type<TTypes..., TPushTypes...>();
  }

  static consteval auto pop_front() noexcept {
    if constexpr (sizeof...(TTypes) < 1) {
      return list_type<>{};
    } else {
      return pop_front_<TTypes...>();
    }
  }

  static consteval auto front() noexcept {
    if constexpr (sizeof...(TTypes) == 0) {
      return undefined_type{};
    } else {
      return front_<TTypes...>();
    }
  }

  static consteval auto pop_back() noexcept {
    if constexpr (sizeof...(TTypes) == 0) {
      return list_type<>{};
    } else {
      return pop_back_<TTypes...>();
    }
  }

  static consteval auto back() noexcept {
    if constexpr (sizeof...(TTypes) == 0) {
      return undefined_type{};
    } else {
      return back_<TTypes...>();
    }
  }

 private:
  consteval list_type() = default;

  template<class T, class... TParams>
  static consteval list_type<TParams...> pop_front_() noexcept {
    return list_type<TParams...>();
  }

  template<class... TParams, class T>
  static consteval list_type<TParams...> pop_back_() noexcept {
    return list_type<TParams...>();
  }

  template<class T, class... TParams>
  static consteval T front_() noexcept {
    return T{};
  }

  template<class... TParams, class T>
  static consteval T back_() noexcept {
    return T{};
  }

}; // struct list_type

} // namespace kore::type_traits