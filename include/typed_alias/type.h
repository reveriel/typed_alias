#pragma once

#include <algorithm>  // for std::copy_n, std::min
#include <array>      // for std::array
#include <initializer_list>
#include <type_traits>
#include <utility>

namespace typed_alias {

namespace detail {
// 类型选择器：基于类型特征选择不同的基类
template <typename T, bool IsClass>
struct base_type;

template <typename T>
struct base_type<T, true> {  // 类类型用继承
  using type = T;
};

template <typename T>
struct base_type<T, false> {  // 非类类型用组合
  struct type {
  protected:
    T value_;

    constexpr type() = default;
    constexpr explicit type(const T& v) : value_(v) {}
    constexpr explicit type(T&& v) : value_(std::move(v)) {}
  };
};

}  // namespace detail

// Type 的统一实现
template <typename T, typename Tag = void>
class Type : public detail::base_type<T, std::is_class_v<T>>::type {
private:
  using Base = typename detail::base_type<T, std::is_class_v<T>>::type;

public:
  // 构造函数
  constexpr Type() = default;

  template <typename U, typename = std::enable_if_t<std::is_constructible_v<T, U>>>
  constexpr explicit Type(U&& value) : Base(std::forward<U>(value)) {}

  // 拷贝和移动操作
  constexpr Type(const Type&) = default;
  constexpr Type& operator=(const Type&) = default;
  constexpr Type(Type&&) = default;
  constexpr Type& operator=(Type&&) = default;
  // 构造 from underlying type
  constexpr Type(const T& value) : Base(value) {}
  constexpr Type(T&& value) : Base(std::move(value)) {}
  // 赋值 from underlying type
  constexpr Type& operator=(const T& value) {
    Base::value_ = value;
    return *this;
  }
  constexpr Type& operator=(T&& value) {
    Base::value_ = std::move(value);
    return *this;
  }

  // 获取底层值
  constexpr const T& get() const& noexcept {
    if constexpr (std::is_class_v<T>) {
      return static_cast<const T&>(*this);
    } else {
      return this->value_;
    }
  }

  constexpr T& get() & noexcept {
    if constexpr (std::is_class_v<T>) {
      return static_cast<T&>(*this);
    } else {
      return this->value_;
    }
  }

  constexpr T&& get() && noexcept {
    if constexpr (std::is_class_v<T>) {
      return static_cast<T&&>(*this);
    } else {
      return std::move(this->value_);
    }
  }

  // 迭代器函数（仅当 T 支持时启用）
  template <typename U = T>
  constexpr auto begin() & noexcept -> decltype(std::declval<U&>().begin()) {
    return get().begin();
  }

  template <typename U = T>
  constexpr auto begin() const& noexcept -> decltype(std::declval<const U&>().begin()) {
    return get().begin();
  }

  template <typename U = T>
  constexpr auto end() & noexcept -> decltype(std::declval<U&>().end()) {
    return get().end();
  }

  template <typename U = T>
  constexpr auto end() const& noexcept -> decltype(std::declval<const U&>().end()) {
    return get().end();
  }

  template <typename U = T>
  constexpr auto cbegin() const noexcept -> decltype(std::declval<const U&>().cbegin()) {
    return get().cbegin();
  }

  template <typename U = T>
  constexpr auto cend() const noexcept -> decltype(std::declval<const U&>().cend()) {
    return get().cend();
  }

  // 到底层类型的转换（仅对基本类型启用）
  template <typename U = T, typename = std::enable_if_t<!std::is_class_v<U>>>
  constexpr operator const T&() const& noexcept {
    return this->value_;
  }

  template <typename U = T, typename = std::enable_if_t<!std::is_class_v<U>>>
  constexpr operator T&() & noexcept {
    return this->value_;
  }

  // 比较运算符
  friend constexpr bool operator==(const Type& lhs, const Type& rhs) noexcept {
    return lhs.get() == rhs.get();
  }

  friend constexpr bool operator!=(const Type& lhs, const Type& rhs) noexcept {
    return !(lhs == rhs);
  }

  friend constexpr bool operator<(const Type& lhs, const Type& rhs) noexcept {
    return lhs.get() < rhs.get();
  }

  friend constexpr bool operator<=(const Type& lhs, const Type& rhs) noexcept {
    return !(rhs < lhs);
  }

  friend constexpr bool operator>(const Type& lhs, const Type& rhs) noexcept {
    return rhs < lhs;
  }

  friend constexpr bool operator>=(const Type& lhs, const Type& rhs) noexcept {
    return !(lhs < rhs);
  }
};

}  // namespace typed_alias
