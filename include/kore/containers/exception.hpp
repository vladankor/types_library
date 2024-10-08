// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <exception>
#include <string>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/exception/base.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore {

struct k_empty_exception_tag {};

using k_empty_exception = k_exception<k_empty_exception_tag>;

struct k_not_found_exception_tag {};

using k_not_found_exception = k_exception<k_not_found_exception_tag>;

} // namespace kore