// ----------------------------------------------------------------------------
// Copyright (C) 2019 Korobov Vladislav
// ----------------------------------------------------------------------------

#pragma once

//- platform ------------------------------------------------------------------
#include <platform/internal/list/list_type.hpp>
// ----------------------------------------------------------------------------

namespace platform::internal {

//-----------------------------------------------------------------------------
// struct merge_type
//-----------------------------------------------------------------------------

template<class ...TArgsFirst>
struct merge_type;

template<class ...TArgsFirst>
struct merge_type<list_type<TArgsFirst...>> {
    template<class ...TArgsSecond>
    struct with_type;

    template<class ...TArgsSecond>
    struct with_type<list_type<TArgsSecond...>> {
        using type = list_type<TArgsFirst..., TArgsSecond...>;
    };  // t_with
};  // merge_type

}  // namespace platform::internal
