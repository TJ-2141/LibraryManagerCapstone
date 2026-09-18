#pragma once
#include "Book.h"
#include <functional>
#include <vector>
#include <cstddef>

namespace algorithms {

const Book* linearSearch(
    const std::vector<Book>& books,
    const std::function<bool(const Book&)>& predicate);

const Book* binarySearchByIsbn(
    const std::vector<Book>& sortedBooks,
    const std::string& isbn);

void mergeSort(
    std::vector<Book>& books,
    const std::function<bool(const Book&, const Book&)>& less);

void selectionSort(
    std::vector<Book>& books,
    const std::function<bool(const Book&, const Book&)>& less);

}
