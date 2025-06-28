#include "book.hpp"
#include "book_database.hpp"
#include <gtest/gtest.h>
#include <iterator>

using namespace bookdb;

auto makeBookDb() {
    return BookDatabase{{"Cixin", "Three-Body Problem", 2008, Genre::SciFi, 5.2, 1000},
                        {"Dreeke", "Sizing People Up", 2020, "NonFiction", 5.8, 1000}};
}

TEST(BookDatabase, addBook) {
    // initializer_list
    BookDatabase db = makeBookDb();
    EXPECT_EQ(db.size(), 2);

    // push_back
    db.push_back({"Weir", "Hail Mary", 2021, Genre::SciFi, 5.4, 1000});
    EXPECT_EQ(db.size(), 3);
    EXPECT_EQ(db[2].author, "Weir");
    EXPECT_EQ(db[2].title, "Hail Mary");

    // emplace_back
    decltype(db)::reference last_book = db.emplace_back("Kahneman", "Fast and Slow", 2011, "NonFiction", 5.8, 1000);
    EXPECT_EQ(db.size(), 4);
    EXPECT_EQ(last_book.author, "Kahneman");
    EXPECT_EQ(last_book.title, "Fast and Slow");
    EXPECT_EQ(last_book.genre, Genre::NonFiction);
}

TEST(BookDatabase, iterators) {
    BookDatabase db = makeBookDb();
    EXPECT_EQ(db.begin()->author, "Cixin");
    EXPECT_EQ((db.begin() + 1)->author, "Dreeke");

    std::vector<Book> db_copy(db.begin(), db.end());
    EXPECT_EQ(db_copy.size(), 2);
    EXPECT_EQ(db_copy[0].title, "Three-Body Problem");
    EXPECT_EQ(db_copy[1].title, "Sizing People Up");

    db.clear();
    EXPECT_EQ(std::distance(db.begin(), db.end()), 0);
}

TEST(BookDatabase, emptyDb) {
    // initializer_list
    BookDatabase db{};
    EXPECT_EQ(db.empty(), true);
    EXPECT_EQ(db.size(), 0);
    EXPECT_EQ(db.getBooks().empty(), true);
    EXPECT_EQ(db.getAuthors().empty(), true);
    EXPECT_EQ(std::distance(db.begin(), db.end()), 0);
}
