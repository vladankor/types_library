// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/internal/list/list_type.hpp>
// ----------------------------------------------------------------------------

namespace platform::internal {

//-----------------------------------------------------------------------------
// struct push_type
//-----------------------------------------------------------------------------

template<class ...TArgs>
struct push_type;


template<class T, class ...TArgs>
struct push_type<T, list_type<TArgs...>> {
  using type = list_type<T, TArgs...>;
};  // struct push_type


template<class ...TArgs>
using push_t = typename push_type<TArgs...>::type;


}  // namespace platform::internal
