#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Usage: $0 <base array size> <multiplier> <iteration number>"
    exit 1
fi

# Input parameters
baseArraySize=$1
multiplier=$2
iterationNumber=$3

# Merge sort scripts
scriptsPath="BuildMakeFile/"
mergeSortScriptsList=("mergeSortSequential" "mergeSortOpenMp" "mergeSortPThread")

# Generate threads number list
threadsNumberList=(1 2 4 8 24 48)

# Generate array size list
arraySizeList=()
arraySizeList[0]="$baseArraySize"
for ((i=1; i<iterationNumber; i++)); do
    arraySizeList[i]=$((${arraySizeList[i-1]} * $multiplier))
done

# Generate input array files
for arraySize in "${arraySizeList[@]}"; do
    echo "Generating array of size $arraySize"
    ./fileGenerator.sh "$arraySize" "array${arraySize}.txt"
done

# Run merge sort
for arraySize in "${arraySizeList[@]}"; do
    for threadsNumber in "${threadsNumberList[@]}"; do
        echo "Running merge sort with $threadsNumber threads on array of size $arraySize"
        for script in "${mergeSortScriptsList[@]}"; do
            echo "Running $script with $threadsNumber threads on array of size $arraySize"
            ./"$scriptsPath$script" "array${arraySize}.txt" "$threadsNumber" "mergeSort${arraySize}_${threadsNumber}.txt"
        done
    done
done

echo "Done"
