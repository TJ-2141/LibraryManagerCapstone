#include "Library.h"
#include <algorithm>
#include <iomanip>
#include <map>
#include <sstream>

Library::Library(Storage storage) : storage_(std::move(storage)) {}

bool Library::load(std::string& error) {
    return storage_.load(books_, members_, loans_, error);
}

bool Library::save(std::string& error) const {
    return storage_.save(books_, members_, loans_, error);
}

bool Library::addBook(const Book& book, std::string& error) {
    if (book.getIsbn().empty() || book.getTitle().empty() || book.getAuthor().empty() || book.getYear() < 0) {
        error = "Invalid book details.";
        return false;
    }
    if (searchIsbn(book.getIsbn())) {
        error = "A book with this ISBN already exists.";
        return false;
    }
    books_.push_back(book);
    return true;
}

bool Library::addMember(const Member& member, std::string& error) {
    if (member.getId().empty() || member.getName().empty()) {
        error = "Invalid member details.";
        return false;
    }
    const auto it = std::find_if(members_.begin(), members_.end(),
        [&](const Member& m){ return m.getId() == member.getId(); });
    if (it != members_.end()) {
        error = "A member with this ID already exists.";
        return false;
    }
    members_.push_back(member);
    return true;
}

bool Library::issueBook(const std::string& isbn, const std::string& memberId, std::string& error) {
    Book* book = nullptr;
    for (auto& b : books_) if (b.getIsbn() == isbn) { book = &b; break; }
    if (!book) { error = "Book not found."; return false; }
    if (!book->isAvailable()) { error = "Book is already issued."; return false; }

    const auto member = std::find_if(members_.begin(), members_.end(),
        [&](const Member& m){ return m.getId() == memberId; });
    if (member == members_.end()) { error = "Member not found."; return false; }

    book->setAvailable(false);
    loans_.emplace_back(isbn, memberId);
    return true;
}

bool Library::returnBook(const std::string& isbn, std::string& error) {
    auto book = std::find_if(books_.begin(), books_.end(),
        [&](const Book& b){ return b.getIsbn() == isbn; });
    if (book == books_.end()) { error = "Book not found."; return false; }
    if (book->isAvailable()) { error = "Book is not currently issued."; return false; }

    for (auto it = loans_.rbegin(); it != loans_.rend(); ++it) {
        if (it->getIsbn() == isbn && it->isActive()) {
            it->close();
            book->setAvailable(true);
            return true;
        }
    }
    error = "Active loan record not found.";
    return false;
}

const std::vector<Book>& Library::books() const { return books_; }
const std::vector<Member>& Library::members() const { return members_; }
const std::vector<Loan>& Library::loans() const { return loans_; }

const Book* Library::searchTitle(const std::string& title) const {
    return algorithms::linearSearch(books_, [&](const Book& b){ return b.getTitle() == title; });
}

const Book* Library::searchAuthor(const std::string& author) const {
    return algorithms::linearSearch(books_, [&](const Book& b){ return b.getAuthor() == author; });
}

const Book* Library::searchIsbn(const std::string& isbn) const {
    return algorithms::linearSearch(books_, [&](const Book& b){ return b.getIsbn() == isbn; });
}

std::vector<Book> Library::booksSortedByTitle() const {
    auto result = books_;
    algorithms::mergeSort(result, [](const Book& a, const Book& b){
        return a.getTitle() < b.getTitle();
    });
    return result;
}

std::vector<Book> Library::booksSortedByYear() const {
    auto result = books_;
    algorithms::selectionSort(result, [](const Book& a, const Book& b){
        return a.getYear() < b.getYear();
    });
    return result;
}

LibraryStats Library::stats() const {
    LibraryStats s;
    s.totalBooks = books_.size();
    s.totalMembers = members_.size();
    for (const auto& b : books_) {
        if (b.isAvailable()) ++s.availableBooks;
        else ++s.issuedBooks;
    }
    for (const auto& l : loans_) if (l.isActive()) ++s.activeLoans;
    s.availabilityPercent = s.totalBooks == 0 ? 0.0 :
        (100.0 * static_cast<double>(s.availableBooks) / static_cast<double>(s.totalBooks));
    return s;
}

std::string Library::mostIssuedBookTitle() const {
    std::map<std::string, int> counts;
    for (const auto& l : loans_) ++counts[l.getIsbn()];
    std::string bestIsbn;
    int bestCount = 0;
    for (const auto& [isbn, count] : counts) {
        if (count > bestCount) { bestCount = count; bestIsbn = isbn; }
    }
    if (bestIsbn.empty()) return "No loan history";
    if (const auto* b = searchIsbn(bestIsbn)) return b->getTitle();
    return "Unknown book";
}
