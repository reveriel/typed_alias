#pragma once

#include "typed_alias/type.h"
#include <array>

namespace typed_alias {

namespace detail {

// 检查类型是否是 std::array
template <typename T>
struct is_array : std::false_type {};

template <typename T, std::size_t N>
struct is_array<std::array<T, N>> : std::true_type {};

template <typename T>
inline constexpr bool is_array_v = is_array<T>::value;

// 获取 std::array 的元素类型
template <typename T>
struct array_value_type {
  using type = void;
};

template <typename T, std::size_t N>
struct array_value_type<std::array<T, N>> {
  using type = T;
};

template <typename T>
using array_value_type_t = typename array_value_type<T>::type;

// 获取 std::array 的大小
template <typename T>
struct array_size : std::integral_constant<std::size_t, 0> {};

template <typename T, std::size_t N>
struct array_size<std::array<T, N>> : std::integral_constant<std::size_t, N> {};

template <typename T>
inline constexpr std::size_t array_size_v = array_size<T>::value;

}  // namespace detail

// Array 的特化实现
template <typename T, std::size_t N, typename Tag>
class Array : public Type<std::array<T, N>, Tag> {
public:
    using Base = Type<std::array<T, N>, Tag>;
    using Base::Base;  // 继承基类构造函数
    using typename Base::iterator;
    using typename Base::const_iterator;
    using reverse_iterator = typename std::array<T, N>::reverse_iterator;
    using const_reverse_iterator = typename std::array<T, N>::const_reverse_iterator;

    // 特殊的聚合初始化支持
    template<typename... Args, 
             typename = std::enable_if_t<sizeof...(Args) == N &&
                                       (std::is_convertible_v<Args, T> && ...)>>
    constexpr Array(Args&&... args) 
        : Base{std::array<T, N>{static_cast<T>(std::forward<Args>(args))...}} {}

    // 初始化列表构造函数
    template <typename U>
    constexpr Array(std::initializer_list<U> init,
                   typename std::enable_if_t<std::is_convertible_v<U, T>, int> = 0)
        : Base([&init]() {
            std::array<T, N> arr{};
            auto it = init.begin();
            for (std::size_t i = 0; i < std::min(init.size(), N); ++i, ++it) {
                arr[i] = static_cast<T>(*it);
            }
            return arr;
          }()) {}

    // 反向迭代器函数
    constexpr reverse_iterator rbegin() & noexcept { return Base::get().rbegin(); }
    constexpr const_reverse_iterator rbegin() const& noexcept { return Base::get().rbegin(); }
    constexpr reverse_iterator rend() & noexcept { return Base::get().rend(); }
    constexpr const_reverse_iterator rend() const& noexcept { return Base::get().rend(); }

    constexpr const_reverse_iterator crbegin() const noexcept { return Base::get().crbegin(); }
    constexpr const_reverse_iterator crend() const noexcept { return Base::get().crend(); }
};

}  // namespace typed_alias
