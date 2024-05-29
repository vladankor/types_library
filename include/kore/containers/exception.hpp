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

class k_empty_exception : public std::exception {
public:
  k_empty_exception() noexcept {}

  k_empty_exception(const k_empty_exception&) noexcept = default;
  k_empty_exception(k_empty_exception&&) noexcept = default;

  k_empty_exception(const std::string& message) : m_what_{message} {}
  k_empty_exception(std::string&& message) : m_what_{std::move(message)} {}

  const char* what() const noexcept override { return m_what_.data(); }

private:
  std::string m_what_;
};

} // namespace kore