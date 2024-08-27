#include <algorithm>
#include <cstdint>
#include <kore/containers/heap.hpp>
#include <kore/containers/utility.hpp>
#include <kore/graph/graph.hpp>
#include <kore/type_traits/list.hpp>
#include <kore/utility/timer.hpp>
#include <map>

#include <iostream>

#include <type_traits>
#include <unordered_map>

#include <concepts>

template<class T, class TSize>
concept Reserverable = requires(T a, TSize size) {
  { a.reserve(size) } -> std::same_as<TSize>;
  { a.size() } -> std::convertible_to<TSize>;
};

template<class... TArgs>
class DefaultUnorderedMapReservePolicy {
  using um_type = std::unordered_map<TArgs...>;

 public:
  DefaultUnorderedMapReservePolicy(um_type& um) : um_{um} {}

  decltype(auto) reserve(um_type::size_type size) noexcept(noexcept(um_.reserve(size))) {
    return um_.reserve(size);
  }

 private:
  um_type& um_;
};

template<class... TArgs>
class CustomUnorderedMapReservePolicy {
  using um_type = std::unordered_map<TArgs...>;

  static constexpr std::array<typename um_type::size_type, 4> k_custom_sizes = {1'000, 10'000,
                                                                                100'000, 500'000};
  static constexpr float k_growth_rate = 2;

 public:
  CustomUnorderedMapReservePolicy(um_type& um) : um_{um} { reserve(0); }

  decltype(auto) reserve(um_type::size_type size) noexcept(noexcept(um_.reserve(size))) {
    const auto begin_it = std::begin(k_custom_sizes);
    const auto end_it = std::end(k_custom_sizes);
    if (current_capacity_ < size) {
      const auto result_it =
          std::find_if(begin_it, end_it, [size](const um_type::size_type current_size) {
            return current_size > size;
          });
      if (result_it == end_it) {
        current_capacity_ *= k_growth_rate;
      } else {
        current_capacity_ = *result_it;
      }
    }
    return um_.reserve(current_capacity_);
  }

 private:
  um_type& um_;
  um_type::size_type current_capacity_;
};

template<class... TArgs>
class CustomUnorderedMap : public std::unordered_map<TArgs...> {
  using um_type = std::unordered_map<TArgs...>;

  static constexpr std::array<typename um_type::size_type, 4> k_custom_sizes = {10'000, 100'000,
                                                                                300'000, 500'000};
  static constexpr float k_growth_rate = 2;

 public:
  decltype(auto) reserve(um_type::size_type size) noexcept(noexcept(um_type::reserve(size))) {
    const auto begin_it = std::begin(k_custom_sizes);
    const auto end_it = std::end(k_custom_sizes);
    if (current_capacity_ < size) {
      const auto result_it =
          std::find_if(begin_it, end_it, [size](const um_type::size_type current_size) {
            return current_size > size;
          });
      if (result_it == end_it) {
        current_capacity_ *= k_growth_rate;
      } else {
        current_capacity_ = *result_it;
      }
    }
    return um_type::reserve(current_capacity_);
  }

 private:
  um_type::size_type current_capacity_;
};

template<class TReservePolicy, class... TArgs>
class unordered_map_rp : public std::unordered_map<TArgs...> {
  using basic_type = std::unordered_map<TArgs...>;

 public:
  unordered_map_rp() {}
};

struct A {
  void reserve() { i = 1; }

  void try_reserve() { reserve(); }

  int i = 0;
};

struct B : public A {
  void reserve() { i = 2; }
};

int main() {
  B b;
  b.try_reserve();
  std::cout << b.i << std::endl;

  constexpr std::size_t k_limit = 500'000;
  // kore::graph::default_graph gr;
  {
    kore::k_timer t;
    std::unordered_map<std::size_t, std::size_t> test_map;
    for (std::size_t i = 0; i < k_limit; ++i) {
      test_map.emplace(i, i);
    }
    std::cout << t.milliseconds() << std::endl;
  }
  {
    kore::k_timer t;
    std::unordered_map<std::size_t, std::size_t> test_map;
    for (std::size_t i = 0; i < k_limit; ++i) {
      if (i % 1'000 == 0) {
        test_map.reserve(i);
      }
      test_map.emplace(i, i);
    }
    std::cout << t.milliseconds() << std::endl;
  }
  {
    kore::k_timer t;
    std::unordered_map<std::size_t, std::size_t> test_map;
    for (std::size_t i = 0; i < k_limit; ++i) {
      if (i % 1'000 == 0) {
        test_map.reserve(i * 2 + 1);
      }
      test_map.emplace(i, i);
    }
    std::cout << t.milliseconds() << std::endl;
  }
  {
    kore::k_timer t;
    std::unordered_map<std::size_t, std::size_t> test_map;
    CustomUnorderedMapReservePolicy policy{test_map};
    for (std::size_t i = 0; i < k_limit; ++i) {
      if (i % 1'000 == 0) {
        policy.reserve(i * 2 + 1);
      }
      test_map.emplace(i, i);
    }
    std::cout << t.milliseconds() << std::endl;
    t.restart();
  }
  {
    kore::k_timer t;
    CustomUnorderedMap<std::size_t, std::size_t> test_map;
    for (std::size_t i = 0; i < k_limit; ++i) {
      if (i % 1'000 == 0) {
        test_map.reserve(i * 2 + 1);
      }
      test_map.emplace(i, i);
    }
    std::cout << t.milliseconds() << std::endl;
    t.restart();
  }

  return 0;
}
