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

//- kore ------------------------------------------------------------------------------------------
#include <kore/managed_ptr.hpp>
#include <kore/type_traits/utility.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::utils {

template<std::ranges::range TContainer>
inline constexpr bool contains(TContainer& container,
                               const typename TContainer::value_type& value) {
  const auto begin = std::begin(container);
  const auto end = std::end(container);
  return !std::ranges::find(container, value).empty();
}

template<::kore::type_traits::MappedContainer TMap>
inline constexpr auto find_or_null(TMap& map, const typename TMap::key_type& key)
    -> decltype(make_k_managed_ptr(&map.find(key)->second)) {
  if (auto it = map.find(key); it != map.end()) {
    return make_k_managed_ptr(&it->second);
  }
  return {nullptr};
}

template<kore::type_traits::STDStringifiable T>
inline std::string k_to_string(const T& a) {
  return std::to_string(a);
}

template<class T, class U>
inline ::std::string k_to_string(const ::std::pair<T, U>& pair) {
  ::std::stringstream result;
  result << "(" << ::std::to_string(pair.first) << "," << ::std::to_string(pair.second) << ")";
  return result.str();
}

template<std::ranges::range T>
inline ::std::string k_to_string(const T& iterable) {
  ::std::stringstream result;
  auto current = ::std::cbegin(iterable);
  const auto end = ::std::cend(iterable);
  result << "[";
  for (; current != end; ++current) {
    result << to_string(*current);
    if (std::next(current) != end) {
      result << ",";
    }
  }
  result << "]";
  return result.str();
}

} // namespace kore::utils
