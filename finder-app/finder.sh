#!/bin/bash
#Script for Assignment 1
#Author: Chinmayi H K S

# Check if both arguments are provided
if [ $# -lt 2 ]; then
    echo "Error: Two arguments required. Usage: finder.sh <filesdir> <searchstr>"
    exit 1
fi

filesdir=$1
searchstr=$2

# Check if filesdir is a valid directory
if [ ! -d "$filesdir" ]; then
    echo "Error: '$filesdir' is not a valid directory."
    exit 1
fi

# Count number of files
file_count=$(find "$filesdir" -type f | wc -l)

# Count number of matching lines
match_count=$(grep -r "$searchstr" "$filesdir" | wc -l)

# Print result
echo "The number of files are $file_count and the number of matching lines are $match_count"
