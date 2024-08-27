// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include "kore/graph/graph.hpp"
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
// ------------------------------------------------------------------------------------------------

//- boost -----------------------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/json.hpp>
#include <boost/json/parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
#include <kore/graph/reader.hpp>
// ------------------------------------------------------------------------------------------------

namespace kore {

k_graph read_graph_from_json(const std::string_view json_value) {
  k_graph result;
  boost::json::value j = boost::json::parse(json_value);
  return result;
}

} // namespace kore
