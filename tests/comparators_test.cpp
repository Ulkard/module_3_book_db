#include "book.hpp"
#include "book_database.hpp"
#include "comparators.hpp"
#include <gtest/gtest.h>

using namespace bookdb;
using namespace bookdb::comp;

namespace {
auto makeBookDb() {
    return BookDatabase{{"Cixin", "Three-Body Problem", 2008, Genre::SciFi, 5.2, 1000},
                        {"Dreeke", "Sizing People Up", 2020, "NonFiction", 5.8, 1000}};
}
}  // namespace

TEST(Comparators, LessByAuthor) {
    BookDatabase db = makeBookDb();

    // simple
    EXPECT_EQ(LessByAuthor()(db[0], db[1]), true);
    EXPECT_EQ(LessByAuthor()(db[1], db[0]), false);

    // heterogenous
    EXPECT_EQ(LessByAuthor()(db[0], "Dreeke"), true);
    EXPECT_EQ(LessByAuthor()("Dreeke", db[0]), false);
}

TEST(Comparators, GreaterByRating) {
    BookDatabase db = makeBookDb();

    // simple
    EXPECT_EQ(GreaterByRating()(db[0], db[1]), false);
    EXPECT_EQ(GreaterByRating()(db[1], db[0]), true);

    // heterogenous
    EXPECT_EQ(GreaterByRating()(db[0], 5.8), false);
    EXPECT_EQ(GreaterByRating()(5.8, db[0]), true);
}
