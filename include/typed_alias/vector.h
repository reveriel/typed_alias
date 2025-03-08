#pragma once

#include "typed_alias/type.h"
#include <vector>

namespace typed_alias {

template <typename T, typename Tag>
class Vector : public Type<std::vector<T>, Tag> {
 public:
  using Base = Type<std::vector<T>, Tag>;
  using Base::Base;  // 继承构造函数
  using typename Base::iterator;
  using typename Base::const_iterator;
  using reverse_iterator = typename std::vector<T>::reverse_iterator;
  using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

  constexpr Vector(std::initializer_list<T> init) : Base(std::vector<T>(init)) {}
  // 反向迭代器函数
  constexpr reverse_iterator rbegin() & noexcept { return Base::get().rbegin(); }
  constexpr const_reverse_iterator rbegin() const& noexcept { return Base::get().rbegin(); }
  constexpr reverse_iterator rend() & noexcept { return Base::get().rend(); }
  constexpr const_reverse_iterator rend() const& noexcept { return Base::get().rend(); }

  constexpr const_reverse_iterator crbegin() const noexcept { return Base::get().crbegin(); }
  constexpr const_reverse_iterator crend() const noexcept { return Base::get().crend(); }
};

} // namespace typed_alias
