CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Iinclude
SRC = src/Book.cpp src/Member.cpp src/Loan.cpp src/Algorithms.cpp src/Storage.cpp src/Library.cpp
APP = library_manager
TEST = library_tests

all: $(APP) $(TEST)

$(APP): $(SRC) src/main.cpp
	$(CXX) $(CXXFLAGS) $(SRC) src/main.cpp -o $@

$(TEST): $(SRC) tests/test_library.cpp
	$(CXX) $(CXXFLAGS) $(SRC) tests/test_library.cpp -o $@

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(APP) $(TEST)
