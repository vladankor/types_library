// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <filesystem>
#include <string_view>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/graph/graph.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::graph {

template<class TVertexData, class TEdgeData>
k_edge<TVertexData, TEdgeData> read_edge_from_json(const std::string_view json_edge) {
  using edge_type = k_edge<TVertexData, TEdgeData>;
  return edge_type{};
}

template<class TVertexData, class TEdgeData>
k_graph<TVertexData, TEdgeData> read_graph_from_json(const std::string_view json_value) {
  using graph_type = k_graph<TVertexData, TEdgeData>;
  return graph_type{};
}

template<class TVertexData, class TEdgeData>
k_graph<TVertexData, TEdgeData> read_graph_from_json_file(const std::filesystem::path& json_file) {
  using graph_type = k_graph<TVertexData, TEdgeData>;
  return graph_type{};
}

} // namespace kore::graph
