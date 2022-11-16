all:
	$(MAKE) LinuxVer
#	$(MAKE) WindowsVer

LinuxVer:
	$(MAKE) MrProperLinux
	$(MAKE) fileGenLinux
	$(MAKE) sequentialVerLinux
	$(MAKE) OpenMpVerLinux
	$(MAKE) PThreadVerLinux
	$(MAKE) clean

fileGenLinux:
	gcc ./fileGenerator/main.c -o buildMakeFile/fileGenerator -std=c90 -Wall -O2

sequentialVerLinux:
	gcc ./mergeSortSequential/main.c -o buildMakeFile/main.o -c -std=c90 -Wall -O2
	gcc ./mergeSortSequential/mergeSortSequential.c -o buildMakeFile/mergeSortSequential.o -c -std=c90 -Wall -O2
	gcc ./commonFunctions/commonFunctions.c -o buildMakeFile/commonFunctions.o -c -std=c90 -Wall -O2
	gcc -o ./buildMakeFile/mergeSortSequential buildMakeFile/main.o buildMakeFile/mergeSortSequential.o buildMakeFile/commonFunctions.o -std=c90 -Wall -O2

OpenMpVerLinux:
	gcc ./mergeSortOpenMp/main.c -o buildMakeFile/main.o -c -std=c90 -Wall -O2
	gcc ./mergeSortOpenMp/mergeSortParallelOpenMp.c -o buildMakeFile/mergeSortParallelOpenMp.o -fopenmp -c -std=c90 -Wall -O2
	gcc ./mergeSortSequential/mergeSortSequential.c -o buildMakeFile/mergeSortSequential.o -c -std=c90 -Wall -O2
	gcc ./commonFunctions/commonFunctions.c -o buildMakeFile/commonFunctions.o -c -std=c90 -Wall -O2
	gcc -o ./buildMakeFile/mergeSortOpenMp buildMakeFile/main.o buildMakeFile/mergeSortParallelOpenMp.o buildMakeFile/commonFunctions.o buildMakeFile/mergeSortSequential.o -fopenmp -std=c90 -Wall -O2

PThreadVerLinux:
	gcc ./mergeSortPThread/main.c -o buildMakeFile/main.o -c -std=c90 -Wall -O2
	gcc ./mergeSortPThread/mergeSortParallelPThread.c -o buildMakeFile/mergeSortParallelPThread.o -lpthread -c -std=c90 -Wall -O2
	gcc ./mergeSortSequential/mergeSortSequential.c -o buildMakeFile/mergeSortSequential.o -c -std=c90 -Wall -O2
	gcc ./commonFunctions/commonFunctions.c -o buildMakeFile/commonFunctions.o -c -std=c90 -Wall -O2
	gcc -o ./buildMakeFile/mergeSortPThread buildMakeFile/main.o buildMakeFile/mergeSortParallelPThread.o buildMakeFile/commonFunctions.o buildMakeFile/mergeSortSequential.o -lpthread -std=c90 -Wall -O2

MrProperLinux : clean
	rm -f buildMakeFile/fileGenerator
	rm -f buildMakeFile/mergeSortOpenMp
	rm -f buildMakeFile/mergeSortPThread
	rm -f buildMakeFile/mergeSortSequential
	$(MAKE) clean

clean :
	rm -rf buildMakeFile/*.o

#WindowsVer:
#	$(MAKE) MrProperWin
#	$(MAKE) fileGenWin
#	$(MAKE) sequentialVerWin
#	$(MAKE) OpenMpVerWin
#	$(MAKE) clean
#
#fileGenWin:
#	x86_64-w64-mingw32-gcc ./fileGenerator/fileGenerator.c -o buildMakeFile/fileGenerator.exe -std=c90 -Wall -O2
#
#sequentialVerWin:
#	x86_64-w64-mingw32-gcc ./mergeSortSequential/d2s.c -o buildMakeFile/mergeSortSequential.exe -std=c90 -Wall -O2
#
#OpenMpVerWin:
#	x86_64-w64-mingw32-gcc ./mergeSortOpenMp/d2omp.c -o buildMakeFile/mergeSortOpenMp.exe -fopenmp=libomp5 -std=c90 -Wall -O2
#
#MrProperWin : clean
#	rm -f buildMakeFile/fileGenerator.exe
#	rm -f buildMakeFile/mergeSortOpenMp.exe
#	rm -f buildMakeFile/mergeSortPThread.exe
#	rm -f buildMakeFile/mergeSortSequential.exe
