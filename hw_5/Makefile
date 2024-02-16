CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic
SRC_DIR = hw_5
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = $(SRC_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_OBJS = $(patsubst $(TEST_DIR)/%_tests.cc,$(BUILD_DIR)/%_tests.o,$(TEST_SRCS))
TEST_EXE = $(BIN_DIR)/unit_tests

.PHONY: all clean test

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(OBJS) $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%_tests.o: $(TEST_DIR)/%_tests.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

$(TEST_EXE): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lgtest_main -lpthread

test: $(TEST_EXE)
	$(TEST_EXE)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
