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

PLACEHOLDER

### Parallel Merge Sort

PLACEHOLDER

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

First thing to do is to install CMake, type the following command to install it.

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
