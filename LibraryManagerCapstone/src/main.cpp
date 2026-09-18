#include "Library.h"
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>

namespace {
void printBook(const Book& b) {
    std::cout << b.getIsbn() << " | " << b.getTitle()
              << " | " << b.getAuthor()
              << " | " << b.getYear()
              << " | " << (b.isAvailable() ? "Available" : "Issued") << '\n';
}

void listBooks(const Library& library) {
    for (const auto& b : library.books()) printBook(b);
}

void showStats(const Library& library) {
    const auto s = library.stats();
    std::cout << "\n--- Library Analytics ---\n";
    std::cout << "Total books: " << s.totalBooks << '\n';
    std::cout << "Available books: " << s.availableBooks << '\n';
    std::cout << "Issued books: " << s.issuedBooks << '\n';
    std::cout << "Members: " << s.totalMembers << '\n';
    std::cout << "Active loans: " << s.activeLoans << '\n';
    std::cout << "Availability: " << s.availabilityPercent << "%\n";
    std::cout << "Most issued book: " << library.mostIssuedBookTitle() << "\n";
}

int menu() {
    std::cout << "\n=== Library Manager Capstone ===\n"
              << "1. List books\n"
              << "2. Search by ISBN\n"
              << "3. Search by title\n"
              << "4. Search by author\n"
              << "5. Show books sorted by title\n"
              << "6. Show books sorted by year\n"
              << "7. Issue book\n"
              << "8. Return book\n"
              << "9. Analytics report\n"
              << "10. Add book\n"
              << "11. Add member\n"
              << "0. Save and exit\n"
              << "Choice: ";
    int choice{};
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}
}

int main(int argc, char* argv[]) {
    const std::filesystem::path dataDir =
        argc > 1 ? argv[1] : std::filesystem::path("data");
    Library library{Storage(dataDir)};

    std::string error;
    if (!library.load(error)) {
        std::cerr << "Warning: " << error << "\n";
        std::cerr << "Starting with an empty in-memory library.\n";
    }

    while (true) {
        const int choice = menu();
        switch (choice) {
            case 1:
                listBooks(library);
                break;
            case 2:
            case 3:
            case 4: {
                std::string query;
                std::cout << "Search text: ";
                std::getline(std::cin, query);
                const Book* found = nullptr;
                if (choice == 2) found = library.searchIsbn(query);
                else if (choice == 3) found = library.searchTitle(query);
                else found = library.searchAuthor(query);
                if (found) printBook(*found);
                else std::cout << "No matching book found.\n";
                break;
            }
            case 5:
                for (const auto& b : library.booksSortedByTitle()) printBook(b);
                break;
            case 6:
                for (const auto& b : library.booksSortedByYear()) printBook(b);
                break;
            case 7: {
                std::string isbn, member;
                std::cout << "ISBN: "; std::getline(std::cin, isbn);
                std::cout << "Member ID: "; std::getline(std::cin, member);
                if (library.issueBook(isbn, member, error)) std::cout << "Book issued successfully.\n";
                else std::cout << "Error: " << error << '\n';
                break;
            }
            case 8: {
                std::string isbn;
                std::cout << "ISBN: "; std::getline(std::cin, isbn);
                if (library.returnBook(isbn, error)) std::cout << "Book returned successfully.\n";
                else std::cout << "Error: " << error << '\n';
                break;
            }
            case 9:
                showStats(library);
                break;
            case 10: {
                std::string isbn, title, author;
                int year{};
                std::cout << "ISBN: "; std::getline(std::cin, isbn);
                std::cout << "Title: "; std::getline(std::cin, title);
                std::cout << "Author: "; std::getline(std::cin, author);
                std::cout << "Year: ";
                if (!(std::cin >> year)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Error: Year must be an integer.\n";
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (library.addBook(Book(isbn, title, author, year), error)) std::cout << "Book added.\n";
                else std::cout << "Error: " << error << '\n';
                break;
            }
            case 11: {
                std::string id, name;
                std::cout << "Member ID: "; std::getline(std::cin, id);
                std::cout << "Name: "; std::getline(std::cin, name);
                if (library.addMember(Member(id, name), error)) std::cout << "Member added.\n";
                else std::cout << "Error: " << error << '\n';
                break;
            }
            case 0:
                if (library.save(error)) {
                    std::cout << "Data saved. Goodbye!\n";
                    return 0;
                }
                std::cerr << "Save failed: " << error << '\n';
                return 1;
            default:
                std::cout << "Invalid menu choice.\n";
        }
    }
}
