#pragma once
#include <string>

#include "type.h"

namespace typed_alias {

// String 特化
template <typename Tag>
class Type<std::string, Tag> : public std::string {
public:
  using std::string::string;  // 继承所有构造函数

  // 从底层类型构造
  explicit Type(const std::string& value) : std::string(value) {}
  explicit Type(std::string&& value) : std::string(std::move(value)) {}

  // 获取底层值的引用
  const std::string& get() const& noexcept {
    return static_cast<const std::string&>(*this);
  }
  std::string& get() & noexcept {
    return static_cast<std::string&>(*this);
  }
  std::string&& get() && noexcept {
    return static_cast<std::string&&>(*this);
  }

  // 转换到底层类型
  std::string into() && noexcept {
    return std::move(get());
  }

  // 从底层类型创建
  static Type from(const std::string& value) {
    return Type(value);
  }
  static Type from(std::string&& value) {
    return Type(std::move(value));
  }
};

// 便捷别名
template <typename Tag>
using String = Type<std::string, Tag>;

}  // namespace typed_alias
