#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <string_view>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;
    bool operator()(std::string_view lhs, const std::string_view rhs) {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    bool operator()(const std::string& lhs, std::string_view rhs) {
        return operator()(std::string_view(lhs), rhs);
    }
    bool operator()(std::string_view lhs, const std::string& rhs) {
        return operator()(lhs, std::string_view(rhs));
    }
};

struct TransparentStringEqual {
    using is_transparent = void;
    bool operator()(std::string_view lhs, const std::string_view rhs) {
        return lhs == rhs;
    }
    
    bool operator()(const std::string& lhs, std::string_view rhs) {
        return operator()(std::string_view(lhs), rhs);
    }
    bool operator()(std::string_view lhs, const std::string& rhs) {
        return operator()(lhs, std::string_view(rhs));
    }
};

struct TransparentStringHash {
    using is_transparent = void;
    bool operator()(std::string_view lhs, const std::string_view rhs) {
        return std::hash<std::string_view>()(lhs) < std::hash<std::string_view>()(rhs);
    }
    
    bool operator()(const std::string& lhs, std::string_view rhs) {
        return operator()(std::string_view(lhs), rhs);
    }
    bool operator()(std::string_view lhs, const std::string& rhs) {
        return operator()(lhs, std::string_view(rhs));
    }
};

}  // namespace bookdb
