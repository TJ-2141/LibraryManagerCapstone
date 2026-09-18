# 3–5 Minute Demonstration Script

1. Build with CMake.
2. Run `library_manager`.
3. Choose **1** to show the seeded collection.
4. Choose **3** and search for `C++ Primer`.
5. Choose **7** and issue ISBN `9780321563842` to `M001`.
6. Choose **9** and show that availability and active-loan counts changed.
7. Choose **8** to return the book.
8. Choose **5** to demonstrate merge-sort title ordering.
9. Choose **6** to demonstrate selection-sort year ordering.
10. Exit with **0** and restart the program to demonstrate persistence.

### Talking points

- Encapsulation keeps model state controlled by methods.
- `Library` owns business rules.
- Search/sort algorithms are independently reusable.
- Automated tests verify expected behaviour without manual inspection.
- CMake builds the same code on different environments.
