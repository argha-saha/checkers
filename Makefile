# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude -I/opt/homebrew/include -Wall -Wextra -std=c++17 -MD -MP
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
TEST_DIR = tests

# Targets
MAIN_TARGET = checkers

# Source files
MAIN_SOURCE = $(SRC_DIR)/main.cpp
CORE_SOURCES = $(SRC_DIR)/Game.cpp $(SRC_DIR)/Board.cpp $(SRC_DIR)/Piece.cpp

# Object files
MAIN_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(MAIN_SOURCE) $(CORE_SOURCES))

# Test configuration
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_TARGETS = $(patsubst $(TEST_DIR)/%.cpp, %, $(TEST_SOURCES))

# Default rule
all: $(MAIN_TARGET)

# Main program with SFML linking
$(MAIN_TARGET): $(MAIN_OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LIBS)

# Test programs
$(TEST_TARGETS): %: $(OBJ_DIR)/%.o $(CORE_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LIBS)

# Compilation rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

-include $(wildcard $(OBJ_DIR)/*.d)

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Phony targets
.PHONY: all clean test

# Run a single test
test: $(TEST)
	@echo "Running test: $(TEST)"
	@./$(TEST) && echo "$(TEST) passed!" || echo "$(TEST) failed"

clean:
	rm -rf $(OBJ_DIR) $(MAIN_TARGET) $(TEST_TARGETS)