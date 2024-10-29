// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

//- boost -----------------------------------------------------------------------------------------
#include <boost/uuid/uuid_generators.hpp>
#include <kore/utility/uuid.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::utility {

boost::uuids::uuid generate_uuid() noexcept {
  thread_local boost::uuids::random_generator generator;
  return generator();
}

} // namespace kore::utility
