#include <gtest/gtest.h>
#include <typed_alias/array.h>

#include <algorithm>

namespace {

TEST(ArrayTest, BasicOperations) {
  using IntArray = typed_alias::Array<int, 3, struct IntArrayTag>;

  // 测试构造
  IntArray arr{1, 2, 3};  // 使用列表初始化
  EXPECT_EQ(arr.size(), 3);

  // 测试访问
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.front(), 1);
  EXPECT_EQ(arr.back(), 3);

  // 测试修改
  arr[0] = 10;
  EXPECT_EQ(arr[0], 10);

  // 测试数据访问
  const int* data = arr.data();
  EXPECT_EQ(data[0], 10);
  EXPECT_EQ(data[1], 2);

  // 测试不同类型的构造
  typed_alias::Array<double, 2, struct DoubleArrayTag> darr{1, 2.5};  // int 到 double 的转换
  EXPECT_EQ(darr[0], 1.0);
  EXPECT_EQ(darr[1], 2.5);
}

TEST(ArrayTest, Algorithms) {
  using IntArray = typed_alias::Array<int, 3, struct IntArrayTag>;
  IntArray arr{3, 1, 2};  // 使用列表初始化

  // 测试排序
  std::sort(arr.begin(), arr.end());
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);

  // 测试查找
  auto it = std::find(arr.begin(), arr.end(), 2);
  EXPECT_NE(it, arr.end());
  EXPECT_EQ(*it, 2);
}

TEST(ArrayTest, Iterators) {
  using IntArray = typed_alias::Array<int, 3, struct IntArrayTag>;
  IntArray arr{1, 2, 3};  // 使用列表初始化

  // begin/end
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  auto last = arr.end();
  --last;
  EXPECT_EQ(*last, 3);

  // const begin/end
  const IntArray& const_arr = arr;
  auto const_it = const_arr.begin();
  EXPECT_EQ(*const_it, 1);
  auto const_last = const_arr.end();
  --const_last;
  EXPECT_EQ(*const_last, 3);

  // rbegin/rend
  auto rit = arr.rbegin();
  EXPECT_EQ(*rit, 3);
  ++rit;
  EXPECT_EQ(*rit, 2);
  auto rlast = arr.rend();
  --rlast;
  EXPECT_EQ(*rlast, 1);

  // cbegin/cend
  auto cit = arr.cbegin();
  EXPECT_EQ(*cit, 1);
  auto clast = arr.cend();
  --clast;
  EXPECT_EQ(*clast, 3);

  // crbegin/crend
  auto crit = arr.crbegin();
  EXPECT_EQ(*crit, 3);
  auto crlast = arr.crend();
  --crlast;
  EXPECT_EQ(*crlast, 1);

  // 迭代器运算
  EXPECT_EQ(arr.end() - arr.begin(), 3);
  auto bit = arr.begin();
  auto next_bit = bit;
  ++next_bit;
  EXPECT_EQ(bit + 1, next_bit);
  EXPECT_TRUE(arr.begin() < arr.end());
  EXPECT_FALSE(arr.begin() < arr.begin());
}

}  // namespace
