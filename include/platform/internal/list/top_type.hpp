// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/internal/list/list_type.hpp>
// ----------------------------------------------------------------------------

namespace platform::internal {

//-----------------------------------------------------------------------------
// struct top_type
//-----------------------------------------------------------------------------

template<class ...>
struct top_type;


template<class ...TArgs>
struct top_type<list_type<TArgs...>> {
  using type = typename list_type<TArgs...>::head_type;
};  // top_type


template<class ...TArgs>
using top_t = typename top_type<TArgs...>::type;


}  // namespace platform::internal
