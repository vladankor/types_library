// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- kore ------------------------------------------------------------------------------------------
#include <kore/graph/traits.hpp>
#include <kore/managed_ptr.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::graph {

template<class VertexDataType, class EdgeDataType>
class k_vertex {
 public:
  using tt = graph_tt<VertexDataType, EdgeDataType>;

 public:
  k_vertex(tt::id_tt::rref id, tt::id_tt::rref data) noexcept
      : m_id__{std::move(id)}, m_data__{std::move(data)} {};

  tt::v_d_tt::cref data() const { return m_data__; }
  tt::v_d_tt::ref data() { return m_data__; }

  tt::id_tt::cref id() const { return m_id__; }

 private:
  tt::id_type m_id__;
  tt::v_d_tt::type m_data__;
}; // class k_vertex

} // namespace kore::graph
