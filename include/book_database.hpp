#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <print>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <set>

#include "book.hpp"
#include "concepts.hpp"
#include "heterogeneous_lookup.hpp"

namespace bookdb {

template <BookContainerLike BookContainer = std::vector<Book>>
class BookDatabase {
public:
    // Type aliases
    using value_type = BookContainer::value_type;
    using reference = BookContainer::reference;
    using pointer = BookContainer::pointer;
    using iterator = BookContainer::iterator;
    using const_iterator = BookContainer::const_iterator;
    using difference_type = BookContainer::difference_type;
    using size_type = BookContainer::size_type;

    iterator begin() {
        return books_.begin();
    }
    iterator end() {
        return books_.end();
    }
    const_iterator begin() const {
        return books_.begin();
    }
    const_iterator end() const {
        return books_.end();
    }

    using AuthorContainer = std::set<std::string, std::less<>>;
    BookDatabase() = default;
    BookDatabase(std::initializer_list<Book> books) 
        : books_(books) {
            for (Book& book : books_) {
                extractAuthor(book);
            }
        }

    // Standard container interface methods
    void clear() {
        books_.clear();
        authors_.clear();
    }
    size_type size() const {
        return books_.size();
    }

    reference operator[](size_type i){
        return books_[i];
    }

    void push_back(Book&& book) {
        extractAuthor(book);
        books_.push_back(book);
    }

    template<typename... Args>
    reference emplace_back(Args&&... args) {
        reference result = books_.emplace_back(std::forward<Args>(args)...);
        extractAuthor(result);
        return result;
    }


    const BookContainer& getBooks() const {
        return books_;
    }
    const AuthorContainer& getAuthors() const {
        return authors_;
    }

private:
    BookContainer books_;
    AuthorContainer authors_;

    void extractAuthor(Book& book) {
        if (!authors_.contains(book.author)) {
            authors_.insert(std::string(book.author));
        }
        book.author = *authors_.find(book.author);
    }
};

}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::BookDatabase<std::vector<bookdb::Book>>> {
    template <typename FormatContext>
    auto format(const bookdb::BookDatabase<std::vector<bookdb::Book>> &db, FormatContext &fc) const {
        /*
        Раскомментируйте, когда bookdb::BookDatabase поддержит интерфейсы, доступные стандартным контейнерам
        (size/begin/...)

        format_to(fc.out(), "BookDatabase (size = {}): ", db.size());

        format_to(fc.out(), "Books:\n");
        for (const auto &book : db.GetBooks()) {
            format_to(fc.out(), "- {}\n", book);
        }

        format_to(fc.out(), "Authors:\n");
        for (const auto &author : db.GetAuthors()) {
            format_to(fc.out(), "- {}\n", author);
        }
        */
        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};
}  // namespace std
