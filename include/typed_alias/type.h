#pragma once
#include <type_traits>
#include <initializer_list>

namespace typed_alias {

// 基础的 Type 实现
template <typename T, typename Tag>
class Type : public T {
public:
  using T::T;  // 继承所有构造函数
  using typename T::iterator;
  using typename T::const_iterator;

  // 默认构造函数
  constexpr Type() = default;

  // 拷贝和移动操作 - 根据基类的行为来决定是否启用
  constexpr Type(const Type&) = default;
  constexpr Type& operator=(const Type&) = default;
  constexpr Type(Type&&) = default;
  constexpr Type& operator=(Type&&) = default;

  // 从基类构造
  constexpr explicit Type(const T& value) : T(value) {}
  constexpr explicit Type(T&& value) : T(std::move(value)) {}

  // 初始化列表构造函数
  template <typename U,
            typename = std::enable_if_t<std::is_constructible_v<T, std::initializer_list<U>>>>
  constexpr Type(std::initializer_list<U> init) : T(init) {}

  // 基本迭代器函数
  constexpr iterator begin() & noexcept { return T::begin(); }
  constexpr const_iterator begin() const& noexcept { return T::begin(); }
  constexpr iterator end() & noexcept { return T::end(); }
  constexpr const_iterator end() const& noexcept { return T::end(); }

  constexpr const_iterator cbegin() const noexcept { return T::cbegin(); }
  constexpr const_iterator cend() const noexcept { return T::cend(); }

  // 获取底层值的引用
  constexpr const T& get() const& noexcept {
    return static_cast<const T&>(*this);
  }

  constexpr T& get() & noexcept {
    return static_cast<T&>(*this);
  }

  constexpr T&& get() && noexcept {
    return static_cast<T&&>(*this);
  }

  // 工厂方法
  static Type from(const T& value) {
    return Type(value);
  }

  static Type from(T&& value) {
    return Type(std::move(value));
  }
};

// 基于组合的 Wrapper 实现
template <typename T, typename Tag>
class Wrapper {
private:
  T value_;

public:
  // 构造函数
  constexpr explicit Wrapper(const T& value) : value_(value) {}
  constexpr explicit Wrapper(T&& value) : value_(std::move(value)) {}

  // 拷贝和移动操作
  constexpr Wrapper(const Wrapper&) = default;
  constexpr Wrapper& operator=(const Wrapper&) = default;
  constexpr Wrapper(Wrapper&&) noexcept = default;
  constexpr Wrapper& operator=(Wrapper&&) noexcept = default;

  // 类型转换
  constexpr operator T&() { return value_; }
  constexpr operator const T&() const { return value_; }
};

} // namespace typed_alias
