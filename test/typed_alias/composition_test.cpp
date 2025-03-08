#include <gtest/gtest.h>
#include <typed_alias/type.h>
#include <typed_alias/vector.h>
#include <typed_alias/list.h>
#include <typed_alias/set.h>
#include <typed_alias/map.h>
#include <typed_alias/string.h>
#include <string>

namespace {

// 基本类型别名
using UserId = typed_alias::Type<int, struct UserIdTag>;
using Score = typed_alias::Type<double, struct ScoreTag>;
using Name = typed_alias::String<struct NameTag>;

TEST(CompositionTest, BasicTypes) {
  UserId id{42};
  Score score{98.5};
  Name name{"Alice"};

  EXPECT_EQ(id.get(), 42);
  EXPECT_DOUBLE_EQ(score.get(), 98.5);
  EXPECT_EQ(name, "Alice");
}

TEST(CompositionTest, VectorOfTypedAlias) {
  using UserIds = typed_alias::Vector<UserId, struct UserIdsTag>;
  using Scores = typed_alias::Vector<Score, struct ScoresTag>;
  
  UserIds ids{UserId{1}, UserId{2}, UserId{3}};
  EXPECT_EQ(ids.size(), 3);
  EXPECT_EQ(ids[0].get(), 1);
  
  Scores scores;
  scores.push_back(Score{95.5});
  scores.push_back(Score{87.0});
  EXPECT_EQ(scores.size(), 2);
  EXPECT_DOUBLE_EQ(scores[0].get(), 95.5);
}

TEST(CompositionTest, SetOfTypedAlias) {
  using NameSet = typed_alias::Set<Name, struct NameSetTag>;
  
  NameSet names;
  names.insert(Name{"Bob"});
  names.insert(Name{"Alice"});
  names.insert(Name{"Bob"});  // 重复，不会插入
  
  EXPECT_EQ(names.size(), 2);
  auto it = names.begin();
  EXPECT_EQ(*it++, "Alice");  // 有序集合，Alice 在前
  EXPECT_EQ(*it++, "Bob");
}

TEST(CompositionTest, MapWithTypedAlias) {
  // Map with typed key and value
  using ScoreMap = typed_alias::Map<UserId, Score, struct ScoreMapTag>;
  
  ScoreMap scores;
  scores[UserId{1}] = Score{95.5};
  scores[UserId{2}] = Score{87.0};
  
  EXPECT_EQ(scores.size(), 2);
  EXPECT_DOUBLE_EQ(scores[UserId{1}].get(), 95.5);
  EXPECT_DOUBLE_EQ(scores[UserId{2}].get(), 87.0);
}

TEST(CompositionTest, ListOfVectors) {
  // List of vectors
  using ScoreList = typed_alias::Vector<Score, struct ScoreListTag>;
  using StudentScores = typed_alias::List<ScoreList, struct StudentScoresTag>;
  
  StudentScores allScores;
  
  // First student's scores
  ScoreList student1{Score{95.0}, Score{87.5}, Score{92.0}};
  allScores.push_back(student1);
  
  // Second student's scores
  ScoreList student2{Score{88.0}, Score{91.5}, Score{89.0}};
  allScores.push_back(student2);
  
  EXPECT_EQ(allScores.size(), 2);
  auto it = allScores.begin();
  EXPECT_EQ(it->size(), 3);
  EXPECT_DOUBLE_EQ((*it)[0].get(), 95.0);
  ++it;
  EXPECT_EQ(it->size(), 3);
  EXPECT_DOUBLE_EQ((*it)[1].get(), 91.5);
}

TEST(CompositionTest, ComplexDataStructure) {
  // 创建一个复杂的数据结构：每个用户ID对应一个有序的成绩集合
  using ScoreSet = typed_alias::Set<Score, struct ScoreSetTag>;
  using UserScores = typed_alias::Map<UserId, ScoreSet, struct UserScoresTag>;
  
  UserScores userScores;
  
  // 添加用户1的成绩
  ScoreSet user1Scores;
  user1Scores.insert(Score{95.0});
  user1Scores.insert(Score{87.5});
  user1Scores.insert(Score{95.0});  // 重复，不会插入
  userScores[UserId{1}] = std::move(user1Scores);
  
  // 添加用户2的成绩
  ScoreSet user2Scores;
  user2Scores.insert(Score{88.0});
  user2Scores.insert(Score{91.5});
  userScores[UserId{2}] = std::move(user2Scores);
  
  // 验证数据结构
  EXPECT_EQ(userScores.size(), 2);
  EXPECT_EQ(userScores[UserId{1}].size(), 2);  // 95.0 只插入一次
  EXPECT_EQ(userScores[UserId{2}].size(), 2);
  
  // 验证成绩有序性
  auto& scores1 = userScores[UserId{1}];
  auto it = scores1.begin();
  EXPECT_DOUBLE_EQ(it->get(), 87.5);  // Set 中较小的值在前
  ++it;
  EXPECT_DOUBLE_EQ(it->get(), 95.0);
}

} // namespace
