#pragma once
#include <string>

class Book {
public:
    Book() = default;
    Book(std::string isbn, std::string title, std::string author, int year);

    const std::string& getIsbn() const;
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getYear() const;
    bool isAvailable() const;

    void setAvailable(bool available);

private:
    std::string isbn_;
    std::string title_;
    std::string author_;
    int year_ = 0;
    bool available_ = true;
};
