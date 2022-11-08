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
mergeSortBuildPath="../buildMakeFile/"
mergeSortExeNames=("mergeSortSequential" "mergeSortOpenMp" "mergeSortPThread")
speedTestArraysPath="speedTestArrays/"
outputsPath="outputs/"

# Generate threads number list
threadsNumberList=(1 2 4 8 16 24 48)

# Generate array size list
arraySizeList=()
arraySizeList[0]="$baseArraySize"
for ((i=1; i<iterationNumber; i++)); do
    arraySizeList[i]=$((${arraySizeList[i-1]} * $multiplier))
done

# Generate input array files
for arraySize in "${arraySizeList[@]}"; do
    echo "Generating array of size $arraySize"
#    ./fileGenerator.sh "${arraySize}" "${speedTestArraysPath}array_${arraySize}.txt"
    eval "${mergeSortBuildPath}fileGenerator ${arraySize} ${speedTestArraysPath}array_${arraySize}.txt"
done

# Run merge sort
for arraySize in "${arraySizeList[@]}"; do
    for threadsNumber in "${threadsNumberList[@]}"; do
        echo "Running merge sort with $threadsNumber threads on array of size $arraySize"
        for mergeSortExeName in "${mergeSortExeNames[@]}"; do
            echo "Running $mergeSortExeName with $threadsNumber threads on array of size $arraySize"
            eval "./${mergeSortBuildPath}${mergeSortExeName} < ${speedTestArraysPath}array_${arraySize}.txt > ./${outputsPath}${mergeSortExeName}_${arraySize}_${threadsNumber}.txt $threadsNumber"
        done
    done
done

echo "Done: outputs written in $outputsPath"
