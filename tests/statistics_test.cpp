#include "book.hpp"
#include "book_database.hpp"
#include "statistics.hpp"
#include <gtest/gtest.h>

using namespace bookdb;
using namespace std::string_view_literals;

namespace {
auto makeBookDb() {
    return BookDatabase{{"Cixin", "Three-Body Problem", 2008, Genre::SciFi, 5.2, 1000},
                            {"Dreeke", "Sizing People Up", 2020, "NonFiction", 5.8, 1000},
                            {"Brooks", "Mythical Man-Month", 1975, "NonFiction", 5.6, 1000}};
}
} // anon ns

TEST(Statistics, buildAuthorHistogramFlat) {
    BookDatabase db = makeBookDb();
    auto result = buildAuthorHistogramFlat(db);
    EXPECT_EQ(result["Cixin"sv], 1);
    EXPECT_EQ(result["Dreeke"sv], 1);
    EXPECT_EQ(result["Brooks"sv], 1);
}
TEST(Statistics, calculateGenreRatings) {
    BookDatabase db = makeBookDb();
    auto result = calculateGenreRatings(db);
    EXPECT_EQ(result[static_cast<int>(Genre::SciFi)], 5.2);
    EXPECT_NEAR(result[static_cast<int>(Genre::NonFiction)], 5.7, 0.01);
}
TEST(Statistics, calculateAverageRating) {
    BookDatabase db = makeBookDb();
    double result = calculateAverageRating(db);
    EXPECT_NEAR(result, 5.53, 0.01);
}
TEST(Statistics, sampleRandomBooks) {
    BookDatabase db = makeBookDb();
    VectorBookRefs result = sampleRandomBooks(db, 2);
    EXPECT_EQ(result.size(), 2);
    EXPECT_FALSE(result[0] == result[1]);
}
TEST(Statistics, getTopNBy) {
    BookDatabase db = makeBookDb();
    VectorBookRefs result = getTopNBy(db, 2);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].get().author, "Dreeke");
    EXPECT_EQ(result[1].get().author, "Brooks");
}
