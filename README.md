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

## Results

| Array size | threads | Sequential | OpenMP    | Pthreads  |
|------------|---------|------------|-----------|-----------|
| 1 000 000  | 1       | 0.153550s  | 0.153550s | 0.153550s |
| 1 000 000  | 4       | 0.153550s  | 0.079991s | 0.073561s |      

<!--
Results for 1 000 000 integers:

- Sequential: 0.153550 seconds
- OpenMP Parallel: 0.079991 seconds
- PThread Parallel: 0.073561 seconds
-->

> **Note**  
> The results are indicative and may vary depending on the machine.

## Quickstart

Depending on you `operating system` you will need to install some libs, they are installed differently depending on your
system, please follow one of the section below `Windows` or `Linux`.

For an explanation on `How to use` go to the according section.

The different algorithms used are described below.

## Algorithms

- [x] Merge Sort
- [x] Parallel Merge Sort

### Merge Sort V1

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

Refer to : Introduction to Algorithms, 3rd Edition, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford
Stein

The parallel version of the algorithm is implemented using OpenMP and PThreads.
Depending on the version the results are different.

### Merge Sort V2

The parallel algorithm is written using `Cilk` algorithm syntax.

```algorithm
parallelMergeSort(A,p,r)
    n = r-p+1
    if n == 1
        B[s] = A[p]
    else let T[1...n] be a new array
        q = (p+r)/2
        q2 = q-p+1
        spawn parallelMergeSort(A,p,q,T,1)
        parallelMergeSort(A,q+1,r,T,q2+1)
        sync
        parallelMerge(T,1,q2,q2+1,n,B,s)
```

```algorithm
parallelMerge(A,p_1,r_1,p_2,r_2,A,p_3)
    n1 = r_1-p_1+1
    n2 = r_2-p_2+1
    if n_1 < n_2
        exchange p_1 and p_2
        exchange r_1 and r_2
        exchange n_1 and n_2
    if n_1 == 0
        return
    else 
        q_1 = (p_1+r_1)/2
        q_2 = binarySearch(T[q1], T, p_2, r_2)
        q_3 = p_3+(q_1-p_1)+(q_2-p_2)
        A[q_3] = T[q_1]
        spawn parallelMerge(T,p_1,q_1-1,p_2,q_2-1,A,p_3)
        parallelMerge(T,q_1+1,r_1,q_2,r_2,A,q_3+1)
        sync
```

```algorithm
binarySearch(x,T,p,r)
    low = p
    high = max(p,r+1)
    while low < high
        mid = (low+high)/2
        if x <= T[mid]
            high = mid
        else 
            low = mid+1
    return high
```

Refer to : Introduction to Algorithms, 3rd Edition, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford
Stein

### Parallel Merge Sort

PLACEHOLDER

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

All the executables work the same way, use pipes to redirect the file to the executable.

For example :

```bash
./mergeSortSequential < ./test_file > ./output_file.txt
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
├── fileGenerator
|  ├── CMakelists.txt
|  ├── fileGenerator.c
├── OpenMpVersion
|  ├── CMakelists.txt
|  ├── d2omp.c
├── PThreadVersion
|  ├── CMakelists.txt
|  ├── d2p.c
├── sequentialVersion
|  ├── CMakelists.txt
|  ├── d2s.c
├── speedTest
|  ├── fileGenerator.sh
|  ├── multithreads_comparison.xlsx
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

## Dependencies

- C11
- CMake or Make
- C11 compiler (MSVC, Mingw, ...)

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
cmake .
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
cmake .
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

You also need to install the mingw compiler to compile the Windows version under linux:

```bash
sudo apt-get install mingw-w64
```

#### Compilation

##### Compile all the versions

You can compile the project for Linux and Windows:

```bash
make
```

to compile the project for Linux only.

```bash
make LinuxVer
```

and to compile the project for Windows only.

```bash
make WindowsVer
```

##### Compile only one script

To compile only one of the scripts type:

```bash
make <script_name>
```

The Linux scripts names are:

- `fileGenLinux`
- `sequentialVerLinux`
- `OpenMpVerLinux`
- `PThreadVerLinux`

The Windows ones are:

- `fileGenWin`
- `sequentialVerWin`
- `OpenMpVerWin`

The executables will be created in the `BuildMakeFile` folder.

## GitHub Actions

[![CMake](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/cmake.yml)
[![Microsoft C++ Code Analysis](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/msvc.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/msvc.yml)
[![CodeQL](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/codeql.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/codeql.yml)
[![cpp-linter](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/cpp-linter.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/cpp-linter.yml)
[![flawfinder](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/flawfinder.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/flawfinder.yml)
[![C/C++ CI](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/c-cpp.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cMergeSortParallel/actions/workflows/c-cpp.yml)

- CMake: This script is used to build the project.
- MSVC: This script is used to analyze the code with Microsoft C++ Code Analysis.
- c-cpp: This script is used to build the project with C/C++ CI using make.
- cpp-linter: This script is used to check the C code formatting.
- CodeQL: This script is used to analyze the code with CodeQL.
- flawfinder: This script is used to analyze the code with flawfinder.

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

## Contributors

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/cMergeSortParallel)](https://github.com/Im-Rises/cMergeSortParallel/graphs/contributors)
