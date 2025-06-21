#pragma once

#include <algorithm>
#include <array>
#include <format>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

namespace bookdb {

enum class Genre { Fiction, NonFiction, SciFi, Biography, Mystery, Unknown };

// Ваш код для constexpr преобразования строк в enum::Genre и наоборот здесь
static constexpr std::array<std::pair<std::string_view, Genre>, 5> genres_arr{ {
    {"Fiction", Genre::Fiction},
    {"NonFiction", Genre::NonFiction},
    {"SciFi", Genre::SciFi},
    {"Biography", Genre::Biography},
    {"Mystery", Genre::Mystery}
}};

constexpr Genre GenreFromString(std::string_view s) {
    // Ваш код здесь
    auto it = std::find_if(genres_arr.begin(), genres_arr.end(), [s](
        const std::pair<std::string_view, Genre>& elem) {
        return elem.first == s;
    });

    if (it != genres_arr.end()) {
        return it->second;
    }
    return Genre::Unknown;
}

struct Book {
    // string_view для экономии памяти, чтобы ссылаться на оригинальную строку, хранящуюся в другом контейнере
    std::string_view author;
    std::string title;

    int year;
    Genre genre;
    double rating;
    int read_count;

    // Ваш код для конструкторов здесь
    constexpr Book(std::string_view _author, const std::string& _title, int _year, Genre _genre)
        : author(_author)
        , title(_title)
        , year(_year)
        , genre(_genre) {}

    constexpr Book(std::string_view _author, const std::string& _title, int _year, std::string_view _genre)
        : author(_author)
        , title(_title)
        , year(_year)
        , genre(GenreFromString(_genre)) {}

};
}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::Genre, char> {
    template <typename FormatContext>
    auto format(const bookdb::Genre g, FormatContext &fc) const {
        std::string genre_str;

        // clang-format off
        using bookdb::Genre;
        switch (g) {
            case Genre::Fiction:    genre_str = "Fiction"; break;
            case Genre::Mystery:    genre_str = "Mystery"; break;
            case Genre::NonFiction: genre_str = "NonFiction"; break;
            case Genre::SciFi:      genre_str = "SciFi"; break;
            case Genre::Biography:  genre_str = "Biography"; break;
            case Genre::Unknown:    genre_str = "Unknown"; break;
            default:
                throw logic_error{"Unsupported bookdb::Genre"};
            }
        // clang-format on
        return format_to(fc.out(), "{}", genre_str);
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

// Ваш код для std::formatter<Book> здесь
template <>
struct formatter<bookdb::Book, char> {
    template <typename FormatContext>
    auto format(const bookdb::Book b, FormatContext &fc) const {
        return format_to(fc.out(), "{}({}) by {}, {}. read {} times. rating {}", b.title, b.genre, b.author, b.year, b.read_count, b.rating);
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

}  // namespace std
