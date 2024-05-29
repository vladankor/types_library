// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <type_traits>
// ------------------------------------------------------------------------------------------------

namespace kore::type_traits {

//-------------------------------------------------------------------------------------------------
// struct null_type
//-------------------------------------------------------------------------------------------------

struct null_type {}; // null_type

template<class TType>
using is_null_type_t = std::is_same<std::decay_t<TType>, null_type>;

template<class TType>
inline constexpr bool is_null_type_v = is_null_type_t<TType>::value;

template<class TType>
inline constexpr bool is_not_null_type_v = !is_null_type_t<TType>::value;

} // namespace kore::type_traits