// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <memory>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/graph/traits.hpp>
#include <kore/managed_ptr.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore::graph {

template<class TVertexData, class TEdgeData>
class k_edge {
 public:
  using tt = graph_tt<TVertexData, TEdgeData>;

 public:
  k_edge(tt::id_tt::type id, kore::k_managed_ptr<typename tt::v_tt::type> source,
         kore::k_managed_ptr<typename tt::v_tt::type> destination, tt::e_d_tt::rref data) noexcept
      : m_id__{std::move(id)}, m_source__{std::move(source)},
        m_destination__{std::move(destination)}, m_data__{std::move(data)} {}

  tt::e_d_tt::cref data() const noexcept { return m_data__; }
  tt::e_d_tt::ref data() noexcept { return m_data__; }

  tt::id_tt::cref id() const noexcept { return m_id__; }

  const k_managed_ptr<typename tt::v_type>& source() const noexcept { return m_source__; }
  const k_managed_ptr<typename tt::v_type>& destination() const noexcept { return m_destination__; }

 private:
  tt::id_type m_id__;
  k_managed_ptr<typename tt::v_type> m_source__ = nullptr;
  k_managed_ptr<typename tt::v_type> m_destination__ = nullptr;
  tt::e_d_tt::type m_data__;
}; // class k_edge

} // namespace kore::graph
