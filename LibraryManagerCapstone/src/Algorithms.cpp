#include "Algorithms.h"
#include <algorithm>

namespace algorithms {

const Book* linearSearch(
    const std::vector<Book>& books,
    const std::function<bool(const Book&)>& predicate) {
    for (const auto& book : books) {
        if (predicate(book)) return &book;
    }
    return nullptr;
}

const Book* binarySearchByIsbn(
    const std::vector<Book>& sortedBooks,
    const std::string& isbn) {
    std::size_t left = 0;
    std::size_t right = sortedBooks.size();
    while (left < right) {
        const std::size_t mid = left + (right - left) / 2;
        const auto& current = sortedBooks[mid].getIsbn();
        if (current == isbn) return &sortedBooks[mid];
        if (current < isbn) left = mid + 1;
        else right = mid;
    }
    return nullptr;
}

void mergeSort(
    std::vector<Book>& books,
    const std::function<bool(const Book&, const Book&)>& less) {
    if (books.size() <= 1) return;
    const std::size_t mid = books.size() / 2;

    std::vector<Book> left(books.begin(), books.begin() + static_cast<long>(mid));
    std::vector<Book> right(books.begin() + static_cast<long>(mid), books.end());

    mergeSort(left, less);
    mergeSort(right, less);

    std::size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (less(left[i], right[j])) books[k++] = left[i++];
        else books[k++] = right[j++];
    }
    while (i < left.size()) books[k++] = left[i++];
    while (j < right.size()) books[k++] = right[j++];
}

void selectionSort(
    std::vector<Book>& books,
    const std::function<bool(const Book&, const Book&)>& less) {
    for (std::size_t i = 0; i < books.size(); ++i) {
        std::size_t best = i;
        for (std::size_t j = i + 1; j < books.size(); ++j) {
            if (less(books[j], books[best])) best = j;
        }
        if (best != i) std::swap(books[i], books[best]);
    }
}

}
