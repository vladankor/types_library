// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -----------------------------------------------------------------------------------------
#include <chrono>
// ------------------------------------------------------------------------------------------------

namespace kore {

template<class TClock>
class k_timer_base {
 public:
  k_timer_base() : m_start__{TClock::now()} {}

  void restart() noexcept { m_start__ = TClock::now(); };

  std::size_t seconds() const noexcept {
    return static_cast<std::size_t>(
        std::chrono::duration_cast<std::chrono::seconds>(TClock::now() - m_start__).count());
  }

  std::size_t milliseconds() const noexcept {
    return static_cast<std::size_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(TClock::now() - m_start__).count());
  }

  std::size_t microseconds() const noexcept {
    return static_cast<std::size_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(TClock::now() - m_start__).count());
  }

 private:
  std::chrono::time_point<TClock> m_start__;
}; // class timer_base

using k_timer = k_timer_base<std::chrono::high_resolution_clock>;

} // namespace kore
