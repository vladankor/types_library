// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <exception>
#include <string>
// ------------------------------------------------------------------------------------------------

//- kore ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

namespace kore {

template<typename TTag>
class k_exception : public std::exception {
 public:
  using tag_type = TTag;

 public:
  k_exception() noexcept {}

  k_exception(const k_exception&) noexcept = default;
  k_exception(k_exception&&) noexcept = default;

  k_exception(const std::string& message) : m_what__{message} {}
  k_exception(std::string&& message) : m_what__{std::move(message)} {}

  const char* what() const noexcept override { return m_what__.data(); }

 private:
  std::string m_what__;
};

} // namespace kore