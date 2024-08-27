// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- boost -----------------------------------------------------------------------------------------
#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore {

boost::uuids::uuid generate_uuid() noexcept;

} // namespace kore

namespace std {

template<>
struct hash<boost::uuids::uuid> {
  size_t operator()(const boost::uuids::uuid& uid) const {
    return boost::hash<boost::uuids::uuid>()(uid);
  }
};

} // namespace std
