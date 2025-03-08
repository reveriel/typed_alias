#include <gtest/gtest.h>
#include <typed_alias/deque.h>
#include <string>

namespace {

TEST(DequeTest, BasicOperations) {
  using TaskQueue = typed_alias::Deque<std::string, struct TaskQueueTag>;
  
  // 测试构造
  TaskQueue empty;
  EXPECT_TRUE(empty.empty());

  TaskQueue tasks{"task1", "task2"};
  EXPECT_EQ(tasks.size(), 2);

  // 测试两端操作
  tasks.push_front("task0");
  tasks.push_back("task3");
  EXPECT_EQ(tasks.size(), 4);
  EXPECT_EQ(tasks.front(), "task0");
  EXPECT_EQ(tasks.back(), "task3");

  // 测试删除
  tasks.pop_front();
  tasks.pop_back();
  EXPECT_EQ(tasks.size(), 2);
  EXPECT_EQ(tasks.front(), "task1");
  EXPECT_EQ(tasks.back(), "task2");
}

TEST(DequeTest, RandomAccess) {
  using TaskQueue = typed_alias::Deque<std::string, struct TaskQueueTag>;
  TaskQueue tasks{"task1", "task2", "task3", "task4"};

  // 测试随机访问
  EXPECT_EQ(tasks[1], "task2");
  EXPECT_EQ(tasks.at(2), "task3");

  // 测试修改
  tasks[1] = "modified";
  EXPECT_EQ(tasks[1], "modified");

  // 测试插入
  tasks.insert(tasks.begin() + 1, "inserted");
  EXPECT_EQ(tasks[1], "inserted");
  EXPECT_EQ(tasks.size(), 5);

  // 测试删除
  tasks.erase(tasks.begin() + 1);
  EXPECT_EQ(tasks[1], "modified");
  EXPECT_EQ(tasks.size(), 4);
}

} // namespace
