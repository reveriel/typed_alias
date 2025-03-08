#pragma once
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace typed_alias {

// Inheritance-based strong type using private inheritance
template <typename T, typename Tag>
class Type : private T {
public:
  using underlying_type = T;

  // Perfect forwarding constructor
  template <typename... Args, typename = std::enable_if_t<std::is_constructible_v<T, Args...>>>
  explicit Type(Args&&... args) : T(std::forward<Args>(args)...) {}

  // 从底层类型构造
  explicit Type(const T& value) : T(value) {}
  explicit Type(T&& value) : T(std::move(value)) {}

  // 访问基类成员
  using T::operator=;
  using T::swap;

  // 转换到底层类型
  operator const T&() const& noexcept {
    return static_cast<const T&>(*this);
  }
  operator T&() & noexcept {
    return static_cast<T&>(*this);
  }
  operator T&&() && noexcept {
    return static_cast<T&&>(*this);
  }

  // 获取底层值的引用
  const T& get() const& noexcept {
    return static_cast<const T&>(*this);
  }
  T& get() & noexcept {
    return static_cast<T&>(*this);
  }
  T&& get() && noexcept {
    return static_cast<T&&>(*this);
  }

  // 转换到底层类型
  T into() && noexcept {
    return std::move(get());
  }

  // 从底层类型创建
  static Type from(const T& value) {
    return Type(value);
  }
  static Type from(T&& value) {
    return Type(std::move(value));
  }

  // Explicit conversion to underlying type
  // operator const T&() const noexcept {
  //   return *this;
  // }
  // operator T&() noexcept {
  //   return *this;
  // }

  // Forwarding of all public member functions
  using T::begin;
  using T::empty;
  using T::end;
  using T::size;
  //... other common STL member functions
};


// Specializations for common STL containers
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
template <typename Tag>
using String = Type<std::string, Tag>;

template <typename T, typename Tag>
class Type<std::vector<T>, Tag> : public std::vector<T> {
public:
  using std::vector<T>::vector;
  using std::vector<T>::operator=;
  using std::vector<T>::begin;
  using std::vector<T>::end;
  using std::vector<T>::size;
  using std::vector<T>::empty;
  // ... other vector methods
};

template <typename T, typename Tag>
using Vector = Type<std::vector<T>, Tag>;

}  // namespace typed_alias
