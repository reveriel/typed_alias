#include <gtest/gtest.h>
#include <typed_alias/type.h>
#include <vector>

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

TEST(TypeTest, Iterators) {
  // 测试继承的迭代器接口
  using Numbers = typed_alias::Type<std::vector<int>, struct NumbersTag>;
  Numbers nums{1, 2, 3, 4, 5};

  // begin/end
  EXPECT_EQ(*nums.begin(), 1);
  EXPECT_EQ(*(nums.end() - 1), 5);
  EXPECT_EQ(nums.end() - nums.begin(), 5);

  // const begin/end
  const Numbers& const_nums = nums;
  EXPECT_EQ(*const_nums.begin(), 1);
  EXPECT_EQ(*(const_nums.end() - 1), 5);

  // rbegin/rend
  EXPECT_EQ(*nums.rbegin(), 5);
  EXPECT_EQ(*(nums.rend() - 1), 1);

  // const rbegin/rend
  EXPECT_EQ(*const_nums.rbegin(), 5);
  EXPECT_EQ(*(const_nums.rend() - 1), 1);

  // cbegin/cend
  EXPECT_EQ(*nums.cbegin(), 1);
  EXPECT_EQ(*(nums.cend() - 1), 5);

  // crbegin/crend
  EXPECT_EQ(*nums.crbegin(), 5);
  EXPECT_EQ(*(nums.crend() - 1), 1);
}

TEST(WrapperTest, BasicOperations) {
  using UserId = typed_alias::Wrapper<int, struct UserIdTag>;
  UserId id(42);
  EXPECT_EQ(static_cast<int>(id), 42);
  
  auto& ref = static_cast<int&>(id);
  ref = 43;
  EXPECT_EQ(static_cast<int>(id), 43);
}

} // namespace
