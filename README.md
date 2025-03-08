# Typed Alias

[![CI](https://github.com/reveriel/bazel_template/actions/workflows/ci.yml/badge.svg)](https://github.com/reveriel/bazel_template/actions)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)

`typed_alias` 是一个基于继承的强类型别名库，它提供了一种类型安全的方式来创建具有特定语义的类型。

## 特性

- 基于继承的实现，零运行时开销
- 完全类型安全，防止类型混淆
- 支持所有 STL 容器
- 支持完整的成员函数访问
- 支持移动语义
- 头文件实现，易于集成

## 性能特性

### 零开销抽象

基于继承的实现（`Type<T, Tag>`）保证了零运行时开销：

1. **大小优化**：
   - 利用空基类优化 (EBCO)
   - `sizeof(Type<T, Tag>) == sizeof(T)`
   - 内存对齐与底层类型完全相同

2. **构造函数优化**：
   - 直接继承底层类型的构造函数
   - 无额外的函数调用或数据拷贝
   ```cpp
   Email email{"abc"};  // 与 std::string{"abc"} 生成相同的机器码
   ```

3. **编译期开销**：
   - 仅在编译期进行类型检查
   - 模板实例化和类型元数据生成
   - 不影响运行时性能

### 继承 vs 组合

库提供了两种实现方式：

1. **基于继承** (`Type<T, Tag>`)：
   - 零运行时开销
   - 利用空基类优化
   - 直接继承成员函数
   - 推荐用于追求性能的场景

2. **基于组合** (`Wrapper<T, Tag>`)：
   - 更严格的封装
   - 显式的接口转发
   - 轻微的运行时开销
   - 适用于需要自定义行为的场景

## 使用示例

```cpp
// 创建一个 Email 类型
using Email = typed_alias::String<struct EmailTag>;

// 使用示例
Email email{"user@domain.com"};
EXPECT_FALSE(email.empty());

// 支持与底层类型的转换
std::string str = "user@domain.com";
Email email2(std::move(str));

// 支持 STL 容器
using Namespace = typed_alias::Vector<std::string, struct NamespaceTag>;
Namespace ns{"item1", "item2", "item3"};
ns.push_back("item4");
```

## 预定义类型

- `typed_alias::String<Tag>`: 基于 `std::string` 的强类型
- `typed_alias::Vector<T, Tag>`: 基于 `std::vector<T>` 的强类型

## 创建自定义类型

```cpp
// 为任意类型创建强类型别名
using UserId = typed_alias::Type<int, struct UserIdTag>;
using Score = typed_alias::Type<double, struct ScoreTag>;
```

## 构建和测试

### 构建

```bash
# 构建所有目标
bazel build //...

# Debug 构建
bazel build --config=debug //...

# Release 构建
bazel build --config=release //...
```

### 测试

```bash
# 运行所有测试
bazel test //...

# 运行特定测试
bazel test //test/typed_alias:typed_alias_test

# 使用 sanitizer 运行测试
bazel test --config=asan //...  # Address Sanitizer
bazel test --config=tsan //...  # Thread Sanitizer
bazel test --config=ubsan //... # Undefined Behavior Sanitizer
```

## 开发工具

### 生成 compile_commands.json

为了获得更好的 IDE 支持，你可以生成 `compile_commands.json`：

```bash
bazel run //:refresh_compile_commands
```

### 代码格式化

使用 clang-format 格式化代码：

```bash
find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i