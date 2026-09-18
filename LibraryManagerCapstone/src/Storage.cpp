#include "Storage.h"
#include <fstream>
#include <sstream>
#include <system_error>

namespace {
std::vector<std::string> splitCsv(const std::string& line) {
    std::vector<std::string> out;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ',')) out.push_back(item);
    return out;
}
std::string booksCsv(const std::vector<Book>& books) {
    std::ostringstream out;
    out << "isbn,title,author,year,available\n";
    for (const auto& b : books)
        out << b.getIsbn() << ',' << b.getTitle() << ',' << b.getAuthor() << ','
            << b.getYear() << ',' << (b.isAvailable() ? 1 : 0) << '\n';
    return out.str();
}
std::string membersCsv(const std::vector<Member>& members) {
    std::ostringstream out;
    out << "id,name\n";
    for (const auto& m : members) out << m.getId() << ',' << m.getName() << '\n';
    return out.str();
}
std::string loansCsv(const std::vector<Loan>& loans) {
    std::ostringstream out;
    out << "isbn,member_id,active\n";
    for (const auto& l : loans)
        out << l.getIsbn() << ',' << l.getMemberId() << ',' << (l.isActive() ? 1 : 0) << '\n';
    return out.str();
}
}

Storage::Storage(std::filesystem::path directory) : directory_(std::move(directory)) {}

bool Storage::writeFile(
    const std::filesystem::path& file,
    const std::string& content,
    std::string& error) {
    std::ofstream out(file, std::ios::trunc);
    if (!out) {
        error = "Unable to open " + file.string() + " for writing.";
        return false;
    }
    out << content;
    if (!out.good()) {
        error = "Write failed for " + file.string() + ".";
        return false;
    }
    return true;
}

bool Storage::load(
    std::vector<Book>& books,
    std::vector<Member>& members,
    std::vector<Loan>& loans,
    std::string& error) const {
    books.clear(); members.clear(); loans.clear();
    std::ifstream bf(directory_ / "books.csv");
    std::ifstream mf(directory_ / "members.csv");
    std::ifstream lf(directory_ / "loans.csv");

    if (!bf || !mf || !lf) {
        error = "Data files are missing or cannot be opened.";
        return false;
    }

    std::string line;
    std::getline(bf, line);
    while (std::getline(bf, line)) {
        auto c = splitCsv(line);
        if (c.size() != 5) continue;
        try {
            Book b(c[0], c[1], c[2], std::stoi(c[3]));
            b.setAvailable(c[4] == "1");
            books.push_back(std::move(b));
        } catch (...) {}
    }

    std::getline(mf, line);
    while (std::getline(mf, line)) {
        auto c = splitCsv(line);
        if (c.size() == 2) members.emplace_back(c[0], c[1]);
    }

    std::getline(lf, line);
    while (std::getline(lf, line)) {
        auto c = splitCsv(line);
        if (c.size() == 3) {
            Loan l(c[0], c[1]);
            if (c[2] != "1") l.close();
            loans.push_back(std::move(l));
        }
    }

    return true;
}

bool Storage::save(
    const std::vector<Book>& books,
    const std::vector<Member>& members,
    const std::vector<Loan>& loans,
    std::string& error) const {
    std::error_code ec;
    std::filesystem::create_directories(directory_, ec);
    if (ec) {
        error = "Unable to create data directory: " + ec.message();
        return false;
    }

    const auto files = std::vector<std::pair<std::string, std::string>>{
        {"books.csv", booksCsv(books)},
        {"members.csv", membersCsv(members)},
        {"loans.csv", loansCsv(loans)}
    };

    for (const auto& [name, content] : files) {
        const auto target = directory_ / name;
        const auto temp = directory_ / (name + ".tmp");
        if (!writeFile(temp, content, error)) return false;
        std::filesystem::rename(temp, target, ec);
        if (ec) {
            std::filesystem::remove(target, ec);
            std::filesystem::rename(temp, target, ec);
            if (ec) {
                error = "Unable to replace " + target.string() + ": " + ec.message();
                return false;
            }
        }
    }
    return true;
}
