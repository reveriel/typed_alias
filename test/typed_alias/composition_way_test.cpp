#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Composition-based wrapper with explicit forwarding
template <typename T, typename Tag>
class Wrapper {
  T value;

public:
  template <typename... Args, typename = std::enable_if_t<std::is_constructible_v<T, Args...>>>
  explicit Wrapper(Args&&... args) : value(std::forward<Args>(args)...) {}

// Forward member functions using macro
#define FORWARD_METHOD(method)                        \
  template <typename... Args>                         \
  decltype(auto) method(Args&&... args) {             \
    return value.method(std::forward<Args>(args)...); \
  }

  FORWARD_METHOD(begin)
  FORWARD_METHOD(end)
  FORWARD_METHOD(size)
  FORWARD_METHOD(empty)
  FORWARD_METHOD(operator[])
  //... expand for other needed methods

#undef FORWARD_METHOD

  // Conversion operators
  explicit operator const T&() const noexcept {
    return value;
  }
  explicit operator T&() noexcept {
    return value;
  }
};

// 测试组合方式
TEST(TypeTest, CompositionApproach) {
  using UserId = Wrapper<int, struct UserIdTag>;  // 注意这里不再使用 typed_alias 命名空间
  UserId id{42};
  UserId id2{43};

  // 测试值访问
  EXPECT_EQ(static_cast<int&>(id), 42);

  // 测试修改
  static_cast<int&>(id) = 43;
  EXPECT_EQ(static_cast<int&>(id), 43);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
