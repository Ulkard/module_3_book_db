#pragma once

#include <concepts>
#include <iterator>
#include <type_traits>

#include "book.hpp"

namespace bookdb {

template <typename T>
concept BookContainerLike = std::same_as<typename T::value_type, Book>;

template <typename T>
concept BookIterator = std::is_same_v<Book, 
    typename std::iterator_traits<T>::value_type>;

/*template <typename S, typename I>
concept BookSentinel = true;*/

template <typename P>
concept BookPredicate = std::predicate<P, Book>;

template <typename C>
concept BookComparator = std::predicate<C, Book, Book>;

}  // namespace bookdb