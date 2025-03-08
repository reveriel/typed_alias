#include <gtest/gtest.h>
#include <typed_alias/type.h>

namespace {

TEST(TypeTest, SizeAndPerformance) {
  using Email = typed_alias::Type<std::string, struct EmailTag>;

  // 测试大小相等
  EXPECT_EQ(sizeof(Email), sizeof(std::string));

  // 测试内存对齐
  EXPECT_EQ(alignof(Email), alignof(std::string));

  // 验证是否是标准布局类型
  EXPECT_EQ(std::is_standard_layout_v<Email>, std::is_standard_layout_v<std::string>);

  // 验证是否可平凡复制
  EXPECT_EQ(std::is_trivially_copyable_v<Email>, std::is_trivially_copyable_v<std::string>);
}

}  // namespace
