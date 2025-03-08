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

// 检查类型是否是关联容器
template <typename, typename = void>
struct is_associative_container : std::false_type {};

// 检查类型是否有 key_type 和 mapped_type
template <typename T, typename = void>
struct has_key_mapped_types : std::false_type {};

template <typename T>
struct has_key_mapped_types<T, std::void_t<typename T::key_type, typename T::mapped_type>>
    : std::true_type {};

template <typename T>
inline constexpr bool has_key_mapped_types_v = has_key_mapped_types<T>::value;

// Specialization for associative containers
template <typename T>
struct is_associative_container<
    T, std::void_t<typename T::key_type, typename T::mapped_type, typename T::value_type,
                   decltype(std::declval<typename T::value_type&>().first),
                   decltype(std::declval<typename T::value_type&>().second)>> : std::true_type {};

template <typename T>
inline constexpr bool is_associative_container_v = is_associative_container<T>::value;

// 检查类型是否支持初始化列表构造
template <typename T, typename U, typename = void>
struct is_initializer_list_constructible : std::false_type {};

template <typename T, typename U>
struct is_initializer_list_constructible<
    T, U, std::void_t<decltype(T(std::declval<std::initializer_list<U>>()))>> : std::true_type {};

template <typename T, typename U>
inline constexpr bool is_initializer_list_constructible_v =
    is_initializer_list_constructible<T, U>::value;

// 检查容器是否支持 push_back 操作
template <typename T, typename U, typename = void>
struct has_push_back : std::false_type {};

template <typename T, typename U>
struct has_push_back<T, U, std::void_t<decltype(std::declval<T&>().push_back(std::declval<U>()))>>
    : std::true_type {};

template <typename T, typename U>
inline constexpr bool has_push_back_v = has_push_back<T, U>::value;

// 检查容器是否支持 push_front 操作
template <typename T, typename U, typename = void>
struct has_push_front : std::false_type {};

template <typename T, typename U>
struct has_push_front<T, U, std::void_t<decltype(std::declval<T&>().push_front(std::declval<U>()))>>
    : std::true_type {};

template <typename T, typename U>
inline constexpr bool has_push_front_v = has_push_front<T, U>::value;

// 检查容器是否支持 insert 操作
template <typename T, typename U, typename = void>
struct has_insert : std::false_type {};

template <typename T, typename U>
struct has_insert<T, U, std::void_t<decltype(std::declval<T&>().insert(std::declval<U>()))>>
    : std::true_type {};

template <typename T, typename U>
inline constexpr bool has_insert_v = has_insert<T, U>::value;

// 检查容器是否支持 emplace 操作
template <typename T, typename U, typename = void>
struct has_emplace : std::false_type {};

template <typename T, typename U>
struct has_emplace<T, U, std::void_t<decltype(std::declval<T&>().emplace(std::declval<U>()))>>
    : std::true_type {};

// 检查容器是否支持 reverse 操作
template <typename T, typename = void>
struct has_reverse : std::false_type {};

template <typename T>
struct has_reverse<T, std::void_t<decltype(std::declval<T&>().reverse())>> : std::true_type {};

template <typename T>
inline constexpr bool has_reverse_v = has_reverse<T>::value;

// 检查类型是否是容器
template <typename T, typename = void>
struct is_container : std::false_type {};

template <typename T>
struct is_container<
    T, std::void_t<typename T::value_type, typename T::iterator, typename T::const_iterator,
                   decltype(std::declval<T&>().begin()), decltype(std::declval<T&>().end())>>
    : std::true_type {};

template <typename T>
inline constexpr bool is_container_v = is_container<T>::value;

// 检查类型是否是序列容器 (更宽松的定义)
template <typename T, typename = void>
struct is_sequence_container : std::false_type {};

template <typename T>
struct is_sequence_container<
    T, std::void_t<typename T::value_type, typename T::iterator, typename T::const_iterator,
                   decltype(std::declval<T&>().begin()), decltype(std::declval<T&>().end())>>
    : std::true_type {};

template <typename T>
inline constexpr bool is_sequence_container_v = is_sequence_container<T>::value;

// 检查类型是否支持size()方法
template <typename T, typename = void>
struct has_size : std::false_type {};

template <typename T>
struct has_size<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type {};

template <typename T>
inline constexpr bool has_size_v = has_size<T>::value;

// 检查类型是否支持迭代器范围构造
template <typename T, typename It, typename = void>
struct is_range_constructible : std::false_type {};

template <typename T, typename It>
struct is_range_constructible<T, It,
                              std::void_t<decltype(T(std::declval<It>(), std::declval<It>()))>>
    : std::true_type {};

template <typename T, typename It>
inline constexpr bool is_range_constructible_v = is_range_constructible<T, It>::value;

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
