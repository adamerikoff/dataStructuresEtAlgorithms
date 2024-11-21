# Directories and files
BUILD_DIR := ./build
SRC_DIR := ./src
MAIN_FILE := $(SRC_DIR)/tsunami.f90
OUTPUT_FILE := $(BUILD_DIR)/tsunami
CALCULATION_FILE := ./output.txt
OUTPUT_PLOT := ./output.jpg

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

# Run the compiled program and then run the Python plotting script
run: build
	@echo "Running the program..."
	$(OUTPUT_FILE) > $(CALCULATION_FILE)
	@echo "Running the Python plotting script..."
	python ./src/plot.py

# Clean the build directory
clean:
	@echo "Cleaning build directory and removing output.jpg..."
	rm -rf $(BUILD_DIR) $(OUTPUT_PLOT) $(CALCULATION_FILE)

# Declare phony targets to avoid conflicts with filenames
.PHONY: build run clean
