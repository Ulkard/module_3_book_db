#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string_view>
#include <flat_map>

#include "book.hpp"
#include "book_database.hpp"
#include "comparators.hpp"

#include <print>

namespace bookdb {

using VectorBookRefs = std::vector<std::reference_wrapper<const Book>>;

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto buildAuthorHistogramFlat(const BookDatabase<T> &db, Comparator comp = {}) {
    std::flat_map<std::string_view, size_t, Comparator> result;
    for (const auto& book: db) {
        ++result[book.author];
    }
    return result;
}

template <BookContainerLike T>
auto calculateGenreRatings(const BookDatabase<T> &db) {
    std::flat_map<Genre, double> ratings;
    std::flat_map<Genre, size_t> counters;
    for (const auto& book: db) {
        ratings[book.Genre] += book.rating;
        ++counters[book.Genre];
    }
    std::transform(ratings.begin(), ratings.end(), 
        counters.begin(), ratings.begin(),
        [](const auto& rating, const auto& counter) -> decltype(ratings)::value_type {
            return {rating.first, rating/counter};
        }
    );
    return ratings;
}

template <BookContainerLike T>
double calculateAverageRating(const BookDatabase<T> &db) {
    return std::reduce(db.begin(), db.end(), 0., [](double init_v, const Book& book) {
        return init_v + book.rating;
    });
}

template <BookContainerLike T>
VectorBookRefs sampleRandomBooks(const BookDatabase<T> &db, size_t N) {
    VectorBookRefs result;
    std::sample(db.begin(), db.end(), std::back_inserter(result), N,
                std::mt19937 { std::random_device{}() });
    return result;
}

template <BookContainerLike T>
VectorBookRefs getTopNBy(BookDatabase<T> &db, size_t N) {
    std::sort(db.begin(), db.end(), comp::LessByRating());
    return {db.begin(), db.begin() + std::min(N, db.size()-1)};
}

}  // namespace bookdb
