#include "Book.h"

Book::Book(std::string isbn, std::string title, std::string author, int year)
    : isbn_(std::move(isbn)), title_(std::move(title)), author_(std::move(author)), year_(year) {}

const std::string& Book::getIsbn() const { return isbn_; }
const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getAuthor() const { return author_; }
int Book::getYear() const { return year_; }
bool Book::isAvailable() const { return available_; }
void Book::setAvailable(bool available) { available_ = available; }
