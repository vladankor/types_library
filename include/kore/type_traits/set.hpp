// ----------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- kore ----------------------------------------------------------------------
#include <kore/type_traits/list.hpp>
// ----------------------------------------------------------------------------


namespace kore::type_traits {

//-----------------------------------------------------------------------------
// struct set_type
//-----------------------------------------------------------------------------

template<class... TTypes>
struct list_type {
public:
  static consteval std::size_t size() noexcept {
    return sizeof...(TTypes);
  }

  template<class T>
  static consteval bool contains() noexcept {
    return (std::is_same_v<T, TTypes> || ...);
  }

  template<class T>
  static consteval std::size_t count() noexcept {
    return (static_cast<std::size_t>(std::is_same_v<T, TTypes>) + ...);
  }

  template<class... TPushTypes>
  static consteval exp_list<TPushTypes..., TTypes...> push_front() noexcept {
    return exp_list<TPushTypes..., TTypes...>();
  }

  template<class... TPushTypes>
  static consteval exp_list<TTypes..., TPushTypes...> push_back() noexcept {
    return exp_list<TTypes..., TPushTypes...>();
  }

  static consteval auto pop_front() noexcept {
    if constexpr (sizeof...(TTypes) < 1) {
      return exp_list<>{};
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
      return exp_list<>{};
    } else {
      return pop_back_<TTypes...>();
    }
  }

  static consteval auto back() noexcept {
    if constexpr (sizeof...(TTypes) == 0) {
      return kore::undefined_type{};
    } else {
      return back_<TTypes...>();
    }
  }

private:
  consteval list_type() = default;

  template<class T, class... TParams>
  static consteval exp_list<TParams...> pop_front_() noexcept {
    return exp_list<TParams...>();
  }

  template<class... TParams, class T>
  static consteval exp_list<TParams...> pop_back_() noexcept {
    return exp_list<TParams...>();
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


}  // namespace kore::type_traits

namespace platform::internal {

//-----------------------------------------------------------------------------
// struct set_type
//-----------------------------------------------------------------------------

template<class ...TArgs>
struct set_type;


template<class T>
struct set_type<list_type<T>> {
  using type = list_type<T>;
};


template<class T>
struct set_type<T> {
    using type = list_type<T>;
};


template<class T, class ...TArgs>
struct set_type<list_type<T, TArgs...>> {
  using type = std::conditional_t<
    is_contains_v<T, list_type<TArgs...>>
    , typename set_type<list_type<TArgs...>>::type
    , typename push_t<T, typename set_type<list_type<TArgs...>>::type>::type
  >;
};  // set_type

template<class ...TArgs>
using set_t = typename set_type<TArgs...>::type;

}  // namespace kore::type_traits
