# cMergeSortParallel

<p align="center">
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="cLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/199836862-958b46d2-2426-48e0-9866-68dd364f9066.png" alt="openmpLogo" style="height:60px;"/>
</p>

## Description

Merge Sort algorithm implemented in C available in three versions:

- Sequential
- Parallel with OpenMP
- Parallel with Pthreads (Linux only)

Merge sort is a divide and conquer algorithm that was invented by John von Neumann in 1945.  
A detailed description of the algorithm can be found [here](https://en.wikipedia.org/wiki/Merge_sort).

The implemented algorithm are the following:

- [x] Merge Sort
- [x] Parallel Merge Sort
- [x] Parallel Merge Sort using OpenMP
- [x] Parallel Merge Sort using PThread

## Dependencies

- C90
- GNU90 (PThread)
- CMake or Make
- C90 compiler (GCC, Clang, MSVC, ...)

## Table of Contents

- [Description](#description)
- [Dependencies](#Dependencies)
- [Table of Contents](#table-of-contents)
- [Quickstart](#Quickstart)
- [Algorithms](#Algorithms)
    - [Sequential Merge Sort V1](#Sequential-Merge-Sort-V1)
    - [Sequential Merge Sort V2](#Sequential-Merge-Sort-V2)
    - [Merge Sort algorithm chosen](#Merge-Sort-algorithm-chosen)
    - [Parallel Merge Sort](#Parallel-Merge-Sort)
    - [Details on the implementation](#Details-on-the-implementation)
- [Details on the implementation](#Details-on-the-implementation)
    - [Sequential Merge Sort](#Sequential-Merge-Sort)
    - [Parallel Merge Sort with OpenMP](#Parallel-Merge-Sort-with-OpenMP)
    - [Parallel Merge Sort with Pthreads](#Parallel-Merge-Sort-with-Pthreads)
- [Results](#Results)
- [How to use](#How-to-use)
- [Speed test](#Speed-test)
- [Compilation](#Compilation)
    - [Compilation with CMake](#Compilation-with-CMake)
        - [Windows](#Windows)
        - [Linux](#Linux)
    - [Compile with Make](#Compile-with-Make)
    - [Setup](#Setup)
    - [Compilation](#Compilation)
- [Project Architecture](#Project-Architecture)
- [GitHub Actions](#GitHub-Actions)
- [Documentations](#Documentations)
- [Contributors](#Contributors)

## Quickstart

Depending on you `operating system` you will need to install some libs, they are installed differently depending on your
system, please follow the instructions in the `Compilation` section.

For an explanation on `How to use` go to the according section.

The different algorithms used are described below.

## Algorithms

The different algorithms used are described below.

For more detail about them refer to :  
Introduction to Algorithms, 3rd Edition, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein

### Sequential Merge Sort V1

```algorithm
mergeSort(A, n, temp)
    if n > 1
        mergeSort(A, n/2, temp)
        mergeSort(A + n/2, n - n/2, temp)
        merge(A, n, temp)
```

```algorithm
merge(A, n, temp)
    i = 0
    j = n/2
    k = 0
    while i < n/2 and j < n
        if A[i] < A[j]
            temp[k] = A[i]
            i++
        else
            temp[k] = A[j]
            j++
        k++
    while i < n/2
        temp[k] = A[i]
        i++
        k++
    while j < n
        temp[k] = A[j]
        j++
        k++
    for i = 0 to n
        A[i] = temp[i]
```

### Sequential Merge Sort V2

```algorithm
mergeSort(A,p,r)
    if p < r
        q = (p+r)/2
        mergeSort(A,p,q)
        mergeSort(A,q+1,r)
        merge(A,p,q,r)
```

```algorithm
merge(A,p,q,r)
    n1 = q-p+1
    n2 = r-q
    let L[1..n1+1] and R[1..n2+1] be new arrays
    for i = 1 to n1
        L[i] = A[p+i-1]
    for j = 1 to n2
        R[j] = A[q+j]
    L[n1+1] = ∞
    R[n2+1] = ∞
    i = 1
    j = 1
    for k = p to r
        if L[i] <= R[j]
            A[k] = L[i]
            i = i + 1
        else A[k] = R[j]
            j = j + 1
```

### Merge Sort algorithm chosen

The algorithm chosen is the first one, it is the simplest to understand and the most efficient.
The most efficient because it only creates one buffer array named `temp` of size `n` and not two of size `n/2` at each
recursive call
of the function `merge`.
By comparing the two algorithms, for any array size the first algorithm was two times faster than the second one.

> **Note**
> For the parallel algorithms, the first algorithm is used.

### Parallel Merge Sort

The parallel merge sort is a simple implementation of the merge sort algorithm, it uses the `fork` system call to create
a new process for each recursive call.
The `merge` function is the same as the one used in the sequential merge sort.
The algorithm is written using `Cilk` syntax:

```algorithm
mergeSortParallel(A, n, temp)
    if n > 1
        spawn mergeSortParallel(A, n/2, temp)
        mergeSortParallel(A + n/2, n - n/2, temp)
        sync
        merge(A, n, temp)
```

```algorithm
merge(A, n, temp)
    i = 0
    j = n/2
    k = 0
    while i < n/2 and j < n
        if A[i] < A[j]
            temp[k] = A[i]
            i++
        else
            temp[k] = A[j]
            j++
        k++
    while i < n/2
        temp[k] = A[i]
        i++
        k++
    while j < n
        temp[k] = A[j]
        j++
        k++
    for i = 0 to n
        A[i] = temp[i]
```

## Details on the implementation

The parallel algorithm are customized to prevent creation of threads if the array size is too small.
The `mergeSort` function is called with a minimum size of `MULTITHREAD_THRESHOLD` (defined in the header file).
If the array size is smaller than this threshold, the algorithm is executed sequentially preventing loss of performance
from creating thread for small arrays.

This also apply in the recursive calls of the `mergeSort` function. After some division of the recursive call of
the `mergeSort` function the array size
is smaller than the threshold, the algorithm is executed sequentially.

The algorithm is the following:

```algorithm
mergeSortParallel(A, n, temp)
    if (size < MULTITHREAD_THRESHOLD)
        mergeSortSequential(array, size, bufferArray);
    else
        mergeSortParallel(A, n/2, temp)
        mergeSortParallel(A + n/2, n - n/2, temp)
        merge(A, n, temp)
```

## Results

| Number of int (Array size) | Number of threads | Sequential time (Work) (s) | Parallel OpenMP time (s) | Parallel Pthread time (s) |
|----------------------------|-------------------|----------------------------|--------------------------|---------------------------|
| 1000000                    | 1                 | 0.219678                   | 0.21941                  | 0.23636                   |
|                            | 2                 |                            | 0.140376                 | 0.137846                  |  

<details>
<summary>Click here to get the details for an array of 10 to 10 000 000 ints.</summary>

| Number of int (Array size) | Number of threads | Sequential time (Work) (s) | Parallel OpenMP time (s) | Parallel Pthread time (s) |
|----------------------------|-------------------|----------------------------|--------------------------|---------------------------|
| 10                         | 1                 | 0.000023                   | 0.000079                 | 0.000012                  |
|                            | 2                 |                            | 0.000216                 | 0.000011                  |
|                            | 4                 |                            | 0.000439                 | 0.000011                  |
|                            | 8                 |                            | 0.007493                 | 0.000011                  |
|                            | 16                |                            | 0.000752                 | 0.000012                  |
|                            | 24                |                            | 0.000861                 | 0.000012                  |
|                            | 48                |                            | 0.00178                  | 0.000012                  |
| 100                        | 1                 | 0.000034                   | 0.000039                 | 0.000025                  |
|                            | 2                 |                            | 0.000228                 | 0.000025                  |
|                            | 4                 |                            | 0.000211                 | 0.000032                  |
|                            | 8                 |                            | 0.005617                 | 0.000025                  |
|                            | 16                |                            | 0.000866                 | 0.000025                  |
|                            | 24                |                            | 0.001311                 | 0.000025                  |
|                            | 48                |                            | 0.002728                 | 0.000026                  |
| 1000                       | 1                 | 0.000383                   | 0.000387                 | 0.000159                  |
|                            | 2                 |                            | 0.00411                  | 0.001905                  |
|                            | 4                 |                            | 0.000531                 | 0.000493                  |
|                            | 8                 |                            | 0.007541                 | 0.000425                  |
|                            | 16                |                            | 0.000808                 | 0.000354                  |
|                            | 24                |                            | 0.001013                 | 0.000369                  |
|                            | 48                |                            | 0.002234                 | 0.000368                  |
| 10000                      | 1                 | 0.003015                   | 0.001617                 | 0.00202                   |
|                            | 2                 |                            | 0.002415                 | 0.001964                  |
|                            | 4                 |                            | 0.002049                 | 0.002111                  |
|                            | 8                 |                            | 0.003257                 | 0.001249                  |
|                            | 16                |                            | 0.003079                 | 0.003737                  |
|                            | 24                |                            | 0.003156                 | 0.003423                  |
|                            | 48                |                            | 0.00544                  | 0.00294                   |
| 100000                     | 1                 | 0.01854                    | 0.018547                 | 0.199                     |
|                            | 2                 |                            | 0.021651                 | 0.015189                  |
|                            | 4                 |                            | 0.01688                  | 0.008408                  |
|                            | 8                 |                            | 0.018882                 | 0.01606                   |
|                            | 16                |                            | 0.013631                 | 0.016771                  |
|                            | 24                |                            | 0.016659                 | 0.02296                   |
|                            | 48                |                            | 0.0227                   | 0.035204                  |
| 1000000                    | 1                 | 0.219678                   | 0.21941                  | 0.23636                   |
|                            | 2                 |                            | 0.140376                 | 0.137846                  |
|                            | 4                 |                            | 0.1255587                | 0.103484                  |
|                            | 8                 |                            | 0.102441                 | 0.133948                  |
|                            | 16                |                            | 0.082464                 | 0.092748                  |
|                            | 24                |                            | 0.088869                 | 0.294837                  |
|                            | 48                |                            | 0.077861                 | 0.131344                  |
| 10000000                   | 1                 | 2.568292                   | 2.564808                 | 2.768002                  |
|                            | 2                 |                            | 1.473908                 | 1.47016                   |
|                            | 4                 |                            | 1.177107                 | 1.08515                   |
|                            | 8                 |                            | 0.892717                 | 1.117797                  |
|                            | 16                |                            | 0.754185                 | 0.924634                  |
|                            | 24                |                            | 0.738589                 | 0.786672                  |
|                            | 48                |                            | 0.714466                 | 0.709331                  |

</details>

> **Note**  
> The results are indicative and may vary depending on the machine.

## How to use

First you need to build the scripts (check the `compilation` section).

Once done you have 2-4 executables :

- fileGenerator
- PThreadVersion (only for Linux)
- OpenMPVersion
- sequentialVersion

The `fileGenerator` one is only used to generate the files that will be used by the other 'merge sort' executables.

If you don't want to use it you can use the file named `test_file.txt` at the root of the project.

A file is composed of several lines:

- the first one is the number of elements in the array
- the second one is the array

For example :

```
4
11 
2 
3 
400
```

All the executables work the same way, use pipes to redirect the input file to the executable.

For example :

```bash
./mergeSortSequential < ./test_file
```

or

```bash
cat  ./test_file.txt | ./mergeSortSequential
```

You can then redirect the output to a file using `>` or `>>`.

Example :

```bash
./mergeSortSequential < ./test_file.txt > ./output_file.txt
```

The output file will now contain the sorted array.

The parallel versions of the merge sort has an additional argument which is the number of threads to use.

For example :

```bash
./mergeSortOpenMP < ./test_file > ./output_file.txt 4
```

The parallel merge sort using OpenMP is started with 4 threads.

The output will explain some details about the execution of the algorithm.

- The number of int in the array
- The number of threads used (only for the parallel versions)
- The CPU Time taken to sort the array
- The Wall Time taken to sort the array
- The sorted array (only if the array is small enough)

## Speed test

The project is set up with some `bash` scripts to test the speed of the different algorithms.
You can start the test by running the `speedTest.sh` script in the `speedTest` folder.

```bash
./speedTest.sh <base array size> <multiplier> <iteration number>
```

Example :

```bash
./speedTest.sh 10 10 6
```

It will generate 6 files with 10, 100, 1000, 10000, 100000, 1000000 elements in the array (they will be located in
the `speedTest/speedTestArrays` folder).

It will then run the different algorithms on the different files and output the results in the `speedTest/outputs`
folder.

> **Warning**
> You need to build the project before running the script (check the `compilation` section).
> You also need to be in the `speedTest` folder to run the script correctly.

## Compilation

To compile the app, the first thing you need to do is install a C++ compiler:

- Visual Studio (MSVC)
- Mingw
- GCC
- Cmake
- Make
- ...

### Compilation with CMake

First download CMake:  
<https://cmake.org>

Or install it with your package manager under Linux:

```bash
sudo apt install cmake
```

Once your environment is set up, depending on your operating system you'll need to install some libs before compiling
the project. Refer to the section below `Windows` or `Linux`;

#### Windows

Windows users can directly compile the project by typing the following command at the project root folder:

```bash
cmake -B . -DCMAKE_BUILD_TYPE=Release
```

> **Note**  
> If you're using Visual Studio, you can install CMake directly from the IDE (Visual Studio Installer).
> Then you need to open the Project as a CMake Project, not a Visual Studio Project!

#### Linux

Linux's users need to install some libs before compiling the project:

First you need to install `gcc` by typing the following command:

```bash
sudo apt-get install gcc
```

Then install CMake, type the following command to install it.

```bash
sudo apt-get install cmake
```

You also need to install the OpenMP lib. Type the following command at the project root.

```bash
sudo apt-get install libomp-dev
```

You are now able to compile the project. Go to the project root and type the following command:

```bash
cmake -B . -DCMAKE_BUILD_TYPE=Release
```

### Compile with Make

You can also use the Makefile to compile the project. Type the following command at the project root:

#### Setup

First you need to install `make` and `gcc` for linux users:

For linux:

```shell
sudo apt-get install gcc
```

```bash
sudo apt-get install make
```

<!--
You also need to install the mingw compiler to compile the Windows version under linux:

```bash
sudo apt-get install mingw-w64
```

You also need the LLVM OpenMP lib. Type the following command at the project root.

```shell
sudo apt-get install libomp-12-dev
```
-->

#### Compilation

You can compile the project for Linux:

```bash
make
```

to compile the project for Linux only.

```bash
make LinuxVer
```

<!--

and to compile the project for Windows only.

```bash
make WindowsVer
```
-->

To compile only one of the scripts, type:

```bash
make <script_name>
```

The Linux scripts names are:

- `fileGen`
- `mergeSortSeq`
- `mergeSortParOpenMp`
- `mergeSortParPthread`

<!--

The Windows ones are:

- `fileGenWin`
- `sequentialVerWin`
- `OpenMpVerWin`

-->

The executables will be created in the `BuildMakeFile` folder.

## Project Architecture

~~~
ParticleEngine
├── .github
│  ├── workflows
│  │   |── c-cpp.yml
│  │   |── cmake.yml
│  │   |── codeql.yml
│  │   |── cpp-linter.yml
│  │   |── dependency-review.yml
│  │   |── flawfinder.yml
│  │   |── greetings.yml
│  │   |── label.yml
│  │   |── msvc.yml
│  │   |── stale.yml
|  ├── labeler.yml
|  ├── release.yml
├── buildMakeFile
|  ├── readme.txt
|  ├── test_file.txt
├── commonFunctions
|  ├── commonFunctions.h
|  ├── commonFunctions.c
├── fileGenerator
|  ├── CMakelists.txt
|  ├── main.c
├── OpenMpVersion
|  ├── CMakelists.txt
|  ├── main.c
|  ├── mergeSortParallelOpenMP.c
|  ├── mergeSortParallelOpenMP.h
├── PThreadVersion
|  ├── CMakelists.txt
|  ├── main.c
|  ├── mergeSortParallelPThread.c
|  ├── mergeSortParallelPThread.h
├── sequentialVersion
|  ├── CMakelists.txt
|  ├── main.c
|  ├── mergeSortSequential.c
|  ├── mergeSortSequential.h
├── speedTest
│  ├── outputs
│  │   |── readme.txt
│  ├── speedTestArrays
│  │   |── readme.txt
|  ├── fileGenerator.sh
|  ├── multithreads_comparison.xlsx
|  ├── multithreads_comparison.csv
|  ├── speedTest.sh
├── test
|  ├── CMakelists.txt
|  ├── mergeSortOpenMPTest.c
|  ├── mergeSortPThreadTest.c
|  ├── mergeSortSequentialTest.c
|  ├── sortFunctions.h
├── ParticleEngine
├── .clang-format
├── .clang-tidy
├── .editorconfig
├── .gitattributes
├── .gitignore
├── CMakelists.txt
├── CMakePresets.json
├── CMakeSettings.json
├── Makefile
├── README.md
~~~

## GitHub Actions

[![CMake](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/cmake.yml)
[![Microsoft C++ Code Analysis](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/msvc.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/msvc.yml)
[![CodeQL](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/codeql.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/codeql.yml)
[![cpp-linter](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/cpp-linter.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/cpp-linter.yml)
[![flawfinder](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/flawfinder.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/flawfinder.yml)
[![C/C++ CI](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/c-cpp.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/c-cpp.yml)

- CMake: This script is used to build the project.
- MSVC: This script is used to analyze the code with Microsoft C++ Code Analysis.
- CodeQL: This script is used to analyze the code with CodeQL.
- cpp-linter: This script is used to check the C code formatting.
- flawfinder: This script is used to analyze the code with flawfinder.
- c-cpp: This script is used to build the project with C/C++ CI using make.

## Documentations

Introduction to Algorithms, 3rd Edition, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein

Wikipedia:  
<https://en.wikipedia.org/wiki/Merge_sort>

OpenMP:  
<https://www.openmp.org>

OpenMp CMake:  
<https://cliutils.gitlab.io/modern-cmake/chapters/packages/OpenMP.html>

StackOverflow:  
<https://stackoverflow.com/questions/52767944/merge-sort-with-pthreads-in-c>  
<https://stackoverflow.com/questions/67131148/how-to-do-merge-sort-without-using-additional-arrays-for-splitting-the-initial-a>

cliutils:  
<https://cliutils.gitlab.io/modern-cmake/chapters/packages/OpenMP.html>

## Contributors

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/cMergeSortParallel)](https://github.com/Im-Rises/cMergeSortParallel/graphs/contributors)
