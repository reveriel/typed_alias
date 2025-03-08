#pragma once

#include <list>

#include "typed_alias/type.h"

namespace typed_alias {

template <typename T, typename Tag>
class List : public Type<std::list<T>, Tag> {
public:
  using Base = Type<std::list<T>, Tag>;
  using Base::Base;  // 继承构造函数
  using value_type = T;
  using container_type = std::list<T>;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;

  // 默认构造函数
  constexpr List() = default;

  // 初始化列表构造函数
  constexpr List(std::initializer_list<T> init) : Base(container_type(init.begin(), init.end())) {}

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
