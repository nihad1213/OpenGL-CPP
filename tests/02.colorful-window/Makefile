CXX = g++
CC = gcc

CXX_FLAGS = std=c++23 -Wall -Wextra -I./src/include
CFLAGS = -Wall -Wextra -I./src/include

LIBS = -lglfw -lGL -lm -ldl

SRC_DIRS = src
BUILD_DIR = build
BIN_DIR   = bin

CPP_SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
C_SOURCES   = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_SOURCES)) \
          $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))

TARGET = $(BIN_DIR)/opengl_program

all: directories $(TARGET)

directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)/src

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "Build complete: $(TARGET)"

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	@make -s all
	@./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean complete"

rebuild: clean all

help:
	@echo "Targets:"
	@echo "  all     - Build"
	@echo "  run     - Build and run"
	@echo "  clean   - Remove build files"
	@echo "  rebuild - Clean then build"
	@echo "  help    - Show this help message"

.PHONY: all directories run clean rebuild help
