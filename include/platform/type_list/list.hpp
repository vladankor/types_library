// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/internal/list/is_empty_type.hpp>
#include <platform/internal/list/is_contains_type.hpp>

#include <platform/internal/list/merge_type.hpp>
#include <platform/internal/list/pop_type.hpp>
#include <platform/internal/list/push_type.hpp>
#include <platform/internal/list/top_type.hpp>
// ----------------------------------------------------------------------------

namespace platform {

using empty_list = internal::empty_list_type;


template<class ...TArgs>
using list_type = internal::list_type<TArgs...>;


template<class ...TArgs>
using is_contains_type = internal::is_contains_type<TArgs...>;


template<class T, class TList>
inline constexpr bool is_contains_v = internal::is_contains_v<T, TList>;


template<class ...TArgs>
using is_empty_type = internal::is_empty_type<TArgs...>;


template<class TList>
inline constexpr bool is_empty_v = internal::is_empty_v<TList>;


template<class ...TArgs>
using pop_t = internal::pop_t<TArgs ...>;


template<class ...TArgs>
using push_t = internal::push_t<TArgs...>;


template<class ...TArgs>
using top_t = internal::pop_t<TArgs ...>;


}  // namespace platform
