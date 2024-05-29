// ------------------------------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- kore ------------------------------------------------------------------------------------------
#include <__ranges/concepts.h>
#include <iterator>
#include <kore/type_traits/list.hpp>
// ------------------------------------------------------------------------------------------------

//- std -------------------------------------------------------------------------------------------
#include <ranges>
#include <string>
// ------------------------------------------------------------------------------------------------

namespace kore::type_traits {

//-------------------------------------------------------------------------------------------------
// struct merge_type
//-------------------------------------------------------------------------------------------------

template <class... TArgsFirst> struct merge_type;

template <class... TArgsFirst> struct merge_type<list_type<TArgsFirst...>> {
  template <class... TArgsSecond> struct with_type;

  template <class... TArgsSecond> struct with_type<list_type<TArgsSecond...>> {
    using type = list_type<TArgsFirst..., TArgsSecond...>;
  }; // t_with
};   // merge_type

template<class T>
concept Container = requires (T a) {
  typename T::value_type;
} && std::ranges::range<T>;

template<class T>
concept MappedContainer = requires (T a) {
    typename T::key_type;
} && Container<T>;

template<class T>
concept Stringify = requires (T a) {
    { a.to_string() } -> std::same_as<std::string>;
};

template<class T>
concept STDStringify = requires (T a) {
  { std::to_string(a) } -> std::same_as<std::string>;
};

template<class T>
concept Iterable = std::ranges::range<T>;

} // namespace kore::type_traits
