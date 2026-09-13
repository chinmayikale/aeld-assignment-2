#!/bin/bash
#Script for assignment 1
#Author : Chinmayi H K S

# Check if both arguments are provided
if [ $# -lt 2 ]; then
    echo "Error: Two arguments required. Usage: writer.sh <writefile> <writestr>"
    exit 1
fi

writefile=$1
writestr=$2

# Create the directory path if it doesn't exist
mkdir -p "$(dirname "$writefile")"

# Try to create/overwrite the file with the given string
echo "$writestr" > "$writefile"
if [ $? -ne 0 ]; then
    echo "Error: Could not create file '$writefile'."
    exit 1
fi
