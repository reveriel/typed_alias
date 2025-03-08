#pragma once

#include "typed_alias/type.h"
#include <deque>

namespace typed_alias {

template <typename T, typename Tag>
class Deque : public Type<std::deque<T>, Tag> {
 public:
  using Base = Type<std::deque<T>, Tag>;
  using Base::Base;  // 继承构造函数
  using typename Base::iterator;
  using typename Base::const_iterator;
  using reverse_iterator = typename std::deque<T>::reverse_iterator;
  using const_reverse_iterator = typename std::deque<T>::const_reverse_iterator;

  // 反向迭代器函数
  constexpr reverse_iterator rbegin() & noexcept { return Base::get().rbegin(); }
  constexpr const_reverse_iterator rbegin() const& noexcept { return Base::get().rbegin(); }
  constexpr reverse_iterator rend() & noexcept { return Base::get().rend(); }
  constexpr const_reverse_iterator rend() const& noexcept { return Base::get().rend(); }

  constexpr const_reverse_iterator crbegin() const noexcept { return Base::get().crbegin(); }
  constexpr const_reverse_iterator crend() const noexcept { return Base::get().crend(); }
};

} // namespace typed_alias
