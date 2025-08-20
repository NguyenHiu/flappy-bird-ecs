# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -Iinclude -I/opt/homebrew/include -std=c++17 -MMD -MP
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

# Auto-detect all .cpp files in src/
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o)
DEP = $(OBJ:.o=.d)   # Dependency files
OUT = build/game

# Create build directory if it doesn't exist
$(shell mkdir -p build)

# Default target
all: $(OUT)

# Link object files into final executable
$(OUT): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile each .cpp into .o and also generate .d files
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include automatically generated dependency files
-include $(DEP)

# Clean build files
clean:
	rm -f build/*.o build/*.d build/game

# Run the game
run: $(OUT)
	./$(OUT)

.PHONY: all clean run