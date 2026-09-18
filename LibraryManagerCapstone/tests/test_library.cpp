#include "Library.h"
#include <cassert>
#include <filesystem>
#include <iostream>
#include <string>

namespace {
void expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(1);
    }
}

Library sampleLibrary(const std::filesystem::path& dir) {
    Library lib{Storage(dir)};
    std::string error;
    expect(lib.addBook(Book("100", "C++ Primer", "Lippman", 2012), error), "add first book");
    expect(lib.addBook(Book("200", "Clean Code", "Martin", 2008), error), "add second book");
    expect(lib.addBook(Book("300", "Algorithms", "Sedgewick", 2011), error), "add third book");
    expect(lib.addMember(Member("M001", "Amar"), error), "add member");
    return lib;
}
}

int main() {
    const auto temp = std::filesystem::temp_directory_path() / "library_capstone_tests";
    std::filesystem::remove_all(temp);
    std::filesystem::create_directories(temp);

    // Normal cases
    {
        auto lib = sampleLibrary(temp);
        std::string error;
        expect(lib.searchTitle("C++ Primer") != nullptr, "title search");
        expect(lib.searchAuthor("Martin") != nullptr, "author search");
        expect(lib.searchIsbn("100") != nullptr, "ISBN search");
        expect(lib.issueBook("100", "M001", error), "issue valid book");
        expect(!lib.searchIsbn("100")->isAvailable(), "issued state");
        expect(lib.returnBook("100", error), "return valid book");
        expect(lib.searchIsbn("100")->isAvailable(), "returned state");
    }

    // Boundary cases
    {
        auto lib = sampleLibrary(temp);
        std::string error;
        auto sorted = lib.booksSortedByTitle();
        expect(sorted.size() == 3, "sorting preserves count");
        expect(sorted.front().getTitle() == "Algorithms", "merge sort order");
        auto byYear = lib.booksSortedByYear();
        expect(byYear.front().getYear() == 2008, "selection sort order");
    }

    // Invalid cases
    {
        auto lib = sampleLibrary(temp);
        std::string error;
        expect(!lib.addBook(Book("100", "Duplicate", "Other", 2020), error), "duplicate ISBN blocked");
        expect(!lib.issueBook("999", "M001", error), "unknown book blocked");
        expect(!lib.issueBook("100", "M999", error), "unknown member blocked");
        expect(lib.issueBook("100", "M001", error), "valid issue");
        expect(!lib.issueBook("100", "M001", error), "double issue blocked");
        expect(lib.returnBook("100", error), "return after issue");
        expect(!lib.returnBook("100", error), "double return blocked");
    }

    // Persistence round trip
    {
        auto lib = sampleLibrary(temp);
        std::string error;
        expect(lib.issueBook("200", "M001", error), "prepare persisted loan");
        expect(lib.save(error), "save persisted state");

        Library reloaded{Storage(temp)};
        expect(reloaded.load(error), "reload state");
        expect(!reloaded.searchIsbn("200")->isAvailable(), "persisted availability");
        expect(reloaded.stats().activeLoans == 1, "persisted active loan");
    }

    std::filesystem::remove_all(temp);
    std::cout << "All library capstone tests passed.\n";
    return 0;
}
