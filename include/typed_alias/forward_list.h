#pragma once

#include "typed_alias/type.h"
#include <forward_list>

namespace typed_alias {

template <typename T, typename Tag>
using ForwardList = Type<std::forward_list<T>, Tag>;

} // namespace typed_alias
