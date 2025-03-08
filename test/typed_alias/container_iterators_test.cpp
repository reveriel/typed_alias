#include <gtest/gtest.h>
#include <typed_alias/array.h>
#include <typed_alias/vector.h>
#include <typed_alias/list.h>
#include <typed_alias/forward_list.h>
#include <typed_alias/deque.h>
#include <typed_alias/set.h>
#include <typed_alias/map.h>
#include <typed_alias/unordered_set.h>
#include <typed_alias/unordered_map.h>
#include <string>

namespace {

TEST(ContainerIteratorsTest, ReverseIterators) {
  // Array
  typed_alias::Array<int, 3, struct ArrayTag> arr{1, 2, 3};
  EXPECT_EQ(*arr.rbegin(), 3);
  EXPECT_EQ(*std::prev(arr.rend()), 1);
  EXPECT_EQ(*arr.crbegin(), 3);
  EXPECT_EQ(*std::prev(arr.crend()), 1);

  // Vector
  typed_alias::Vector<int, struct VectorTag> vec{1, 2, 3};
  EXPECT_EQ(*vec.rbegin(), 3);
  EXPECT_EQ(*std::prev(vec.rend()), 1);
  EXPECT_EQ(*vec.crbegin(), 3);
  EXPECT_EQ(*std::prev(vec.crend()), 1);

  // List
  typed_alias::List<int, struct ListTag> lst{1, 2, 3};
  EXPECT_EQ(*lst.rbegin(), 3);
  EXPECT_EQ(*std::prev(lst.rend()), 1);
  EXPECT_EQ(*lst.crbegin(), 3);
  EXPECT_EQ(*std::prev(lst.crend()), 1);

  // Deque
  typed_alias::Deque<int, struct DequeTag> deq{1, 2, 3};
  EXPECT_EQ(*deq.rbegin(), 3);
  EXPECT_EQ(*std::prev(deq.rend()), 1);
  EXPECT_EQ(*deq.crbegin(), 3);
  EXPECT_EQ(*std::prev(deq.crend()), 1);

  // Set
  typed_alias::Set<int, struct SetTag> set{1, 2, 3};
  EXPECT_EQ(*set.rbegin(), 3);
  EXPECT_EQ(*std::prev(set.rend()), 1);
  EXPECT_EQ(*set.crbegin(), 3);
  EXPECT_EQ(*std::prev(set.crend()), 1);

  // MultiSet
  typed_alias::MultiSet<int, struct MultiSetTag> mset{1, 2, 2, 3};
  EXPECT_EQ(*mset.rbegin(), 3);
  EXPECT_EQ(*std::prev(mset.rend()), 1);
  EXPECT_EQ(*mset.crbegin(), 3);
  EXPECT_EQ(*std::prev(mset.crend()), 1);

  // Map
  typed_alias::Map<std::string, int, struct MapTag> map{{"a", 1}, {"b", 2}, {"c", 3}};
  EXPECT_EQ(map.rbegin()->second, 3);
  EXPECT_EQ(std::prev(map.rend())->second, 1);
  EXPECT_EQ(map.crbegin()->second, 3);
  EXPECT_EQ(std::prev(map.crend())->second, 1);

  // MultiMap
  typed_alias::MultiMap<std::string, int, struct MultiMapTag> mmap{{"a", 1}, {"b", 2}, {"b", 2}, {"c", 3}};
  EXPECT_EQ(mmap.rbegin()->second, 3);
  EXPECT_EQ(std::prev(mmap.rend())->second, 1);
  EXPECT_EQ(mmap.crbegin()->second, 3);
  EXPECT_EQ(std::prev(mmap.crend())->second, 1);
}

TEST(ContainerIteratorsTest, ForwardIterators) {
  // Forward list (只有前向迭代器)
  typed_alias::ForwardList<int, struct ForwardListTag> flst{1, 2, 3};
  EXPECT_EQ(*flst.begin(), 1);
  EXPECT_EQ(*std::next(flst.begin()), 2);
  EXPECT_EQ(*flst.cbegin(), 1);
  EXPECT_EQ(*std::next(flst.cbegin()), 2);

  // Unordered set (只有前向迭代器)
  typed_alias::UnorderedSet<int, struct UnorderedSetTag> uset{1, 2, 3};
  auto it = uset.begin();
  EXPECT_NE(it, uset.end());
  auto cit = uset.cbegin();
  EXPECT_NE(cit, uset.cend());

  // Unordered multiset (只有前向迭代器)
  typed_alias::UnorderedMultiSet<int, struct UnorderedMultiSetTag> umset{1, 2, 2, 3};
  auto umit = umset.begin();
  EXPECT_NE(umit, umset.end());
  auto umcit = umset.cbegin();
  EXPECT_NE(umcit, umset.cend());

  // Unordered map (只有前向迭代器)
  typed_alias::UnorderedMap<std::string, int, struct UnorderedMapTag> umap{{"a", 1}, {"b", 2}};
  auto umapit = umap.begin();
  EXPECT_NE(umapit, umap.end());
  auto umapcit = umap.cbegin();
  EXPECT_NE(umapcit, umap.cend());

  // Unordered multimap (只有前向迭代器)
  typed_alias::UnorderedMultiMap<std::string, int, struct UnorderedMultiMapTag> 
      ummap{{"a", 1}, {"b", 2}, {"b", 2}};
  auto ummapit = ummap.begin();
  EXPECT_NE(ummapit, ummap.end());
  auto ummapcit = ummap.cbegin();
  EXPECT_NE(ummapcit, ummap.cend());
}

} // namespace
