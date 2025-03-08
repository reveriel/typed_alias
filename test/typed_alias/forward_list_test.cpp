#include <gtest/gtest.h>
#include <typed_alias/forward_list.h>
#include <string>

namespace {

TEST(ForwardListTest, BasicOperations) {
  using Queue = typed_alias::ForwardList<std::string, struct QueueTag>;
  
  // 测试构造
  Queue empty;
  EXPECT_TRUE(empty.empty());

  Queue queue{"item1", "item2", "item3"};
  EXPECT_EQ(queue.front(), "item1");

  // 测试前端操作
  queue.push_front("item0");
  EXPECT_EQ(queue.front(), "item0");

  queue.pop_front();
  EXPECT_EQ(queue.front(), "item1");
}

TEST(ForwardListTest, Insert) {
  using Queue = typed_alias::ForwardList<std::string, struct QueueTag>;
  Queue queue{"item1", "item2", "item3"};

  // 测试插入
  auto pos = queue.begin();
  ++pos;  // 指向 "item2"
  queue.insert_after(pos, "inserted");

  // 验证插入结果
  pos = queue.begin();
  EXPECT_EQ(*pos++, "item1");
  EXPECT_EQ(*pos++, "item2");
  EXPECT_EQ(*pos++, "inserted");
  EXPECT_EQ(*pos++, "item3");

  // 测试删除
  pos = queue.begin();
  queue.erase_after(pos);  // 删除 "item2"
  
  pos = queue.begin();
  EXPECT_EQ(*pos++, "item1");
  EXPECT_EQ(*pos++, "inserted");
  EXPECT_EQ(*pos++, "item3");
}

TEST(ForwardListTest, Operations) {
  using Queue = typed_alias::ForwardList<std::string, struct QueueTag>;
  Queue queue{"item3", "item1", "item2", "item2"};

  // 测试排序
  queue.sort();
  auto it = queue.begin();
  EXPECT_EQ(*it++, "item1");
  EXPECT_EQ(*it++, "item2");
  EXPECT_EQ(*it++, "item2");
  EXPECT_EQ(*it++, "item3");

  // 测试去重
  queue.unique();
  it = queue.begin();
  EXPECT_EQ(*it++, "item1");
  EXPECT_EQ(*it++, "item2");
  EXPECT_EQ(*it++, "item3");

  // 测试反转
  queue.reverse();
  it = queue.begin();
  EXPECT_EQ(*it++, "item3");
  EXPECT_EQ(*it++, "item2");
  EXPECT_EQ(*it++, "item1");
}

} // namespace
