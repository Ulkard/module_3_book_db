#pragma once

#include <algorithm>
#include <functional>

#include "book.hpp"
#include "book_database.hpp"
#include "concepts.hpp"

namespace bookdb {

using VectorBookRefs = std::vector<std::reference_wrapper<const Book>>;

auto YearBetween(int year_left, int year_right) {
    return [=](const Book &book) -> bool { return book.year >= year_left && book.year <= year_right; };
}
auto RatingAbove(double rating) {
    return [=](const Book &book) -> bool { return book.rating >= rating; };
}
auto GenreIs(Genre genre) {
    return [=](const Book &book) -> bool { return book.genre == genre; };
}

template <typename... Args>
auto all_of(Args... args) {
    return [... args = std::move(args)](const Book &book) -> bool { return (args(book) && ...); };
}

template <typename... Args>
auto any_of(Args... args) {
    return [... args = std::move(args)](const Book &book) -> bool { return (args(book) || ...); };
}

template <BookIterator T, BookPredicate P>
VectorBookRefs filterBooks(T begin, T end, P predicate) {
    VectorBookRefs result;
    for (T it = begin; it != end; ++it) {
        if (predicate(*it)) {
            result.push_back(*it);
        }
    }
    return result;
}

}  // namespace bookdb