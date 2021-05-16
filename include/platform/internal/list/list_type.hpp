// ----------------------------------------------------------------------------
// Copyright (C) 2021 Korobov Vladislav
// Type list with push type to front supporting
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/internal/base/void_type.hpp>
// ----------------------------------------------------------------------------


namespace platform::internal {

//-----------------------------------------------------------------------------
// struct list_type
//-----------------------------------------------------------------------------

template<class...>
struct list_type;


template<>
struct list_type<> {
  using head_type = internal::void_type;
  using tail_type = internal::void_type;
  static constexpr std::size_t size = 0;
};  // list_type


template<class THead>
struct list_type<THead> {
  using head_type = THead;
  using tail_type = internal::void_type;
  static constexpr std::size_t size = 1;
};  // list_type


template<class THead, class TNext, class ...TTail>
struct list_type<THead, TNext, TTail...> {
  using head_type = THead;
  using tail_type = list_type<TNext, TTail...>;
  static constexpr std::size_t size = 2 + sizeof...(TTail);
};  // list_type

using empty_list_type = list_type<>;


}  // namespace platform::internal