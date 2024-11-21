# Directories and files
BUILD_DIR := ./build
SRC_DIR := ./src
MAIN_FILE := $(SRC_DIR)/main.f90
OUTPUT_FILE := $(BUILD_DIR)/program

# Compiler and flags
FC := gfortran
FFLAGS := -O2 -Wall

# Build target
build: $(OUTPUT_FILE)

# Create build directory, compile, and link the program
$(OUTPUT_FILE): $(MAIN_FILE)
	@echo "Creating build directory if not exists..."
	mkdir -p $(BUILD_DIR)
	@echo "Compiling Fortran source file..."
	$(FC) $(FFLAGS) $(MAIN_FILE) -o $(OUTPUT_FILE)

# Run the compiled program
run: build
	@echo "Running the program..."
	./$(OUTPUT_FILE)

# Clean the build directory
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)

# Declare phony targets to avoid conflicts with filenames
.PHONY: build run clean
