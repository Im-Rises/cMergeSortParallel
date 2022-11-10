all:
	$(MAKE) LinuxVer
	$(MAKE) WindowsVer

LinuxVer:
	$(MAKE) MrProperLinux
	$(MAKE) fileGenLinux
	$(MAKE) sequentialVerLinux
	$(MAKE) OpenMpVerLinux
	$(MAKE) PThreadVerLinux
	$(MAKE) clean

fileGenLinux:
	gcc ./fileGenerator/fileGenerator.c -o BuildMakeFile/fileGenerator -std=c90 -Wall -O2

sequentialVerLinux:
	gcc ./mergeSortSequential/d2s.c -o BuildMakeFile/mergeSortSequential -fopenmp -std=c90 -Wall -O2

OpenMpVerLinux:
	gcc ./mergeSortOpenMp/d2omp.c -o BuildMakeFile/mergeSortOpenMp -fopenmp -std=c90 -Wall -O2

PThreadVerLinux:
	gcc ./mergeSortPThread/d2p.c -o BuildMakeFile/mergeSortPThread -lpthread -fopenmp -std=c90 -Wall -O2
# -pedantic

MrProperLinux : clean
	rm -f BuildMakeFile/fileGenerator
	rm -f BuildMakeFile/mergeSortOpenMp
	rm -f BuildMakeFile/mergeSortPThread
	rm -f BuildMakeFile/mergeSortSequential

WindowsVer:
	$(MAKE) MrProperWin
	$(MAKE) fileGenWin
	$(MAKE) sequentialVerWin
	$(MAKE) OpenMpVerWin
	$(MAKE) clean

fileGenWin:
	x86_64-w64-mingw32-gcc ./fileGenerator/fileGenerator.c -o BuildMakeFile/fileGenerator.exe -std=c90 -Wall -O2

sequentialVerWin:
	x86_64-w64-mingw32-gcc ./mergeSortSequential/d2s.c -o BuildMakeFile/mergeSortSequential.exe -std=c90 -Wall -O2

OpenMpVerWin:
	x86_64-w64-mingw32-gcc ./mergeSortOpenMp/d2omp.c -o BuildMakeFile/mergeSortOpenMp.exe -fopenmp -std=c90 -Wall -O2

clean :
	rm -rf *.o

MrProperWin : clean
	rm -f BuildMakeFile/fileGenerator.exe
	rm -f BuildMakeFile/mergeSortOpenMp.exe
	rm -f BuildMakeFile/mergeSortPThread.exe
	rm -f BuildMakeFile/mergeSortSequential.exe
