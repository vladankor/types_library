// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/internal/list/list_type.hpp>
// ----------------------------------------------------------------------------

namespace platform::internal {

//-----------------------------------------------------------------------------
// struct pop_type
//-----------------------------------------------------------------------------

template<class ...TArgs>
struct pop_type;


template<class ...TArgs>
struct pop_type<list_type<TArgs...>> {
  using type = typename list_type<TArgs...>::tail_type;
};  // pop_type


template<class ...TArgs>
using pop_t = typename pop_type<TArgs...>::type;


}  // namespace platform::internal
