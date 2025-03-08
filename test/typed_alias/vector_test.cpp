#include <gtest/gtest.h>
#include <typed_alias/vector.h>
#include <string>

namespace {

TEST(VectorTest, BasicOperations) {
  using Namespace = typed_alias::Vector<std::string, struct NamespaceTag>;
  
  // 测试构造函数
  Namespace empty;
  EXPECT_TRUE(empty.empty());
  EXPECT_EQ(empty.size(), 0);

  // 测试初始化列表构造
  Namespace ns{"item1", "item2", "item3"};
  EXPECT_EQ(ns.size(), 3);
  
  // 测试基本访问
  EXPECT_EQ(ns[0], "item1");
  EXPECT_EQ(ns.at(1), "item2");
  EXPECT_EQ(ns.front(), "item1");
  EXPECT_EQ(ns.back(), "item3");

  // 测试修改
  ns[0] = "modified";
  EXPECT_EQ(ns.front(), "modified");

  // 测试添加元素
  ns.push_back("item4");
  EXPECT_EQ(ns.size(), 4);
  EXPECT_EQ(ns.back(), "item4");

  ns.emplace_back("item5");
  EXPECT_EQ(ns.size(), 5);
  EXPECT_EQ(ns.back(), "item5");
}

TEST(VectorTest, AdvancedOperations) {
  using Namespace = typed_alias::Vector<std::string, struct NamespaceTag>;
  Namespace ns{"item1", "item2", "item3"};

  // 测试插入
  ns.insert(ns.begin() + 1, "inserted");
  EXPECT_EQ(ns[1], "inserted");
  EXPECT_EQ(ns.size(), 4);

  // 测试删除
  ns.pop_back();
  EXPECT_EQ(ns.size(), 3);
  EXPECT_EQ(ns.back(), "item2");

  auto it = ns.erase(ns.begin());
  EXPECT_EQ(*it, "inserted");
  EXPECT_EQ(ns.size(), 2);

  // 测试清空
  ns.clear();
  EXPECT_TRUE(ns.empty());
  EXPECT_EQ(ns.size(), 0);

  // 测试容量操作
  ns.reserve(10);
  EXPECT_GE(ns.capacity(), 10);

  ns.shrink_to_fit();
  EXPECT_LE(ns.capacity(), 10);
}

TEST(VectorTest, Iterators) {
  using Namespace = typed_alias::Vector<std::string, struct NamespaceTag>;
  Namespace ns{"item1", "item2", "item3"};

  // begin/end
  auto it = ns.begin();
  EXPECT_EQ(*it, "item1");
  ++it;
  EXPECT_EQ(*it, "item2");
  EXPECT_EQ(*(--ns.end()), "item3");

  // const begin/end
  const Namespace& const_ns = ns;
  auto const_it = const_ns.begin();
  EXPECT_EQ(*const_it, "item1");
  EXPECT_EQ(*(--const_ns.end()), "item3");

  // rbegin/rend
  auto rit = ns.rbegin();
  EXPECT_EQ(*rit, "item3");
  ++rit;
  EXPECT_EQ(*rit, "item2");
  EXPECT_EQ(*(--ns.rend()), "item1");

  // cbegin/cend
  auto cit = ns.cbegin();
  EXPECT_EQ(*cit, "item1");
  EXPECT_EQ(*(--ns.cend()), "item3");

  // crbegin/crend
  auto crit = ns.crbegin();
  EXPECT_EQ(*crit, "item3");
  EXPECT_EQ(*(--ns.crend()), "item1");

  // 迭代器运算
  EXPECT_EQ(ns.end() - ns.begin(), 3);
  EXPECT_EQ(ns.begin() + 1, ++ns.begin());
  EXPECT_TRUE(ns.begin() < ns.end());
  EXPECT_FALSE(ns.begin() < ns.begin());
}

TEST(VectorTest, Comparison) {
  using Namespace = typed_alias::Vector<std::string, struct NamespaceTag>;
  
  Namespace ns1{"a", "b"};
  Namespace ns2 = ns1;  // 应该可以拷贝
  EXPECT_EQ(ns1, ns2);
  
  ns2.push_back("c");
  EXPECT_NE(ns1, ns2);
  EXPECT_LT(ns1, ns2);
}

} // namespace
