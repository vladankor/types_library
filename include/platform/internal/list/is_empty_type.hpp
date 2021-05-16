// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/internal/list/list_type.hpp>
// ----------------------------------------------------------------------------

namespace platform::internal {

//-----------------------------------------------------------------------------
// struct is_empty_type
//-----------------------------------------------------------------------------

template<class ...TArgs>
struct is_empty_type;


template<>
struct is_empty_type<empty_list_type> : public std::true_type {
}; // is_empty_type


template<class T>
struct is_empty_type<list_type<T>> : public std::integral_constant<bool, is_void_v<typename list_type<T>::head_type>> {
};  // is_empty_type


template<class TNext, class ...TArgs>
struct is_empty_type<list_type<TNext, TArgs...>> : public
  std::integral_constant<
    bool
    , std::conjunction_v<
        is_void_type_type<typename list_type<TNext, TArgs...>::head_type>
        , is_empty_type<typename list_type<TNext, TArgs...>::tail_type>
      >  // std::disjunction_v
  > {  // std::integral_constant
};  // is_empty_type


template<class TList>
inline constexpr bool is_empty_v = is_empty_type<TList>::value;


}  // namespace platform::internal
