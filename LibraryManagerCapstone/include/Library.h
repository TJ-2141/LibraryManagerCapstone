#pragma once
#include "Algorithms.h"
#include "Book.h"
#include "Loan.h"
#include "Member.h"
#include "Storage.h"
#include <string>
#include <vector>

struct LibraryStats {
    std::size_t totalBooks = 0;
    std::size_t availableBooks = 0;
    std::size_t issuedBooks = 0;
    std::size_t totalMembers = 0;
    std::size_t activeLoans = 0;
    double availabilityPercent = 0.0;
};

class Library {
public:
    explicit Library(Storage storage);

    bool load(std::string& error);
    bool save(std::string& error) const;

    bool addBook(const Book& book, std::string& error);
    bool addMember(const Member& member, std::string& error);
    bool issueBook(const std::string& isbn, const std::string& memberId, std::string& error);
    bool returnBook(const std::string& isbn, std::string& error);

    const std::vector<Book>& books() const;
    const std::vector<Member>& members() const;
    const std::vector<Loan>& loans() const;

    const Book* searchTitle(const std::string& title) const;
    const Book* searchAuthor(const std::string& author) const;
    const Book* searchIsbn(const std::string& isbn) const;

    std::vector<Book> booksSortedByTitle() const;
    std::vector<Book> booksSortedByYear() const;
    LibraryStats stats() const;
    std::string mostIssuedBookTitle() const;

private:
    std::vector<Book> books_;
    std::vector<Member> members_;
    std::vector<Loan> loans_;
    Storage storage_;
};
