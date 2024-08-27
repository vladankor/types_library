// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- kore ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

namespace kore::type_traits {

//-------------------------------------------------------------------------------------------------
// struct general
//-------------------------------------------------------------------------------------------------

template<class T>
struct general {
  using type = T;
  using ref = type&;
  using rref = type&&;
  using cref = const type&;
  using ptr = type*;
  using cptr = const type*;
  using cptrc = const type* const;
}; // struct general

} // namespace kore::type_traits
