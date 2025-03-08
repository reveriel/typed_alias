#include <gtest/gtest.h>
#include <typed_alias/unordered_set.h>

#include <algorithm>
#include <string>
#include <vector>

namespace {

TEST(UnorderedSetTest, BasicOperations) {
  using HashSet = typed_alias::UnorderedSet<int, struct HashSetTag>;

  // 测试构造和插入
  HashSet set{1, 2, 3, 3};  // 重复的 3 会被忽略
  EXPECT_EQ(set.size(), 3);
  EXPECT_NE(set.find(1), set.end());  // 使用 find 代替 contains
  EXPECT_EQ(set.find(4), set.end());

  // 测试插入
  auto [it, inserted] = set.insert(4);
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, 4);

  // 测试删除
  EXPECT_EQ(set.erase(2), 1);
  EXPECT_EQ(set.size(), 3);
}

TEST(UnorderedSetTest, Buckets) {
  using HashSet = typed_alias::UnorderedSet<int, struct HashSetTag>;
  HashSet set;

  // 测试桶接口
  set.reserve(10);
  EXPECT_GE(set.bucket_count(), 10);

  set.insert({1, 2, 3, 4, 5});
  for (size_t i = 0; i < set.bucket_count(); ++i) {
    EXPECT_GE(set.bucket_size(i), 0);
  }

  // 测试负载因子
  EXPECT_GT(set.load_factor(), 0.0f);
  float max_load = set.max_load_factor();
  set.max_load_factor(max_load * 2);
  EXPECT_EQ(set.max_load_factor(), max_load * 2);
}

TEST(UnorderedSetTest, Iterators) {
  using HashSet = typed_alias::UnorderedSet<int, struct HashSetTag>;
  HashSet set{1, 2, 3, 4, 5};

  // begin/end
  EXPECT_EQ(std::distance(set.begin(), set.end()), 5);

  // 测试迭代器遍历
  std::vector<int> values;
  for (auto it = set.begin(); it != set.end(); ++it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values.size(), 5);
  std::sort(values.begin(), values.end());
  EXPECT_EQ(values, std::vector<int>({1, 2, 3, 4, 5}));

  // const begin/end
  const HashSet& const_set = set;
  std::vector<int> const_values;
  for (auto it = const_set.begin(); it != const_set.end(); ++it) {
    const_values.push_back(*it);
  }
  EXPECT_EQ(const_values.size(), 5);
  std::sort(const_values.begin(), const_values.end());
  EXPECT_EQ(const_values, std::vector<int>({1, 2, 3, 4, 5}));

  // cbegin/cend
  std::vector<int> cvalues;
  for (auto it = set.cbegin(); it != set.cend(); ++it) {
    cvalues.push_back(*it);
  }
  EXPECT_EQ(cvalues.size(), 5);
  std::sort(cvalues.begin(), cvalues.end());
  EXPECT_EQ(cvalues, std::vector<int>({1, 2, 3, 4, 5}));

  // 测试迭代器查找
  auto it = std::find(set.begin(), set.end(), 3);
  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 3);

  it = std::find(set.begin(), set.end(), 6);
  EXPECT_EQ(it, set.end());
}

TEST(UnorderedMultiSetTest, BasicOperations) {
  using MultiSet = typed_alias::UnorderedMultiSet<int, struct MultiSetTag>;

  // 测试多值插入
  MultiSet set{1, 2, 2, 3, 3, 3};
  EXPECT_EQ(set.size(), 6);

  // 测试计数
  EXPECT_EQ(set.count(1), 1);
  EXPECT_EQ(set.count(2), 2);
  EXPECT_EQ(set.count(3), 3);

  // 测试范围
  auto [begin, end] = set.equal_range(3);
  int count = 0;
  for (auto it = begin; it != end; ++it) {
    ++count;
  }
  EXPECT_EQ(count, 3);
}

}  // namespace
