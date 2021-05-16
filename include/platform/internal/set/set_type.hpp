// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/internal/list/list_type.hpp>
#include <platform/internal/list/is_empty_type.hpp>
#include <platform/internal/list/is_contains_type.hpp>

#include <platform/internal/list/merge_type.hpp>
#include <platform/internal/list/pop_type.hpp>
#include <platform/internal/list/push_type.hpp>
#include <platform/internal/list/top_type.hpp>
// ----------------------------------------------------------------------------

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

}  // namespace platform::internal
