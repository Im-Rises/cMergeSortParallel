# cMergeSortParallel

<p align="center">
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="cLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/199836862-958b46d2-2426-48e0-9866-68dd364f9066.png" alt="openmpLogo" style="height:60px;"/>
</p>

## Description

This is a simple physics engine written in C++ using Glad, GLFW, OpenGl3 and Dear ImGui.

It is implemented using Fixed Framerate and Component Oriented Programming.

> **Note**  
> The project is a work in progress and is not yet complete.

## Quickstart

Depending on you `operating system` you will need to install some libs, they are installed differently depending on your
system, please follow one of the section below `Windows` or `Linux`.

The different algorithms used are described below.

## Algorithms

- [x] Merge Sort
- [x] Parallel Merge Sort

### Merge Sort

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

Refer to : Introduction to Algorithms, 3rd Edition, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein

### Parallel Merge Sort

The parallel algorithm is written using `Cilk` algorithm syntax. 

```algorithm
parallelMergeSort(A,p,r)
    n = r-p+1
    if n == 1
        B[s] = A[p]
    else let T[1..n] be a new array
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

Refer to : Introduction to Algorithms, 3rd Edition, Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein


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
├── BuildMakeFile
|  ├── readme.txt
|  ├── *
├── OpenMpVersion
|  ├── CMakelists.txt
|  ├── d2omp.c
├── PThreadVersion
|  ├── CMakelists.txt
|  ├── d2p.c
├── sequentialVersion
|  ├── CMakelists.txt
|  ├── d2s.c
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
- ...

You also need to install Cmake:  
<https://cmake.org>

Once your environment is set up, depending on your operating system you'll need to install some libs before compiling
the project. Refer to the section below `Windows` or `Linux`;

### Windows

Windows users can directly compile the project by typing the following command at the project root folder:

```bash
cmake .
```

> **Note**  
> If you're using Visual Studio, you can install CMake directly from the IDE (Visual Studio Installer).
> Then you need to open the Project as a CMake Project, not a Visual Studio Project!

### Linux

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

You can also use the Makefile to compile the project. Type the following command at the project root:

First you need to install `make`:

```bash
sudo apt-get install make
```

Then you can compile the project:

```bash
make
```

or if you want to compile only one of the scripts type:

```bash
make <script_name>
```

The scripts names are:
- `sequentialVer`
- `OpenMpVer`
- `PThreadVer`

The executable will be created in the `BuildMakeFile` folder.

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

## Contributors

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/cMergeSortParallel)](https://github.com/Im-Rises/cMergeSortParallel/graphs/contributors)
