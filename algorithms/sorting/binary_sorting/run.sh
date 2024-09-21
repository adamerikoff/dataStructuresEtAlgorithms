#!/bin/bash

main="binary_sorting.c"
random_numbers="random_numbers.txt"
output="output.o"

# Compile the C file
if gcc "$main" -o "$output"; then
    # Check if the random_numbers file exists
    if [[ -f "$random_numbers" ]]; then
        # Run the compiled output with the random_numbers as an argument
        ./"$output" "$random_numbers"
    else
        echo "Error: $random_numbers not found."
        exit 1
    fi
else
    echo "Compilation failed."
    exit 1
fi

# Clean up the generated binary
rm -f "$output"
echo "Compiled files was removed."
