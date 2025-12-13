CXX = g++
CC  = gcc

CXXFLAGS = -std=c++23 -Wall -Wextra -I./src/include
CFLAGS   = -Wall -Wextra -I./src/include

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
	@mkdir -p $(BUILD_DIR)/src
	@mkdir -p $(BIN_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	@./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all run clean
