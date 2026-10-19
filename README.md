# Corner Grocer

CS 210 Project that allows a user to select from the following options:

1. Search for Product - uses a loop to find a matching name string in a map [string int]
2. Display List - writes a list to the screen of the items stored in the map and their quantity
3. Display Histogram - writes a list with colored bars representing the amount in inventory
4. Exit Program

The data is obtained from a file when the program begins and parsed into a map, then the parsed file is save with the .dat extension.

As a bonus a Logger class was added to record errors and events in .log files.

## Unit testing review (`ItemTracker.cpp` / `ItemTracker.h`)

### Recommended framework (Visual Studio 2022)
- Use **Microsoft C++ Unit Test Framework (MSTest)** in a separate test project in the same solution (for example `CornerGrocer.Tests`).
- Add the app sources/headers to the test project references so tests can call `ItemTracker`.

### Functions that should be tested first
1. **`loadFile(std::string fileName)`**
   - Why: Core inventory loading logic; all reports depend on this map data.
   - Test: valid file, missing file, empty file, whitespace-only file, repeated item names, mixed capitalization input.
2. **`runReport(int userInput)`**
   - Why: Main dispatcher for menu actions.
   - Test: options `1`, `2`, `3`, and out-of-range values to confirm default behavior.
3. **`toLower(std::string originalText)`**
   - Why: Search correctness depends on case normalization.
   - Test: uppercase/lowercase, mixed case, punctuation, and extended characters.
4. **`colorizeByQuantity(std::string text, int quantity)`**
   - Why: Boundary logic drives histogram color feedback.
   - Test: boundary values `3`, `4`, `6`, `7`.
5. **Output methods (`printItemByName`, `printList`, `printHistogram`)**
   - Why: User-visible behavior and empty-inventory validation live here.
   - Test by redirecting `std::cout`/`std::cin` and asserting expected text for found/not-found items and empty inventory.

### Potential bugs / edge cases to cover
- **Empty input file batch**: loading an empty file should not crash and should log/print meaningful output.
- **Repeated calls to `loadFile`**: current behavior accumulates counts in `inventory_`; verify this is intended.
- **Case handling mismatch**: search is case-insensitive, but map keys are stored with original case; verify displayed key behavior is acceptable.
- **Missing file path**: confirm graceful failure path (`Logger::error`) without changing inventory.
- **Special tokens**: items split on whitespace only; punctuation or multi-word product names may parse unexpectedly.

### Suggested test strategy
- Keep tests in three groups:
  1. **Inventory loading tests** (`loadFile`) with test data files (`valid`, `empty`, `whitespace`, `missing`).
  2. **Search tests** for case-insensitive lookup and item-not-found behavior.
  3. **Validation/output tests** for empty inventory messages and histogram/list formatting boundaries.
- Use small deterministic fixture files in the test project directory and clean up any generated `frequency.dat` in test teardown.
- Start with high-value path tests (load + search + empty file), then add boundary and formatting assertions.
