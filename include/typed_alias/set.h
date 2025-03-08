#pragma once

#include <set>

#include "typed_alias/type.h"

namespace typed_alias {

template <typename T, typename Tag>
class Set : public Type<std::set<T>, Tag> {
public:
  using Base = Type<std::set<T>, Tag>;
  using Base::Base;  // 继承构造函数
  using value_type = T;
  using container_type = std::set<T>;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;

  // 默认构造函数
  constexpr Set() = default;

  // 初始化列表构造函数
  constexpr Set(std::initializer_list<T> init) : Base(container_type(init.begin(), init.end())) {}
};

template <typename T, typename Tag>
class MultiSet : public Type<std::multiset<T>, Tag> {
public:
  using Base = Type<std::multiset<T>, Tag>;
  using Base::Base;  // 继承构造函数
  using value_type = T;
  using container_type = std::multiset<T>;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;

  // 初始化列表构造函数
  constexpr MultiSet(std::initializer_list<T> init)
      : Base(container_type(init.begin(), init.end())) {}
};

}  // namespace typed_alias
