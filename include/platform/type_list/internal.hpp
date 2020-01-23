// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- std -----------------------------------------------------------------------
#include <type_traits>
// ----------------------------------------------------------------------------

namespace platform::internal {

struct void_type {};

template<class TNode>
struct t_wrapper {
  using type = TNode;
};  // struct t_node

template<class T>
struct t_is_void
  : public std::is_same<
    T
    , void_type
  > {  // std::is_same
};  // struct t_is_void

template<class T>
struct t_is_void<t_wrapper<T>>
  : public std::is_same<
            typename t_wrapper<T>::type
            , void_type
           > {  // std::is_same
};  // struct t_is_void

template<class T>
inline constexpr bool is_void_v = t_is_void<T>::value;

template<class T>
struct t_is_not_void
  : public std::negation<
    std::is_same<
      T
      , void_type
    >  // std::is_same
  > {  // std::negation
};  // struct t_is_not_void

template<class T>
struct t_is_not_void<t_wrapper<T>>
  : public std::negation<
      std::is_same<
        typename t_wrapper<T>::type
        , void_type
      >  // std::is_same
    > {  // std::negation
};  // struct t_is_not_void

template<class T>
inline constexpr bool is_not_void_v = t_is_not_void<T>::value;

}  // namespace platform::internal
