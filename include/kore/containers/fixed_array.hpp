// ------------------------------------------------------------------------------------------------
// Copyright (C) 2024 Korobov Vladislav
// ------------------------------------------------------------------------------------------------

#pragma once

//- std -------------------------------------------------------------------------------------------
#include <memory>
#include <type_traits>
#include <utility>
// ------------------------------------------------------------------------------------------------

namespace kore {

namespace impl {

struct k_generate_tag final {
  explicit k_generate_tag() = default;
}; // struct k_generate_tag

} // namespace impl

template<class T, class TAllocator = std::allocator<T>>
class k_fixed_array final {
 public:
  using iterator = T*;
  using const_iterator = const T*;
  using allocator_type = TAllocator;

  k_fixed_array() = default;

  template<class... Args>
  explicit k_fixed_array(const std::size_t size, Args&&... args);

  k_fixed_array(const k_fixed_array&) = delete;
  k_fixed_array& operator=(const k_fixed_array&) = delete;

  k_fixed_array(k_fixed_array&& other) noexcept;
  k_fixed_array& operator=(k_fixed_array&& other) noexcept;

  ~k_fixed_array();

  std::size_t size() const noexcept { return m_size__; }
  bool empty() const noexcept { return m_size__ == 0; }

  const T& operator[](const std::size_t i) const noexcept { return data()[i]; }

  T& operator[](const std::size_t i) noexcept { return data()[i]; }

  T& front() noexcept { return *m_data__; }
  const T& front() const noexcept { return *m_data__; }

  T& back() noexcept { return *(m_data__ + m_size__ - 1); }
  const T& back() const noexcept { return *(m_data__ + m_size__ - 1); }

  T* data() noexcept { return m_data__; }
  const T* data() const noexcept { return m_data__; }

  T* begin() noexcept { return data(); }
  T* end() noexcept { return data() + m_size__; }
  const T* begin() const noexcept { return data(); }
  const T* end() const noexcept { return data() + m_size__; }
  const T* cbegin() const noexcept { return data(); }
  const T* cend() const noexcept { return data() + m_size__; }

  template<class TGeneratorFunc>
  k_fixed_array(impl::k_generate_tag /*tag*/, const std::size_t size, TGeneratorFunc&& generator);

 private:
  T* m_data__{nullptr};
  std::size_t m_size__{0};
};

template<class T, class TAllocator>
template<class... Args>
k_fixed_array<T, TAllocator>::k_fixed_array(const std::size_t size, Args&&... args)
    : m_size__(size) {
  if (m_size__ == 0) {
    return;
  }
  m_data__ = allocator_type{}.allocate(m_size__);

  auto* begin = data();
  try {
    for (const auto* end = begin + size - 1; begin != end; ++begin) {
      new (begin) T(args...);
    }
    new (begin) T(std::forward<Args>(args)...);
  } catch (...) {
    std::destroy(data(), begin);
    allocator_type{}.deallocate(m_data__, size);
    throw;
  }
}

template<class T, class TAllocator>
template<class TGeneratorFunc>
k_fixed_array<T, TAllocator>::k_fixed_array(const impl::k_generate_tag /*tag*/,
                                            const std::size_t size, TGeneratorFunc&& generator)
    : m_size__(size) {
  if (m_size__ == 0) {
    return;
  }
  m_data__ = allocator_type{}.allocate(m_size__);

  auto* current_it = begin();
  auto* const end_it = end();
  std::size_t index = 0;

  try {
    for (; current_it != end_it; ++current_it) {
      new (current_it) T{generator(index)};
      ++index;
    }
  } catch (...) {
    std::destroy(begin(), current_it);
    allocator_type{}.deallocate(m_data__, m_size__);
    throw;
  }
}

template<class T, class TAllocator>
k_fixed_array<T, TAllocator>::k_fixed_array(k_fixed_array&& other) noexcept
    : m_data__{std::exchange(other.m_data__, nullptr)}, m_size__{std::exchange(other.m_size__, 0)} {
}

template<class T, class TAllocator>
k_fixed_array<T, TAllocator>&
k_fixed_array<T, TAllocator>::operator=(k_fixed_array&& other) noexcept {
  std::swap(m_data__, other.m_data__);
  std::swap(m_size__, other.m_size__);
  return *this;
}

template<class T, class TAllocator>
k_fixed_array<T, TAllocator>::~k_fixed_array() {
  std::destroy(begin(), end());
  allocator_type{}.deallocate(m_data__, m_size__);
}

template<class TGeneratorFunc>
auto make_k_fixed_array(const std::size_t size, TGeneratorFunc&& generator) {
  using TResult = std::remove_reference_t<std::invoke_result_t<TGeneratorFunc&, std::size_t>>;
  return k_fixed_array<TResult>(impl::k_generate_tag{}, size,
                                std::forward<TGeneratorFunc>(generator));
}

} // namespace kore
