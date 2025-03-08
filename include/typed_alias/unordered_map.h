#pragma once

#include <unordered_map>

#include "typed_alias/type.h"

namespace typed_alias {

template <typename K, typename V, typename Tag>
class UnorderedMap : public Type<std::unordered_map<K, V>, Tag> {
public:
  using Base = Type<std::unordered_map<K, V>, Tag>;
  using Base::Base;  // 继承构造函数
  using value_type = std::pair<const K, V>;
  using container_type = std::unordered_map<K, V>;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;

  constexpr UnorderedMap(std::initializer_list<value_type> init)
      : Base(container_type(init.begin(), init.end())) {}
};

template <typename K, typename V, typename Tag>
class UnorderedMultiMap : public Type<std::unordered_multimap<K, V>, Tag> {
public:
  using Base = Type<std::unordered_multimap<K, V>, Tag>;
  using Base::Base;  // 继承构造函数
  using value_type = std::pair<const K, V>;
  using container_type = std::unordered_multimap<K, V>;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;

  constexpr UnorderedMultiMap(std::initializer_list<value_type> init)
      : Base(container_type(init.begin(), init.end())) {}
};

}  // namespace typed_alias
