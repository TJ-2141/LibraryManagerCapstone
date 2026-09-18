# Complexity Notes

| Operation | Strategy | Time | Extra Space |
|---|---|---:|---:|
| Search ISBN/title/author | Linear search | O(n) | O(1) |
| Search sorted ISBN | Binary search | O(log n) | O(1) |
| Sort by title | Merge sort | O(n log n) | O(n) |
| Sort by year | Selection sort | O(n²) | O(1) extra |
| Analytics scan | Sequential scan | O(n + m) | O(k) for counts |

`n` is the number of books and `m` is the number of loan records. `k` is the number of unique ISBNs in loan history.
