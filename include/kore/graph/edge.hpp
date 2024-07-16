// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <memory>
// ------------------------------------------------------------------------------------------------

//- boost -----------------------------------------------------------------------------------------
#include <boost/uuid/uuid.hpp>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/managed_ptr.hpp>
#include <kore/type_traits/helper.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore {

class k_vertex;

class k_edge {
 public:
  struct data {
    data(const double weight, kore::k_managed_ptr<k_vertex> source,
         kore::k_managed_ptr<k_vertex> destination)
        : m_weight{weight}, m_source{std::move(source)}, m_destination{std::move(destination)} {}

    double m_weight = 0.0;
    k_managed_ptr<k_vertex> m_source = nullptr;
    k_managed_ptr<k_vertex> m_destination = nullptr;
  }; // struct data

 public:
  using data_traits = ::kore::type_traits::general<data>;
  using id_traits = ::kore::type_traits::general<boost::uuids::uuid>;

 public:
  k_edge() noexcept {}

  data_traits::const_reference data() const { return m_data__; }
  data_traits::reference data() { return m_data__; }

  id_traits::const_reference id() const { return m_id__; }
  id_traits::reference id() { return m_id__; }

 private:
  id_traits::value_type m_id__;
  data_traits::value_type m_data__;
}; // class k_edge

} // namespace kore
