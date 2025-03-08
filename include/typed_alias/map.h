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
  using reverse_iterator = typename std::map<K, V>::reverse_iterator;
  using const_reverse_iterator = typename std::map<K, V>::const_reverse_iterator;

  // 反向迭代器函数
  constexpr reverse_iterator rbegin() & noexcept { return Base::get().rbegin(); }
  constexpr const_reverse_iterator rbegin() const& noexcept { return Base::get().rbegin(); }
  constexpr reverse_iterator rend() & noexcept { return Base::get().rend(); }
  constexpr const_reverse_iterator rend() const& noexcept { return Base::get().rend(); }

  constexpr const_reverse_iterator crbegin() const noexcept { return Base::get().crbegin(); }
  constexpr const_reverse_iterator crend() const noexcept { return Base::get().crend(); }
};

template <typename K, typename V, typename Tag>
using MultiMap = Type<std::multimap<K, V>, Tag>;

} // namespace typed_alias
