#pragma once

#include <string>
#include <string_view>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;
};

struct TransparentStringEqual {
    using is_transparent = void;
};

struct TransparentStringHash {
    using is_transparent = void;
};

}  // namespace bookdb
