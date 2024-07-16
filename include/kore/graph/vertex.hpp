// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <kore/type_traits/helper.hpp>
// ------------------------------------------------------------------------------------------------

//- boost -----------------------------------------------------------------------------------------
#include <boost/uuid/uuid.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore {

class k_vertex {
 public:
  struct data {}; // struct data

 public:
  using data_traits = ::kore::type_traits::general<data>;
  using id_traits = ::kore::type_traits::general<boost::uuids::uuid>;

 public:
  k_vertex() noexcept = default;

  data_traits::const_reference data() const { return m_data__; }
  data_traits::reference data() { return m_data__; }

  id_traits::const_reference id() const { return m_id__; }
  id_traits::reference id() { return m_id__; }

 private:
  id_traits::value_type m_id__;
  data_traits::value_type m_data__;
}; // class k_vertex

} // namespace kore
