#pragma once

#include "typed_alias/type.h"
#include <array>

namespace typed_alias {

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

    // 反向迭代器函数
    constexpr reverse_iterator rbegin() & noexcept { return Base::get().rbegin(); }
    constexpr const_reverse_iterator rbegin() const& noexcept { return Base::get().rbegin(); }
    constexpr reverse_iterator rend() & noexcept { return Base::get().rend(); }
    constexpr const_reverse_iterator rend() const& noexcept { return Base::get().rend(); }

    constexpr const_reverse_iterator crbegin() const noexcept { return Base::get().crbegin(); }
    constexpr const_reverse_iterator crend() const noexcept { return Base::get().crend(); }
};

} // namespace typed_alias
