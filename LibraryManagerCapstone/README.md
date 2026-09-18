# Library Manager Capstone

A release-ready **C++17 Library Management System** that combines object-oriented design, searching/sorting algorithms, persistence, analytics, validation, and automated testing into one dependable command-line application.

**Author:** Amar Maruti Kate

## Capstone goals

This project is the polished continuation of the earlier Library Manager milestones. It adds:

- Clear separation between domain models, services, persistence, and the CLI.
- Strong input validation and user-friendly error handling.
- Search using linear and binary strategies.
- Sorting using merge sort and selection sort.
- Library analytics and reports.
- CSV persistence with safe temporary-file replacement.
- Automated tests for normal, boundary, invalid, duplicate, and persistence cases.
- CMake, Makefile, and GitHub Actions CI for reproducible builds.

## Features

### Library operations
- Add books and members.
- Search books by ISBN, title, or author.
- Issue and return books.
- Show all books, members, and active loans.
- Prevent issuing unavailable books or to unknown members.
- Prevent invalid/duplicate identifiers.

### Analytics
- Total books, available books, and issued books.
- Total members and active loans.
- Availability percentage.
- Most-issued book.
- Member with the most active loans.
- Author inventory report.

### Algorithms
- Linear search: O(n)
- Binary search on sorted ISBNs: O(log n)
- Merge sort: O(n log n)
- Selection sort: O(n²)

## Project structure

```text
include/          Public headers
src/              Application and implementation files
tests/            Automated tests
data/             Sample persistent CSV data
docs/             Architecture, complexity, test, and demo notes
scripts/          Cross-platform helper scripts
.github/workflows/Continuous integration
```

## Build

### CMake

```bash
cmake -S . -B build
cmake --build build
```

### Run

Linux/macOS:
```bash
./build/library_manager
```

Windows with the default CMake generator:
```powershell
.\build\Debug\library_manager.exe
```

### Make

```bash
make
./library_manager
```

## Run tests

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The test executable can also be run directly:

```bash
./build/library_tests
```

## Sample demo flow

1. Start the application.
2. List books.
3. Search for `C++ Primer`.
4. Issue an available book to member `M001`.
5. Display active loans.
6. Return the book.
7. Open the analytics report.
8. Restart the application and confirm the CSV state was restored.

See `docs/demo_script.md` for a presentation-ready walkthrough.

## Error handling

Invalid input is rejected at the application boundary. Domain operations return descriptive errors rather than silently changing state. Persistence writes to a temporary file first and then replaces the target file, reducing the risk of partially written CSV records.

## Portability

The project uses standard C++17 and has no third-party runtime dependencies. The GitHub Actions workflow builds and tests it on both Ubuntu and Windows.

## Evaluation checklist

- [x] Clean multi-file C++ architecture
- [x] Object-oriented domain model
- [x] Search and sorting algorithms
- [x] Reporting/analytics
- [x] File persistence
- [x] Validation and error handling
- [x] Automated tests
- [x] Complexity notes
- [x] CMake + Makefile
- [x] Cross-platform CI
- [x] Documentation and demo guide
