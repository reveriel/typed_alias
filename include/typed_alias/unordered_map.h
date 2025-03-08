#pragma once

#include "typed_alias/type.h"
#include <unordered_map>

namespace typed_alias {

template <typename K, typename V, typename Tag>
using UnorderedMap = Type<std::unordered_map<K, V>, Tag>;

template <typename K, typename V, typename Tag>
using UnorderedMultiMap = Type<std::unordered_multimap<K, V>, Tag>;

} // namespace typed_alias
