// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/traits/type_traits.hpp>
#include <platform/type_list/internal.hpp>
// ----------------------------------------------------------------------------

namespace platform {

//-----------------------------------------------------------------------------
// struct t_type_list
//-----------------------------------------------------------------------------

template<class...>
struct t_type_list;

template<>
struct t_type_list<> {
  using head_type = internal::void_type;
  using tail_type = internal::void_type;
};  // t_type_list<>

using t_empty_list = t_type_list<>;

template<class THead>
struct t_type_list<THead> {
  using head_type = THead;
  using tail_type = t_empty_list;
};  // t_type_list<class THead>

template<class THead, class TNext, class ...TTail>
struct t_type_list<THead, TNext, TTail...> {
  using head_type = THead;
  using tail_type = t_type_list<TNext, TTail...>;
};  // t_type_list<class THead, class TNext, class ...TTail>

//-----------------------------------------------------------------------------
// struct t_is_empty
//-----------------------------------------------------------------------------

template<class ...TArgs>
struct t_is_empty;

template<>
struct t_is_empty<t_empty_list> : public std::true_type {
};

template<class T>
struct t_is_empty<t_type_list<T>> : public
  std::integral_constant<
    bool
    , internal::is_void_v<
        typename t_type_list<T>::head_type
      >  // is_not_void_v
  > {  // std::integral_constant
};

template<class TNext, class ...TArgs>
struct t_is_empty<t_type_list<TNext, TArgs...>> : public
  std::integral_constant<
    bool
    , std::conjunction_v<
        internal::t_is_void<
          typename t_type_list<TNext, TArgs...>::head_type
        >  // internal::is_void
        , t_is_empty<
            typename t_type_list<TNext, TArgs...>::tail_type
          >  // t_is_empty
      >  // std::disjunction_v
  > {  // std::integral_constant
};

template<class TList>
inline constexpr bool is_empty_v = t_is_empty<TList>::value;

//-----------------------------------------------------------------------------
// struct t_is_contains
//-----------------------------------------------------------------------------

template<class T, class ...TArgs>
struct t_is_contains;

template<class T>
struct t_is_contains<T, t_empty_list> : public std::false_type {
};  // struct t_is_contains

template<class T, class TNext, class ...TArgs>
struct t_is_contains<T, t_type_list<TNext, TArgs...>> : public
  std::integral_constant<
    bool
    , std::conjunction_v<
        internal::t_is_not_void<
          T
        >  // t_is_not_void
        , std::disjunction<
            std::is_same<
              T
              , typename t_type_list<TNext, TArgs...>::head_type
            >  // std::is_same
            , t_is_contains<
                T
                , typename t_type_list<TNext, TArgs...>::tail_type
              >  // t_is_contains
          >  // std::disjunction
      >  // std::conjunction_v
  > {  // std::integral_constant
};  // struct t_is_contains

template<class T, class TList>
inline constexpr bool is_contains_v = t_is_contains<T, TList>::value;

//-----------------------------------------------------------------------------
// struct t_push_front
//-----------------------------------------------------------------------------

template<class ...TArgs>
struct t_push_front;

template<class T, class ...TArgs>
struct t_push_front<T, t_type_list<TArgs...>> {
  using type = t_type_list<T, TArgs...>;
};  // struct t_push_front

template<class ...TArgs>
using push_front_t = typename t_push_front<TArgs...>::type;

//-----------------------------------------------------------------------------
// struct t_pop_front
//-----------------------------------------------------------------------------

template<class ...TArgs>
struct t_pop_front;

template<class ...TArgs>
struct t_pop_front<t_type_list<TArgs...>> {
  using type = typename t_type_list<TArgs...>::tail_type;
};  // struct t_pop_front

template<class ...TArgs>
using pop_front_t = typename t_pop_front<TArgs...>::type;

//-----------------------------------------------------------------------------
// struct t_at_front
//-----------------------------------------------------------------------------

template<class ...TArgs>
struct t_at_front;

template<class ...TArgs>
struct t_at_front<t_type_list<TArgs...>> {
  using type = typename t_type_list<TArgs...>::head_type;
};  // struct t_at_front

template<class ...TArgs>
using at_front_t = typename t_at_front<TArgs...>::type;

//-----------------------------------------------------------------------------
// struct t_merge
//-----------------------------------------------------------------------------

template<class ...TArgsFirst>
struct t_merge;

template<class ...TArgsFirst>
struct t_merge<t_type_list<TArgsFirst...>> {
template<class ...TArgsSecond>
struct t_with;

template<class ...TArgsSecond>
struct t_with<t_type_list<TArgsSecond...>> {
  using type = t_type_list<TArgsFirst..., TArgsSecond...>;
};  // t_with
};  // t_merge

//-----------------------------------------------------------------------------
// struct t_if_else
//-----------------------------------------------------------------------------

template<class TIf, class TElse, bool Conditional>
struct t_if_else;

template<class TIf, class TElse>
struct t_if_else<TIf, TElse, true> {
  using type = TIf;
};  // t_if_else<true, TIf, TElse>

template<class TIf, class TElse>
struct t_if_else<TIf, TElse, false> {
  using type = TElse;
};  // t_if_else<false, TIf, TElse>

template<class TIf, class TElse, bool Confitional>
using if_else_t = typename t_if_else<TIf, TElse, Confitional>::type;

//-----------------------------------------------------------------------------
// struct t_unique
//-----------------------------------------------------------------------------

template<class ...TArgs>
struct t_unique;

template<class T>
struct t_unique<t_type_list<T>> {
  using type = t_type_list<T>;
};

template<class T, class ...TArgs>
struct t_unique<t_type_list<T, TArgs...>> {
  using type = typename t_if_else<
    typename t_unique<t_type_list<TArgs...>>::type
    , typename t_push_front<T, typename t_unique<t_type_list<TArgs...>>::type>::type
    , is_contains_v<
        T
        , t_type_list<TArgs...>
      >  // is_contains_v
  >::type;  // if_else_t
};  // t_unique

template<class T, class ...TArgs>
using unique_t = typename t_unique<T, TArgs...>::type;

}  // namespace platform
