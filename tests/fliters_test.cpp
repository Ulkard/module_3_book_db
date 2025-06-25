#include "book.hpp"
#include "book_database.hpp"
#include "filters.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

namespace {
auto makeBookDb() {
    return BookDatabase{{"Cixin", "Three-Body Problem", 2008, Genre::SciFi, 5.2, 1000},
                            {"Dreeke", "Sizing People Up", 2020, "NonFiction", 5.8, 1000},
                            {"Brooks", "Mythical Man-Month", 1975, "NonFiction", 5.6, 1000}};
}
} // anon ns

TEST(Filters, YearBetween) { 
    BookDatabase db = makeBookDb();
    VectorBookRefs result = filterBooks(db.begin(), db.end(), YearBetween(1970, 2000));
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].get().author, "Brooks");

    VectorBookRefs empty_result = filterBooks(db.begin(), db.end(), YearBetween(2000, 2005));
    EXPECT_EQ(empty_result.size(), 0);
}

TEST(Filters, RatingAbove) { 
    BookDatabase db = makeBookDb();
    VectorBookRefs result = filterBooks(db.begin(), db.end(), RatingAbove(5.5));
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].get().author, "Dreeke");
    EXPECT_EQ(result[1].get().author, "Brooks");
}

TEST(Filters, GenreIs) { 
    BookDatabase db = makeBookDb();
    VectorBookRefs result = filterBooks(db.begin(), db.end(), GenreIs(Genre::NonFiction));
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].get().author, "Dreeke");
    EXPECT_EQ(result[1].get().author, "Brooks");
}

TEST(Filters, all_of) { 
    BookDatabase db = makeBookDb();
    VectorBookRefs result = filterBooks(db.begin(), db.end(), all_of(GenreIs(Genre::NonFiction), RatingAbove(5.7)));
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].get().author, "Dreeke");
}

TEST(Filters, any_of) { 
    BookDatabase db = makeBookDb();
    VectorBookRefs result = filterBooks(db.begin(), db.end(), any_of(GenreIs(Genre::SciFi), RatingAbove(5.7)));
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].get().author, "Cixin");
    EXPECT_EQ(result[1].get().author, "Dreeke");
}