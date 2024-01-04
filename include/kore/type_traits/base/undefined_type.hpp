// ----------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- std -----------------------------------------------------------------------
#include <type_traits>
// ----------------------------------------------------------------------------


namespace kore::type_traits {

//-----------------------------------------------------------------------------
// struct undefined_type
//-----------------------------------------------------------------------------

struct undefined_type {
};  // undefined_type

template<class TType>
using is_undefined_type_t = std::is_same<std::decay_t<TType>, undefined_type>;

template<class TType>
inline constexpr bool is_undefined_type_v = is_undefined_type_t<TType>::value;

template<class TType>
inline constexpr bool is_not_undefined_type_v = !is_undefined_type_t<TType>::value;

}  // namespace kore::type_traits
