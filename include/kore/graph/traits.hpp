// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- kore ------------------------------------------------------------------------------------------
#include <kore/type_traits/helper.hpp>
#include <kore/utility/uuid.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::graph {

template<class VertexDataType, class EdgeDataType>
class k_vertex;

template<class VertexDataType, class EdgeDataType>
class k_edge;

template<class VertexDataType, class EdgeDataType>
struct graph_tt {
  // id helper types
  using id_type = boost::uuids::uuid;
  using id_tt = ::kore::type_traits::general<id_type>;
  // vertex helper types
  using v_type = k_vertex<EdgeDataType, VertexDataType>;
  using v_tt = ::kore::type_traits::general<v_type>;
  using v_d_tt = ::kore::type_traits::general<VertexDataType>;
  // edge helper types
  using e_type = k_edge<EdgeDataType, VertexDataType>;
  using e_tt = ::kore::type_traits::general<e_type>;
  using e_d_tt = ::kore::type_traits::general<EdgeDataType>;
}; // struct graph_ts

} // namespace kore::graph
