// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#include "kore/utility/string.hpp"

//- std -------------------------------------------------------------------------------------------
#include <unordered_set>
// ------------------------------------------------------------------------------------------------

//- boost -----------------------------------------------------------------------------------------
#include <boost/algorithm/string.hpp>
#include <boost/functional/hash.hpp>
#include <boost/test/unit_test.hpp>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/graph/graph.hpp>
#include <kore/utility/uuid.hpp>
// ------------------------------------------------------------------------------------------------

namespace {

struct common_v_data {};

struct common_e_data {};

using common_graph = kore::graph::k_graph<common_v_data, common_e_data>;

struct weighted_e_data {
  std::size_t weight;
};

using weighted_graph = kore::graph::k_graph<common_v_data, weighted_e_data>;

} // namespace

BOOST_AUTO_TEST_SUITE(k_graph)
BOOST_AUTO_TEST_CASE(test_only_ctor) { BOOST_CHECK_NO_THROW(common_graph g); }
BOOST_AUTO_TEST_CASE(test_add_vertices_and_edges) {
  common_graph g;

  const auto source_id = kore::utility::generate_uuid();
  const auto p_source_vertex = g.add_vertex(source_id, common_v_data{});
  BOOST_CHECK_EQUAL(p_source_vertex->id(), source_id);

  const auto destination_id = kore::utility::generate_uuid();
  const auto p_destination_vertex = g.add_vertex(destination_id, common_v_data{});
  BOOST_CHECK_EQUAL(p_destination_vertex->id(), destination_id);

  BOOST_CHECK_EQUAL(g.vertices().size(), 2);
  const auto ids = std::unordered_set<common_graph::tt::id_type>{source_id, destination_id};
  for (const auto& [id, vertex] : g.vertices()) {
    BOOST_CHECK(ids.contains(id));
  }

  g.add_oriented_edge(source_id, destination_id, common_graph::tt::e_d_tt::type{});
}
BOOST_AUTO_TEST_CASE(test_breadth_first_search) {
  {
    common_graph g;

    const auto make_and_add_vertex = [&g]() {
      const auto vertex_id = kore::utility::generate_uuid();
      auto p_source_vertex = g.add_vertex(vertex_id, common_v_data{});
      BOOST_CHECK_EQUAL(p_source_vertex->id(), vertex_id);
      return p_source_vertex;
    };

    auto p_v_1 = make_and_add_vertex();
    auto p_v_2 = make_and_add_vertex();
    auto p_v_3 = make_and_add_vertex();
    auto p_v_4 = make_and_add_vertex();
    auto p_v_5 = make_and_add_vertex();
    auto p_v_6 = make_and_add_vertex();

    g.add_edge(p_v_1->id(), p_v_2->id(), common_graph::tt::e_d_tt::type{},
               common_graph::tt::e_d_tt::type{});
    g.add_edge(p_v_1->id(), p_v_3->id(), common_graph::tt::e_d_tt::type{},
               common_graph::tt::e_d_tt::type{});
    g.add_edge(p_v_1->id(), p_v_5->id(), common_graph::tt::e_d_tt::type{},
               common_graph::tt::e_d_tt::type{});
    g.add_edge(p_v_2->id(), p_v_4->id(), common_graph::tt::e_d_tt::type{},
               common_graph::tt::e_d_tt::type{});
    g.add_edge(p_v_3->id(), p_v_4->id(), common_graph::tt::e_d_tt::type{},
               common_graph::tt::e_d_tt::type{});
    g.add_edge(p_v_4->id(), p_v_5->id(), common_graph::tt::e_d_tt::type{},
               common_graph::tt::e_d_tt::type{});
    g.add_edge(p_v_4->id(), p_v_6->id(), common_graph::tt::e_d_tt::type{},
               common_graph::tt::e_d_tt::type{});
    g.add_edge(p_v_5->id(), p_v_6->id(), common_graph::tt::e_d_tt::type{},
               common_graph::tt::e_d_tt::type{});

    const auto result = g.breadth_first_search(p_v_1->id(), p_v_4->id());
    std::cout << kore::utility::k_to_std_string(result) << std::endl;
  }
}
BOOST_AUTO_TEST_CASE(test_uniform_cost_search) {
  {
    weighted_graph g;

    const auto make_and_add_vertex = [&g]() {
      const auto vertex_id = kore::utility::generate_uuid();
      auto p_source_vertex = g.add_vertex(vertex_id, common_v_data{});
      BOOST_CHECK_EQUAL(p_source_vertex->id(), vertex_id);
      return p_source_vertex;
    };

    auto p_v_1 = make_and_add_vertex();
    auto p_v_2 = make_and_add_vertex();
    auto p_v_3 = make_and_add_vertex();

    g.add_edge(p_v_1->id(), p_v_2->id(), weighted_graph::tt::e_d_tt::type{1},
               weighted_graph::tt::e_d_tt::type{1});
    g.add_edge(p_v_2->id(), p_v_3->id(), weighted_graph::tt::e_d_tt::type{1},
               weighted_graph::tt::e_d_tt::type{1});
    g.add_edge(p_v_1->id(), p_v_3->id(), weighted_graph::tt::e_d_tt::type{3},
               weighted_graph::tt::e_d_tt::type{3});

    const auto result =
        g.uniform_cost_search(p_v_1->id(), p_v_3->id(), [](weighted_graph::tt::e_tt::cref edge) {
          return edge.data().weight;
        });
    std::cout << kore::utility::k_to_std_string(result) << std::endl;
  }
}
BOOST_AUTO_TEST_SUITE_END()