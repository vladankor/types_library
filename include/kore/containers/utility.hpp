// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <algorithm>
#include <concepts>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
// ------------------------------------------------------------------------------------------------

//- boost -----------------------------------------------------------------------------------------
#include <boost/uuid/uuid_io.hpp>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/managed_ptr.hpp>
#include <kore/type_traits/utility.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::utility {

template<std::ranges::range TContainer>
inline constexpr bool contains(TContainer& container,
                               const typename TContainer::value_type& value) {
  const auto begin = std::begin(container);
  const auto end = std::end(container);
  return !std::ranges::find(container, value).empty();
}

template<::kore::type_traits::Container TContainer>
inline constexpr auto find_or_null(TContainer& container,
                                   const typename TContainer::value_type& value)
    -> decltype(make_k_managed_ptr(std::find(std::begin(container), std::end(container), value))) {
  const auto end_it = std::end(container);
  if (const auto it = std::find(std::begin(container), end_it, value); it != end_it) {
    return make_k_managed_ptr(&(*it));
  }
  return {nullptr};
}

template<::kore::type_traits::MappedContainer TMap>
inline constexpr auto find_or_null(TMap& map, const typename TMap::key_type& key)
    -> decltype(make_k_managed_ptr(&map.find(key)->second)) {
  if (auto it = map.find(key); it != map.end()) {
    return make_k_managed_ptr(&it->second);
  }
  return {nullptr};
}

} // namespace kore::utility
