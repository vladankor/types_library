// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- kore ------------------------------------------------------------------------------------------
#include <kore/type_traits/helper.hpp>
#include <kore/utility/uuid.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::graph {

template<class TVertexData, class TEdgeData>
class k_vertex;

template<class TVertexData, class TEdgeData>
class k_edge;

template<class TVertexData, class TEdgeData>
struct graph_tt {
  // id helper types
  using id_type = boost::uuids::uuid;
  using id_tt = typename ::kore::type_traits::general<id_type>;
  // vertex helper types
  using v_type = k_vertex<TVertexData, TEdgeData>;
  using v_tt = typename ::kore::type_traits::general<v_type>;
  using v_d_tt = typename ::kore::type_traits::general<TVertexData>;
  // edge helper types
  using e_type = k_edge<TVertexData, TEdgeData>;
  using e_tt = typename ::kore::type_traits::general<e_type>;
  using e_d_tt = typename ::kore::type_traits::general<TEdgeData>;
}; // struct graph_ts

} // namespace kore::graph
