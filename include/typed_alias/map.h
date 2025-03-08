#pragma once

#include "typed_alias/type.h"
#include <map>

namespace typed_alias {

template <typename K, typename V, typename Tag>
class Map : public Type<std::map<K, V>, Tag> {
 public:
  using Base = Type<std::map<K, V>, Tag>;
  using Base::Base;  // 继承构造函数
  using typename Base::iterator;
  using typename Base::const_iterator;
  using value_type = std::pair<const K, V>;
  using container_type = std::map<K, V>;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;
  
  // 默认构造函数
  constexpr Map() = default;
  
  // 初始化列表构造函数
  constexpr Map(std::initializer_list<value_type> init) : Base(container_type(init.begin(), init.end())) {}
};

template <typename K, typename V, typename Tag>
class MultiMap : public Type<std::multimap<K, V>, Tag> {
 public:
  using Base = Type<std::multimap<K, V>, Tag>;
  using Base::Base;  // 继承构造函数
  using typename Base::iterator;
  using typename Base::const_iterator;
  using value_type = std::pair<const K, V>;
  using container_type = std::multimap<K, V>;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;
  
  // 默认构造函数
  constexpr MultiMap() = default;
  
  // 初始化列表构造函数
  constexpr MultiMap(std::initializer_list<value_type> init) : Base(container_type(init.begin(), init.end())) {}
};

} // namespace typed_alias
