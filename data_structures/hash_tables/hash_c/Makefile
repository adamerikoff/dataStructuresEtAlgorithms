# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -Wno-unused-function -MMD -MP

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRCS = $(SRC_DIR)/hash.c $(SRC_DIR)/helper_prime.c $(SRC_DIR)/main.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Output binary
TARGET = $(BUILD_DIR)/output

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR)

start:
	$(TARGET)

# Phony targets
.PHONY: all clean start
