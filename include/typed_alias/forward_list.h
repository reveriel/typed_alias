#pragma once

#include <forward_list>
#include <string>
#include <vector>

#include "typed_alias/type.h"

namespace typed_alias {

// Generic ForwardList definition
template <typename T, typename Tag>
class ForwardList : public Type<std::forward_list<T>, Tag> {
private:
  using Base = Type<std::forward_list<T>, Tag>;

public:
  using value_type = T;
  using container_type = std::forward_list<T>;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;

  // Inherit all constructors from the base class
  using Base::Base;

  // 默认构造函数
  constexpr ForwardList() = default;

  // 初始化列表构造函数
  constexpr ForwardList(std::initializer_list<T> init)
      : Base(container_type(init.begin(), init.end())) {}
};

}  // namespace typed_alias
