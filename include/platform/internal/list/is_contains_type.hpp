// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/internal/list/list_type.hpp>
// ----------------------------------------------------------------------------

namespace platform::internal {

//-----------------------------------------------------------------------------
// struct is_contains_type
//-----------------------------------------------------------------------------

template<class T, class ...TArgs>
struct is_contains_type;


template<class T>
struct is_contains_type<T, empty_list_type> : public std::false_type {
};  // is_contains_type


template<class T, class TNext, class ...TArgs>
struct is_contains_type<T, list_type<TNext, TArgs...>> : public
  std::integral_constant<
    bool
    , std::conjunction_v<
        internal::is_not_void_type_type<T>
        , std::disjunction<
            std::is_same<T, typename list_type<TNext, TArgs...>::head_type>
            , is_contains_type<T, typename list_type<TNext, TArgs...>::tail_type>
          >  // std::disjunction
      >  // std::conjunction_v
  > /* std::integral_constant */ {
};  // is_contains_type


template<class T, class TList>
inline constexpr bool is_contains_v = is_contains_type<T, TList>::value;


}  // namespace platform::internal
