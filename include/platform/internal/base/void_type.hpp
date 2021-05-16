// ----------------------------------------------------------------------------
// Copyright (C) 2021 Korobov Vladislav
// Type list with push type to front supporting
// ----------------------------------------------------------------------------

#pragma once

//- std -----------------------------------------------------------------------
#include <type_traits>
// ----------------------------------------------------------------------------


namespace platform::internal {

//-----------------------------------------------------------------------------
// struct void_type
//-----------------------------------------------------------------------------

struct void_type {
};  // void_type

//-----------------------------------------------------------------------------
// struct is_void_type_type
//-----------------------------------------------------------------------------

template<class TType>
struct is_void_type_type : public std::false_type {
};  // is_void_type_type


template<>
struct is_void_type_type<void_type> : public std::true_type {
};  // is_void_type_type


template<class TType>
inline constexpr bool is_void_v = is_void_type_type<TType>::value;

//-----------------------------------------------------------------------------
// struct is_not_void_type_type
//-----------------------------------------------------------------------------

template<class TType>
struct is_not_void_type_type : public std::true_type {
};  // is_not_void_type_type


template<>
struct is_not_void_type_type<void_type> : public std::false_type {
};  // is_not_void_type_type


template<class TType>
inline constexpr bool is_not_void_v = is_not_void_type_type<TType>::value;


}  // namespace platform::internal