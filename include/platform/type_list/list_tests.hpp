// ----------------------------------------------------------------------------
// Copyright (C) 2020 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/type_list/list.hpp>
//-----------------------------------------------------------------------------

namespace platform::tests {

namespace data {

using empty_list = t_type_list<>;
using integers_1 = t_type_list<int>;
using integers_2 = t_type_list<int, int>;
using floats_1 = t_type_list<float>;
using floats_2 = t_type_list<float, float>;
using not_unique = t_type_list<int, int, int, float, int, float, float, bool, bool>;
using unique = t_type_list<int, float, bool>;

}  // namespace data

// ----------------------------------------------------------------------------
// is_empty_v tests
// ----------------------------------------------------------------------------

// test empty list
static_assert(is_empty_v<data::empty_list>, "is_empty_v failed");
// test list with one element
static_assert(!is_empty_v<data::integers_1>, "is_empty_v failed");
// test list with some elements
static_assert(!is_empty_v<data::integers_2>, "is_empty_v failed");

// ----------------------------------------------------------------------------
// is_contains_v tests
// ----------------------------------------------------------------------------

// test empty list
static_assert(!is_contains_v<int, data::empty_list>, "is_contains_v failed");
// test list with one element
static_assert(!is_contains_v<float, data::integers_1>, "is_contains_v failed");
// test list with come elements
static_assert(is_contains_v<int, data::integers_2>, "is_contains_v failed");
// test empty list with internal void type
static_assert(!is_contains_v<internal::void_type, data::empty_list>
  , "is_contains_v failed");
// test not empty list with internal void type
static_assert(!is_contains_v<internal::void_type, data::integers_1>
  , "is_contains_v failed");

// ----------------------------------------------------------------------------
// push_front_t tests
// ----------------------------------------------------------------------------

using empty_with_float = platform::push_front_t<float, data::empty_list>;
static_assert(std::is_same_v<empty_with_float, data::floats_1>, "push_front_t failed");

// ----------------------------------------------------------------------------
// pop_front_t tests
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// at_front_t tests
// ----------------------------------------------------------------------------

using integer_type = platform::at_front_t<data::integers_1>;
static_assert(std::is_same_v<integer_type, int>, "t_at_back failed");
using integers_with_float = platform::push_front_t<float, data::integers_1>;
using float_type = platform::at_front_t<integers_with_float>;
static_assert(std::is_same_v<float_type, float>, "t_at_back failed");

// ----------------------------------------------------------------------------
// unique_t tests
// ----------------------------------------------------------------------------

using unique_type = platform::unique_t<data::not_unique>;
static_assert(std::is_same_v<unique_type, data::unique>, "unique_t failed");

}  // namespace platform::tests
