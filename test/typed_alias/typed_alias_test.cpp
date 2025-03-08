#include <gtest/gtest.h>
#include <typed_alias/typed_alias.h>

#include <cassert>
#include <iostream>
#include <type_traits>
#include <utility>

// 测试继承方式
TEST(TypeTest, InheritanceApproach) {
  using Email = typed_alias::String<struct EmailTag>;
  Email email{"user@domain.com"};

  // 测试成员函数
  EXPECT_EQ(email.size(), std::string("user@domain.com").size());
  EXPECT_FALSE(email.empty());

  // 测试类型安全
  static_assert(!std::is_same_v<Email, std::string>, "Types should differ");

  // 测试比较
  Email email2{"user@domain.com"};
  EXPECT_EQ(email, email2);

  // 测试与底层类型的转换
  std::string str = "user@domain.com";
  Email email3(std::move(str));  // 从右值构造
  EXPECT_EQ(email3, email);

  // 测试转换回底层类型
  std::string str2 = static_cast<std::string>(email3);  // 显式转换
  EXPECT_EQ(str2, "user@domain.com");

  // 测试工厂方法
  Email email4 = Email::from("test@example.com");
  EXPECT_EQ(email4.get(), "test@example.com");

  // 测试移动语义
  std::string moved_str = std::move(email4).into();
  EXPECT_EQ(moved_str, "test@example.com");
}

// 测试 STL 容器使用
TEST(TypeTest, StlVector) {
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

  // 测试插入
  ns.insert(ns.begin() + 1, "inserted");
  EXPECT_EQ(ns[1], "inserted");
  EXPECT_EQ(ns.size(), 6);

  // 测试删除
  ns.pop_back();
  EXPECT_EQ(ns.size(), 5);
  EXPECT_EQ(ns.back(), "item4");

  auto it = ns.erase(ns.begin());
  EXPECT_EQ(*it, "inserted");
  EXPECT_EQ(ns.size(), 4);

  // 测试清空
  ns.clear();
  EXPECT_TRUE(ns.empty());
  EXPECT_EQ(ns.size(), 0);

  // 测试容量操作
  ns.reserve(10);
  EXPECT_GE(ns.capacity(), 10);

  ns.shrink_to_fit();
  EXPECT_LE(ns.capacity(), 10);

  // 测试赋值
  Namespace ns2;
  ns2 = {"new1", "new2"};
  EXPECT_EQ(ns2.size(), 2);
  EXPECT_EQ(ns2[0], "new1");

  // 测试比较
  Namespace ns3 = ns2;
  EXPECT_EQ(ns2, ns3);
  ns3.push_back("new3");
  EXPECT_NE(ns2, ns3);
  EXPECT_LT(ns2, ns3);

  // 测试迭代器
  std::vector<std::string> vec;
  for (const auto& item : ns2) {
    vec.push_back(item);
  }
  EXPECT_EQ(vec.size(), ns2.size());
  EXPECT_EQ(vec[0], ns2[0]);

  // 测试与底层类型的转换
  std::vector<std::string> underlying = {"test1", "test2"};
  Namespace from_vec(underlying.begin(), underlying.end());
  EXPECT_EQ(from_vec.size(), underlying.size());
  EXPECT_EQ(from_vec[0], underlying[0]);

  // 测试移动语义
  Namespace moved = std::move(from_vec);
  EXPECT_EQ(moved.size(), 2);
  EXPECT_EQ(moved[0], "test1");
  EXPECT_TRUE(from_vec.empty());  // NOLINT: 访问移动后的对象是合法的，但可能导致 lint 警告
}

// 测试大小和性能
TEST(TypeTest, SizeAndPerformance) {
  using Email = typed_alias::String<struct EmailTag>;
  
  // 测试大小相等
  EXPECT_EQ(sizeof(Email), sizeof(std::string));

  // 测试内存对齐
  EXPECT_EQ(alignof(Email), alignof(std::string));

  // 验证是否是标准布局类型
  EXPECT_EQ(std::is_standard_layout_v<Email>, std::is_standard_layout_v<std::string>);

  // 验证是否可平凡复制
  EXPECT_EQ(std::is_trivially_copyable_v<Email>, std::is_trivially_copyable_v<std::string>);

  // 验证构造函数是否被正确转发
  const char* str = "test@example.com";
  Email email(str);
  std::string std_str(str);
  EXPECT_EQ(email.size(), std_str.size());
  EXPECT_EQ(email.capacity(), std_str.capacity());
}
