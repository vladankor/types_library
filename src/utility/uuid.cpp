// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- boost -----------------------------------------------------------------------------------------
#include <boost/uuid/uuid_generators.hpp>
#include <kore/utility/uuid.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore {

boost::uuids::uuid generate_uuid() noexcept {
  thread_local boost::uuids::random_generator generator;
  return generator();
}

} // namespace kore
