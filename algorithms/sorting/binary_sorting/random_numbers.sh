#!/bin/bash

# Output file for the random numbers
output_file="random_numbers.txt"

# Generate a sequence of numbers from -1,000,000 to 1,000,000
sequence=$(seq -1000000 1000000)

# Shuffle the sequence and select 50,000 random numbers
shuffled=$(echo "$sequence" | shuf -n 50000)

# Save the shuffled numbers to the output file
echo "$shuffled" > "$output_file"

echo "Generated 50,000 random numbers in the range -1,000,000 to +1,000,000."
echo "The numbers are saved in $output_file."
