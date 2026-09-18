#pragma once
#include "Book.h"
#include "Member.h"
#include "Loan.h"
#include <filesystem>
#include <string>
#include <vector>

class Storage {
public:
    explicit Storage(std::filesystem::path directory);

    bool load(
        std::vector<Book>& books,
        std::vector<Member>& members,
        std::vector<Loan>& loans,
        std::string& error) const;

    bool save(
        const std::vector<Book>& books,
        const std::vector<Member>& members,
        const std::vector<Loan>& loans,
        std::string& error) const;

private:
    std::filesystem::path directory_;

    static bool writeFile(
        const std::filesystem::path& file,
        const std::string& content,
        std::string& error);
};
