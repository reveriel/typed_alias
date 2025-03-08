#include <gtest/gtest.h>
#include <typed_alias/unordered_map.h>
#include <string>

namespace {

TEST(UnorderedMapTest, BasicOperations) {
  using Cache = typed_alias::UnorderedMap<std::string, int, struct CacheTag>;
  
  // 测试构造和插入
  Cache cache{{"key1", 1}, {"key2", 2}};
  cache["key3"] = 3;
  
  // 测试访问
  EXPECT_EQ(cache["key1"], 1);
  EXPECT_EQ(cache.at("key2"), 2);
  EXPECT_EQ(cache.size(), 3);

  // 测试查找
  auto it = cache.find("key1");
  EXPECT_NE(it, cache.end());
  EXPECT_EQ(it->second, 1);

  // 测试删除
  cache.erase("key2");
  EXPECT_EQ(cache.size(), 2);
  EXPECT_EQ(cache.count("key2"), 0);
}

TEST(UnorderedMapTest, Buckets) {
  using Cache = typed_alias::UnorderedMap<std::string, int, struct CacheTag>;
  Cache cache;
  
  // 测试桶接口
  cache.reserve(10);
  EXPECT_GE(cache.bucket_count(), 10);

  cache.insert({{"a", 1}, {"b", 2}, {"c", 3}});
  for (size_t i = 0; i < cache.bucket_count(); ++i) {
    EXPECT_GE(cache.bucket_size(i), 0);
  }

  // 测试负载因子
  EXPECT_GT(cache.load_factor(), 0.0f);
  float max_load = cache.max_load_factor();
  cache.max_load_factor(max_load * 2);
  EXPECT_EQ(cache.max_load_factor(), max_load * 2);
}

TEST(UnorderedMultiMapTest, BasicOperations) {
  using MultiCache = typed_alias::UnorderedMultiMap<std::string, int, struct MultiCacheTag>;
  
  // 测试多值插入
  MultiCache cache;
  cache.insert({"key1", 1});
  cache.insert({"key1", 11});
  cache.insert({"key2", 2});
  
  // 测试计数和范围
  EXPECT_EQ(cache.count("key1"), 2);
  EXPECT_EQ(cache.count("key2"), 1);

  // 测试范围
  auto [begin, end] = cache.equal_range("key1");
  std::vector<int> values;
  for (auto it = begin; it != end; ++it) {
    values.push_back(it->second);
  }
  EXPECT_EQ(values.size(), 2);
  EXPECT_TRUE(std::find(values.begin(), values.end(), 1) != values.end());
  EXPECT_TRUE(std::find(values.begin(), values.end(), 11) != values.end());
}

} // namespace
