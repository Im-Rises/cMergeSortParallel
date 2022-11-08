#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <array size> <output file>"
    exit 1
fi

arraySize=$1

echo "$arraySize" > "$2"

for ((i=0; i<arraySize; i++)); do
    echo $RANDOM >> "$2"
done

echo "Done"
