#!/bin/bash

main="binary_sorting.c"
filename="sorted_numbers.txt"
output="output.o"


sequence=$(seq 999999)
echo "$sequence" > "$filename"
echo "The numbers are saved in $filename."

if gcc "$main" -o "$output"; then
    # Check if the random_numbers file exists
    if [[ -f "$filename" ]]; then
        # Run the compiled output with the random_numbers as an argument
        ./"$output" "$filename"
    else
        echo "Error: $filename not found."
        exit 1
    fi
else
    echo "Compilation failed."
    exit 1
fi

# Clean up the generated binary
rm -f "$output"
# rm -f "$filename"
echo "Compiled files was removed."
