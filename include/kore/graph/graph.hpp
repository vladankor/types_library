// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <functional>
#include <unordered_map>
// ------------------------------------------------------------------------------------------------

//- boost -----------------------------------------------------------------------------------------
#include <boost/uuid/uuid_io.hpp>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/containers/exception.hpp>
#include <kore/containers/utility.hpp>
#include <kore/graph/edge.hpp>
#include <kore/graph/vertex.hpp>
#include <kore/managed_ptr.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::graph {

template<class VertexDataType, class EdgeDataType>
class k_graph {
 public:
  using tt = graph_tt<VertexDataType, EdgeDataType>;
  using id_to_v_type = std::unordered_map<typename tt::id_type, typename tt::v_type>;
  using id_to_e_type = std::unordered_map<typename tt::id_type, typename tt::e_type>;

  enum class result {};

 public:
  // add vertex
  void add_vertex(tt::v_tt::rref vertex) {
    auto vertex_id = vertex_id_type(vertex.id());
    if (auto vertex_it = m_vertices__.find(vertex_id); vertex_it == m_vertices__.end()) {
      m_vertices__.emplace(vertex_id, std::move(vertex));
      m_source_to_edges__.emplace(vertex_id, {});
      m_destination_to_edges__.emplace(std::move(vertex_id), {});
    } else {
      vertex_it->second = std::move(vertex);
    }
    return;
  }
  auto add_vertex(tt::v_tt::ref vertex) { return add_vertex(k_vertex{vertex}); }

  // edd edge
  void add_edge(tt::id_tt::cref source_id, tt::id_tt::cref destination_id,
                tt::e_tt::rref edge_data) {
    // check vertices
    auto source_ptr = find_or_throw_vertex_ptr(source_id);
    auto destination_ptr = find_or_throw_vertex_ptr(destination_id);

    auto new_edge = k_edge{generate_uuid(), source_ptr, destination_ptr, std::move(edge_data)};
    auto new_edge_id = typename tt::e_tt::type{new_edge.id()};

    m_edges__.insert_or_assign(new_edge_id, std::move(new_edge));
    m_source_to_edges__[source_id].emplace_back(new_edge_id);
    m_destination_to_edges__[destination_id].emplace_back(std::move(new_edge_id));
  }

 public:
  [[nodiscard]] const id_to_v_type& vertices() { return m_vertices__; }

  [[nodiscard]] const id_to_e_type& edges() { return m_edges__; }

 private:
  using id_list_type = std::vector<typename tt::id_type>;
  using id_to_id_list_type = std::unordered_map<typename tt::id_type, id_list_type>;

  id_to_v_type m_vertices__;
  id_to_e_type m_edges__;
  id_to_id_list_type m_source_to_edges__;
  id_to_id_list_type m_destination_to_edges__;

  [[nodiscard]] inline k_managed_ptr<typename tt::v_tt::type>
  find_or_throw_vertex_ptr(tt::v_tt::ref vertex_id) {
    auto vertex_ptr = utils::find_or_null(m_vertices__, vertex_id);
    if (!vertex_ptr) {
      throw k_not_found_exception{std::format("{}:{}: Vertex with id {} not found", __FILE__,
                                              __LINE__, boost::uuids::to_string(vertex_id))};
    }
    return vertex_ptr;
  };
}; // class k_graph

struct v_data {};

struct e_data {};

using default_graph = k_graph<v_data, e_data>;

} // namespace kore::graph
