#!/bin/bash

main="main.c"
output="output.o"

# Compile both main.c and hash_table.c
if gcc "$main" -o "$output"; then
    ./"$output"
else
    echo "Compilation failed."
    exit 1
fi

# Clean up the generated binary
rm -f "$output"
echo "Compiled binary was removed."
