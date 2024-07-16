// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <functional>
#include <list>
#include <type_traits>
#include <unordered_map>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/graph/edge.hpp>
#include <kore/graph/vertex.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore {

class k_graph {
 public:
  k_graph() {}

 private:
  using vertex_id_type = k_vertex::id_traits::value_type;
  using edge_id_type = k_edge::id_traits::value_type;

  std::unordered_map<vertex_id_type, k_vertex> m_vertices__;
  std::unordered_map<edge_id_type, k_edge> m_edges__;
  std::unordered_map<vertex_id_type, std::vector<edge_id_type>> m_adjacency_list__;
}; // class k_graph

} // namespace kore
