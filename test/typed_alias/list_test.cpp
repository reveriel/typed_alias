#include <gtest/gtest.h>
#include <typed_alias/list.h>
#include <string>

namespace {

TEST(ListTest, BasicOperations) {
  using UserList = typed_alias::List<std::string, struct UserListTag>;
  
  // 测试构造
  UserList empty;
  EXPECT_TRUE(empty.empty());

  UserList users{"user1", "user2", "user3"};
  EXPECT_EQ(users.size(), 3);

  // 测试两端操作
  users.push_front("user0");
  users.push_back("user4");
  EXPECT_EQ(users.size(), 5);
  EXPECT_EQ(users.front(), "user0");
  EXPECT_EQ(users.back(), "user4");

  users.pop_front();
  users.pop_back();
  EXPECT_EQ(users.front(), "user1");
  EXPECT_EQ(users.back(), "user3");
}

TEST(ListTest, Splice) {
  using UserList = typed_alias::List<std::string, struct UserListTag>;
  UserList list1{"user1", "user2"};
  UserList list2{"user3", "user4"};

  // 测试拼接整个列表
  list1.splice(list1.end(), list2);
  EXPECT_EQ(list1.size(), 4);
  EXPECT_TRUE(list2.empty());

  // 测试拼接单个元素
  list2.push_back("user5");
  list1.splice(list1.begin(), list2, list2.begin());
  EXPECT_EQ(list1.size(), 5);
  EXPECT_EQ(list1.front(), "user5");
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Sort) {
  using UserList = typed_alias::List<std::string, struct UserListTag>;
  UserList users{"user3", "user1", "user2"};

  // 测试排序
  users.sort();
  auto it = users.begin();
  EXPECT_EQ(*it++, "user1");
  EXPECT_EQ(*it++, "user2");
  EXPECT_EQ(*it++, "user3");

  // 测试反转
  users.reverse();
  it = users.begin();
  EXPECT_EQ(*it++, "user3");
  EXPECT_EQ(*it++, "user2");
  EXPECT_EQ(*it++, "user1");

  // 测试去重
  users.push_back("user2");
  users.push_back("user2");
  users.sort();  // 先排序，让重复元素相邻
  users.unique();  // 然后去重
  EXPECT_EQ(users.size(), 3);
}

} // namespace
