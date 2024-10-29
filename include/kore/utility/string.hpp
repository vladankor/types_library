// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <sstream>
#include <string>
// ------------------------------------------------------------------------------------------------

//- boost -----------------------------------------------------------------------------------------
#include <boost/uuid/uuid_io.hpp>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/type_traits/utility.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::utility {

namespace impl {

template<class TChar, class TCharTraits = std::char_traits<TChar>,
         class TAllocator = std::allocator<TChar>>
struct k_stringifier {
  using StringType = std::basic_string<TChar, TCharTraits, TAllocator>;
  using StringStreamType = std::basic_stringstream<TChar, TCharTraits, TAllocator>;

  inline StringType to_string(const boost::uuids::uuid& uuid) {
    return boost::uuids::to_string(uuid);
  }

  template<class... TArgs>
  inline StringType to_string(const TArgs&... args);

  template<kore::type_traits::STDStringifiable T>
  inline StringType to_string(const T& a) {
    return std::to_string(a);
  }

  template<kore::type_traits::SelfStringifiable T>
  inline StringType to_string(const T& a) {
    return a.to_string();
  }

  template<class T, class U>
  inline StringType to_string(const ::std::pair<T, U>& pair) {
    StringStreamType result;
    result << "(" << to_string(pair.first) << ", " << to_string(pair.second) << ")";
    return result.str();
  }

  template<std::ranges::range T>
  inline StringType to_string(const T& iterable) {
    StringStreamType result;
    const auto end = std::cend(iterable);
    result << "[";
    for (auto current = std::cbegin(iterable); current != end; ++current) {
      result << to_string(*current);
      if (std::next(current) != end) {
        result << ", ";
      }
    }
    result << "]";
    return result.str();
  }

  template<::kore::type_traits::MappedContainer T>
  inline StringType to_string(const T& iterable) {
    StringStreamType result;
    const auto end = std::cend(iterable);
    result << "{";
    for (auto current = std::cbegin(iterable); current != end; ++current) {
      result << to_string(*current);
      if (std::next(current) != end) {
        result << ", ";
      }
    }
    result << "}";
    return result.str();
  }

}; // struct k_stringifier

template<class TChar, class TCharTraits, class TAllocator, class... TArgs>
inline k_stringifier<TChar, TCharTraits, TAllocator>::StringType k_to_string(const TArgs&... args) {
  return k_stringifier<TChar, TCharTraits, TAllocator>{}.to_string(args...);
}

} // namespace impl

template<class... TArgs>
inline std::string k_to_std_string(const TArgs&... args) {
  return impl::k_to_string<char, std::char_traits<char>, std::allocator<char>, TArgs...>(args...);
}

} // namespace kore::utility
