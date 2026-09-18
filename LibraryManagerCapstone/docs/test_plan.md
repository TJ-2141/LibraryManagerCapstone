# Test Plan

The automated suite covers:

**Normal:** valid book/member creation, search, issue and return.

**Boundary:** sorting a small collection and preserving collection size.

**Invalid:** duplicate ISBN, unknown book/member, double issue, and double return.

**Persistence:** save state to CSV, reload into a new `Library`, and verify availability and active-loan state.

Run:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
