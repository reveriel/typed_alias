#pragma once

#include <deque>

#include "typed_alias/type.h"

namespace typed_alias {

// Generic Deque definition
template <typename T, typename Tag>
class Deque : public Type<std::deque<T>, Tag> {
public:
  using Base = Type<std::deque<T>, Tag>;
  using Base::Base;  // 继承构造函数
  using value_type = T;
  using container_type = std::deque<T>;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;

  // 默认构造函数
  constexpr Deque() = default;

  // 初始化列表构造函数
  constexpr Deque(std::initializer_list<T> init) : Base(container_type(init.begin(), init.end())) {}

  // 反向迭代器函数
  constexpr reverse_iterator rbegin() & noexcept {
    return Base::get().rbegin();
  }
  constexpr const_reverse_iterator rbegin() const& noexcept {
    return Base::get().rbegin();
  }
  constexpr reverse_iterator rend() & noexcept {
    return Base::get().rend();
  }
  constexpr const_reverse_iterator rend() const& noexcept {
    return Base::get().rend();
  }

  constexpr const_reverse_iterator crbegin() const noexcept {
    return Base::get().crbegin();
  }
  constexpr const_reverse_iterator crend() const noexcept {
    return Base::get().crend();
  }
};

}  // namespace typed_alias
