#include <gtest/gtest.h>
#include <typed_alias/map.h>
#include <string>

namespace {

TEST(MapTest, BasicOperations) {
  using UserScores = typed_alias::Map<std::string, int, struct UserScoresTag>;
  
  // 测试构造和插入
  UserScores scores{{{"Alice", 100}, {"Bob", 95}}};
  scores["Charlie"] = 98;
  
  // 测试访问
  EXPECT_EQ(scores["Alice"], 100);
  EXPECT_EQ(scores.at("Bob"), 95);
  EXPECT_EQ(scores.size(), 3);

  // 测试查找
  auto it = scores.find("Alice");
  EXPECT_NE(it, scores.end());
  EXPECT_EQ(it->second, 100);

  // 测试删除
  scores.erase("Bob");
  EXPECT_EQ(scores.size(), 2);
  EXPECT_EQ(scores.count("Bob"), 0);
}

TEST(MultiMapTest, BasicOperations) {
  using Grades = typed_alias::MultiMap<std::string, int, struct GradesTag>;
  
  // 测试多值插入
  Grades grades;
  grades.insert({"Alice", 95});
  grades.insert({"Alice", 98});
  grades.insert({"Bob", 92});

  // 测试范围
  auto [begin, end] = grades.equal_range("Alice");
  int count = 0;
  int sum = 0;
  for (auto it = begin; it != end; ++it) {
    ++count;
    sum += it->second;
  }
  EXPECT_EQ(count, 2);
  EXPECT_EQ(sum, 193);
}

} // namespace
