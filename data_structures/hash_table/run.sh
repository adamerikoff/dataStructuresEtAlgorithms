#!/bin/bash

main="main.c"
hash_table="hash_table.c"
output="output.o"

# Compile both main.c and hash_table.c
if gcc "$main" "$hash_table" -o "$output"; then
    ./"$output"
else
    echo "Compilation failed."
    exit 1
fi

# Clean up the generated binary
rm -f "$output"
echo "Compiled binary was removed."
