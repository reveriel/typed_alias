#include <gtest/gtest.h>
#include <typed_alias/set.h>

namespace {

TEST(SetTest, BasicOperations) {
  using UniqueIds = typed_alias::Set<int, struct UniqueIdsTag>;

  // 测试插入
  UniqueIds ids{1, 2, 3, 3};  // 重复的 3 会被忽略
  EXPECT_EQ(ids.size(), 3);

  // 测试查找
  EXPECT_NE(ids.find(1), ids.end());  // 使用 find 代替 contains
  EXPECT_EQ(ids.find(4), ids.end());

  // 测试插入重复元素
  auto [it, inserted] = ids.insert(3);
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, 3);

  // 测试删除
  EXPECT_EQ(ids.erase(2), 1);
  EXPECT_EQ(ids.size(), 2);
}

TEST(SetTest, Iterators) {
  using UniqueIds = typed_alias::Set<int, struct UniqueIdsTag>;
  UniqueIds ids{3, 1, 4, 2, 5};  // 会自动排序

  // begin/end
  auto it = ids.begin();
  EXPECT_EQ(*it, 1);             // 最小值
  EXPECT_EQ(*(--ids.end()), 5);  // 最大值

  // const begin/end
  const UniqueIds& const_ids = ids;
  auto const_it = const_ids.begin();
  EXPECT_EQ(*const_it, 1);
  EXPECT_EQ(*(--const_ids.end()), 5);

  // rbegin/rend
  auto rit = ids.rbegin();
  EXPECT_EQ(*rit, 5);             // 最大值
  EXPECT_EQ(*(--ids.rend()), 1);  // 最小值

  // cbegin/cend
  auto cit = ids.cbegin();
  EXPECT_EQ(*cit, 1);
  EXPECT_EQ(*(--ids.cend()), 5);

  // crbegin/crend
  auto crit = ids.crbegin();
  EXPECT_EQ(*crit, 5);
  EXPECT_EQ(*(--ids.crend()), 1);

  // 迭代器遍历
  std::vector<int> values;
  for (auto it = ids.begin(); it != ids.end(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3, 4, 5}));  // 有序遍历

  // 测试迭代器查找
  it = std::find(ids.begin(), ids.end(), 3);
  EXPECT_NE(it, ids.end());
  EXPECT_EQ(*it, 3);

  it = std::find(ids.begin(), ids.end(), 6);
  EXPECT_EQ(it, ids.end());
}

TEST(MultiSetTest, BasicOperations) {
  using Scores = typed_alias::MultiSet<int, struct ScoresTag>;

  // 测试多值插入
  Scores scores{95, 98, 95, 92};
  EXPECT_EQ(scores.size(), 4);

  // 测试计数
  EXPECT_EQ(scores.count(95), 2);

  // 测试范围
  auto [begin, end] = scores.equal_range(95);
  int count = 0;
  for (auto it = begin; it != end; ++it) {
    ++count;
  }
  EXPECT_EQ(count, 2);
}

}  // namespace
