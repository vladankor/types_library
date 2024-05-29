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
  using value_type = T;
  using reference = value_type&;
  using rreference = value_type&&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
}; // struct general

} // namespace kore::type_traits
