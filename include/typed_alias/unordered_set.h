#pragma once

#include "typed_alias/type.h"
#include <unordered_set>

namespace typed_alias {

template <typename T, typename Tag>
using UnorderedSet = Type<std::unordered_set<T>, Tag>;

template <typename T, typename Tag>
using UnorderedMultiSet = Type<std::unordered_multiset<T>, Tag>;

} // namespace typed_alias
