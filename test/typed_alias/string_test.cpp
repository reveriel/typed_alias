#include <gtest/gtest.h>
#include <typed_alias/string.h>

namespace {

TEST(StringTest, BasicOperations) {
  using Email = typed_alias::String<struct EmailTag>;

  // 测试构造函数
  Email email{"user@domain.com"};
  EXPECT_FALSE(email.empty());
  EXPECT_EQ(email.size(), 15);  // "user@domain.com" 的长度是 15

  // 测试字符串操作
  email += ".cn";
  EXPECT_EQ(email, "user@domain.com.cn");

  // 测试与 std::string 互操作
  std::string str = "other@domain.com";
  Email other(str);
  EXPECT_EQ(other, str);

  // 测试移动语义
  Email moved = std::move(other);
  EXPECT_EQ(moved, str);
  EXPECT_TRUE(other.empty());  // NOLINT: 访问移动后的对象是合法的
}

TEST(StringTest, Conversion) {
  using Email = typed_alias::String<struct EmailTag>;

  // 从字符串构造
  std::string str = "test@example.com";
  Email email(str);
  EXPECT_EQ(email.size(), str.size());
  EXPECT_EQ(email.capacity(), str.capacity());

  // 获取底层引用
  const std::string& ref = email.get();
  EXPECT_EQ(ref, str);

  // 移动转换
  std::string moved = std::move(email).into();
  EXPECT_EQ(moved, str);
  EXPECT_TRUE(email.empty());  // NOLINT
}

}  // namespace
