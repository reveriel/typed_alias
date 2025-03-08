# Typed Alias

一个现代 C++ 类型别名库，提供类型安全的别名和容器包装。

## 特性

- 🛡️ **类型安全**：通过标签区分相同底层类型的不同用途
- 🔄 **完全兼容**：保持与 STL 容器完全相同的接口和行为
- 🎯 **零开销**：编译期类型检查，运行时零开销
- 🧩 **组合友好**：支持任意嵌套和组合使用
- 📦 **容器支持**：支持所有标准 STL 容器

## 快速开始

### 基本类型别名

```cpp
#include <typed_alias/type.h>

// 为不同用途的整数创建类型安全的别名
using UserId = typed_alias::Type<int, struct UserIdTag>;
using GroupId = typed_alias::Type<int, struct GroupIdTag>;

void process_user(UserId id) {
    // ...
}

int main() {
    UserId user_id{42};
    GroupId group_id{42};
    
    process_user(user_id);   // ✅ 正确：类型匹配
    process_user(group_id);  // ❌ 错误：类型不匹配
    process_user(42);        // ❌ 错误：需要显式构造
}
```

### 字符串别名

```cpp
#include <typed_alias/string.h>

using Email = typed_alias::String<struct EmailTag>;
using PhoneNumber = typed_alias::String<struct PhoneNumberTag>;

void send_email(Email to) {
    // ...
}

int main() {
    Email email{"user@example.com"};
    PhoneNumber phone{"+1234567890"};
    
    send_email(email);        // ✅ 正确：类型匹配
    send_email(phone);        // ❌ 错误：类型不匹配
    send_email("bad_email");  // ❌ 错误：需要显式构造
}
```

### 容器别名

```cpp
#include <typed_alias/vector.h>
#include <typed_alias/set.h>
#include <typed_alias/map.h>

// 基本类型别名
using UserId = typed_alias::Type<int, struct UserIdTag>;
using Score = typed_alias::Type<double, struct ScoreTag>;
using Name = typed_alias::String<struct NameTag>;

// 容器别名
using UserIds = typed_alias::Vector<UserId, struct UserIdsTag>;
using Names = typed_alias::Set<Name, struct NamesTag>;
using Scores = typed_alias::Map<UserId, Score, struct ScoresTag>;

int main() {
    UserIds ids{UserId{1}, UserId{2}, UserId{3}};
    
    Names names;
    names.insert(Name{"Alice"});
    names.insert(Name{"Bob"});
    
    Scores scores;
    scores[UserId{1}] = Score{95.5};
    scores[UserId{2}] = Score{87.0};
}
```

### 复杂数据结构

```cpp
#include <typed_alias/vector.h>
#include <typed_alias/set.h>
#include <typed_alias/map.h>

// 创建复杂的数据结构
using ScoreSet = typed_alias::Set<Score, struct ScoreSetTag>;
using UserScores = typed_alias::Map<UserId, ScoreSet, struct UserScoresTag>;

int main() {
    UserScores user_scores;
    
    // 添加用户1的成绩
    ScoreSet user1_scores;
    user1_scores.insert(Score{95.0});
    user1_scores.insert(Score{87.5});
    user_scores[UserId{1}] = std::move(user1_scores);
    
    // 使用自动排序和去重特性
    auto& scores = user_scores[UserId{1}];
    scores.insert(Score{95.0});  // 重复分数会被忽略
    for (const auto& score : scores) {
        // 分数会自动按升序排列
    }
}
```

## 支持的容器

- `Vector<T, Tag>`：动态数组
- `Array<T, N, Tag>`：固定大小数组
- `List<T, Tag>`：双向链表
- `ForwardList<T, Tag>`：单向链表
- `Deque<T, Tag>`：双端队列
- `Set<T, Tag>`：有序集合
- `MultiSet<T, Tag>`：有序多重集合
- `Map<K, V, Tag>`：有序映射
- `MultiMap<K, V, Tag>`：有序多重映射
- `UnorderedSet<T, Tag>`：无序集合
- `UnorderedMultiSet<T, Tag>`：无序多重集合
- `UnorderedMap<K, V, Tag>`：无序映射
- `UnorderedMultiMap<K, V, Tag>`：无序多重映射

## 特性说明

### 迭代器支持

- 所有容器都支持基本的迭代器操作（`begin()`/`end()`）
- 支持反向迭代器的容器（如 `Vector`、`List`、`Set` 等）额外提供 `rbegin()`/`rend()` 操作
- 提供 `const` 迭代器支持（`cbegin()`/`cend()`，`crbegin()`/`crend()`）

### 构造和赋值

- 支持从底层类型构造和赋值
- 支持移动语义
- 支持初始化列表构造

### 类型安全

- 不同标签的相同底层类型不能隐式转换
- 需要显式构造，防止意外赋值
- 编译期类型检查，运行时零开销

## 构建和测试

使用 Bazel 构建系统：

```bash
# 构建所有目标
bazel build //...

# 运行所有测试
bazel test //...

# build compile_commands.json
bazel build :refresh_compile_commands
```


## 许可证

MIT License