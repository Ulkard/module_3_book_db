#pragma once

#include "book.hpp"
#include <algorithm>
#include <string_view>

namespace bookdb::comp {

struct LessByAuthor {
    using is_transparent = void;
    
    bool operator()(const Book& lhs, const Book& rhs) {
        return std::lexicographical_compare(
            lhs.author.begin(), lhs.author.end(),
            rhs.author.begin(), rhs.author.end()
        );
    } 
    bool operator()(const Book& lhs, std::string_view rhs) {
        return std::lexicographical_compare(
            lhs.author.begin(), lhs.author.end(),
            rhs.begin(), rhs.end()
        );
    }
    bool operator()(std::string_view lhs, const Book& rhs) {
        return std::lexicographical_compare(
            lhs.begin(), lhs.end(),
            rhs.author.begin(), rhs.author.end()
        );
    }
};

struct LessByRating {
    using is_transparent = void;
    
    bool operator()(const Book& lhs, const Book& rhs) {
        return lhs.rating < rhs.rating;
    } 
    bool operator()(const Book& lhs, double rhs) {
        return lhs.rating < rhs;
    }
    bool operator()(double lhs, const Book& rhs) {
        return lhs < rhs.rating;
    }
};

}  // namespace bookdb::comp