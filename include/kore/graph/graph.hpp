// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
// ------------------------------------------------------------------------------------------------

//- boost -----------------------------------------------------------------------------------------
#include <boost/uuid/uuid_io.hpp>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/containers/exception.hpp>
#include <kore/containers/heap.hpp>
#include <kore/containers/utility.hpp>
#include <kore/graph/edge.hpp>
#include <kore/graph/vertex.hpp>
#include <kore/managed_ptr.hpp>
#include <kore/utility/string.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::graph {

template<class TVertexData, class TEdgeData>
class k_graph {
 public:
  using tt = graph_tt<TVertexData, TEdgeData>;
  using id_to_v_type = std::unordered_map<typename tt::id_type, typename tt::v_type>;
  using id_to_e_type = std::unordered_map<typename tt::id_type, typename tt::e_type>;
  using id_list_type = std::vector<typename tt::id_type>;
  using id_to_id_list_type = std::unordered_map<typename tt::id_type, id_list_type>;

  enum class result {};

 public:
  // add vertex
  k_managed_ptr<typename tt::v_tt::type> add_vertex(tt::v_tt::rref vertex) {
    auto vertex_id = typename tt::id_tt::type{vertex.id()};
    typename tt::v_tt::ptr result = nullptr;
    if (auto vertex_it = m_vertices__.find(vertex_id); vertex_it == m_vertices__.end()) {
      m_source_to_edges__.emplace(vertex_id, id_list_type{});
      m_destination_to_edges__.emplace(vertex_id, id_list_type{});
      result = &(m_vertices__.emplace(std::move(vertex_id), std::move(vertex)).first->second);
    } else {
      vertex_it->second = std::move(vertex);
      result = &(vertex_it->second);
    }
    return make_k_managed_ptr(result);
  }
  decltype(auto) add_vertex(tt::v_tt::ref vertex) {
    return add_vertex(typename tt::v_tt::type{vertex});
  }
  decltype(auto) add_vertex(tt::id_tt::cref vertex_id, tt::v_d_tt::rref vertex_data) {
    return add_vertex(typename tt::v_tt::type{vertex_id, std::move(vertex_data)});
  }

  // edd edge
  k_managed_ptr<typename tt::e_tt::type> add_oriented_edge(tt::id_tt::cref source_id,
                                                           tt::id_tt::cref destination_id,
                                                           tt::e_d_tt::rref edge_data) {
    // check vertices
    auto source_ptr = utility::find_or_null(m_vertices__, source_id);
    if (!source_ptr) {
      return nullptr;
    }
    auto destination_ptr = utility::find_or_null(m_vertices__, destination_id);
    if (!destination_ptr) {
      return nullptr;
    }

    auto new_edge = typename tt::e_tt::type{utility::generate_uuid(), source_ptr, destination_ptr,
                                            std::move(edge_data)};
    auto new_edge_id = typename tt::id_tt::type{new_edge.id()};

    m_source_to_edges__[source_id].emplace_back(new_edge_id);
    m_destination_to_edges__[destination_id].emplace_back(new_edge_id);
    return make_k_managed_ptr(
        &m_edges__.insert_or_assign(std::move(new_edge_id), std::move(new_edge)).first->second);
  }

  std::pair<k_managed_ptr<typename tt::e_tt::type>, k_managed_ptr<typename tt::e_tt::type>>
  add_edge(tt::id_tt::cref source_id, tt::id_tt::cref destination_id, tt::e_d_tt::rref sd_edge_data,
           tt::e_d_tt::rref ds_edge_data) {
    return std::make_pair(add_oriented_edge(source_id, destination_id, std::move(sd_edge_data)),
                          add_oriented_edge(source_id, destination_id, std::move(ds_edge_data)));
  }

 public:
  [[nodiscard]] const id_to_v_type& vertices() { return m_vertices__; }

  [[nodiscard]] const id_to_e_type& edges() { return m_edges__; }

  template<typename TUnaryPredicat>
  [[nodiscard]] auto uniform_cost_search(tt::id_tt::cref source_vertex_id,
                                         tt::id_tt::cref destination_vertex_id,
                                         TUnaryPredicat edge_weight_function) const
      -> std::pair<
          bool, std::unordered_map<typename tt::id_type,
                                   std::invoke_result_t<TUnaryPredicat, typename tt::e_tt::cref>>> {
    using weight_type = std::invoke_result_t<TUnaryPredicat, typename tt::e_tt::cref>;
    using weighted_edge_id_type = std::pair<typename tt::id_type, weight_type>;
    struct WeightedEdgeIdComparator {
      bool operator()(const weighted_edge_id_type& lhs,
                      const weighted_edge_id_type& rhs) const noexcept {
        return std::less<weight_type>{}(lhs.second, rhs.second);
      }
    }; // struct WeightedEdgeIdComparator
    auto weight_summator = std::plus<weight_type>{};

    // Simple check
    if (!m_source_to_edges__.contains(source_vertex_id) ||
        !m_destination_to_edges__.contains(destination_vertex_id)) {
      return {false, {}};
    }
    k_heap<weighted_edge_id_type, WeightedEdgeIdComparator> bfs_border;
    bfs_border.emplace(source_vertex_id, weight_type{});
    std::unordered_map<typename tt::id_type, weight_type> weights;
    std::unordered_set<typename tt::id_type> visited_vertices;
    while (!bfs_border.empty()) {
      const auto current_vertex_info = bfs_border.pop();
      const auto& current_vertex_id = current_vertex_info.first;
      weights.emplace_hint(weights.end(), current_vertex_info.first, current_vertex_info.second);
      if (current_vertex_id == destination_vertex_id) {
        break;
      }
      const auto& output_edge_ids = m_source_to_edges__.find(current_vertex_id)->second;
      for (const auto& output_edge_id : output_edge_ids) {
        const auto& current_edge = m_edges__.find(output_edge_id)->second;
        const auto& destination_id = current_edge.destination()->id();
        if (visited_vertices.contains(destination_id)) {
          continue;
        }
        bfs_border.emplace(current_edge.destination()->id(),
                           std::invoke(weight_summator, current_vertex_info.second,
                                       std::invoke(edge_weight_function, current_edge)));
      }
      visited_vertices.emplace(current_vertex_id);
    }

    return {true, std::move(weights)};
  }

  [[nodiscard]] decltype(auto) breadth_first_search(tt::id_tt::cref start_vertex_id,
                                                    tt::id_tt::cref destination_vertex_id) const {
    return uniform_cost_search(start_vertex_id, destination_vertex_id,
                               []([[maybe_unused]] tt::e_tt::cref edge) -> std::size_t {
                                 return static_cast<std::size_t>(1);
                               });
  }

 private:
  id_to_v_type m_vertices__;
  id_to_e_type m_edges__;
  id_to_id_list_type m_source_to_edges__;
  id_to_id_list_type m_destination_to_edges__;
}; // class k_graph

} // namespace kore::graph
