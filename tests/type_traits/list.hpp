// ------------------------------------------------------------------------------------------------
// Copyright (C) 2020 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- platform --------------------------------------------------------------------------------------
#include <kore/type_traits/list.hpp>
//-------------------------------------------------------------------------------------------------

namespace kore::type_traits {

namespace data {

using empty_list = list_type<>;
using integers_1 = list_type<int>;
using integers_2 = list_type<int, int>;
using floats_1 = list_type<float>;
using floats_2 = list_type<float, float>;
using not_unique = list_type<int, int, float, float, bool, bool>;
using unique = list_type<int, float, bool>;

} // namespace data

// ------------------------------------------------------------------------------------------------
// size tests
// ------------------------------------------------------------------------------------------------

namespace {

static_assert(data::empty_list::size() == 0, "list size failed");
static_assert(data::integers_1::size() == 1, "list size failed");
static_assert(data::integers_2::size() == 2, "list size failed");

} // namespace

// ------------------------------------------------------------------------------------------------
// empty tests
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// contains tests
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// count tests
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// push_front tests
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// push_back tests
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// pop_front tests
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// front tests
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// pop_back tests
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// back tests
// ------------------------------------------------------------------------------------------------

} // namespace kore::type_traits
