#pragma once

#include <unordered_set>

#include "typed_alias/type.h"

namespace typed_alias {

template <typename T, typename Tag>
class UnorderedSet : public Type<std::unordered_set<T>, Tag> {
public:
  using Base = Type<std::unordered_set<T>, Tag>;
  using Base::Base;  // 继承构造函数
  using value_type = T;
  using container_type = std::unordered_set<T>;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;

  // 默认构造函数
  constexpr UnorderedSet() = default;

  // 初始化列表构造函数
  constexpr UnorderedSet(std::initializer_list<T> init)
      : Base(container_type(init.begin(), init.end())) {}
};

template <typename T, typename Tag>
class UnorderedMultiSet : public Type<std::unordered_multiset<T>, Tag> {
public:
  using Base = Type<std::unordered_multiset<T>, Tag>;
  using Base::Base;  // 继承构造函数
  using value_type = T;
  using container_type = std::unordered_multiset<T>;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  // 默认构造函数
  constexpr UnorderedMultiSet() = default;

  // 初始化列表构造函数
  constexpr UnorderedMultiSet(std::initializer_list<T> init)
      : Base(container_type(init.begin(), init.end())) {}
};

}  // namespace typed_alias
