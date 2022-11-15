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
	gcc ./fileGenerator/fileGenerator.c -o buildMakeFile/fileGenerator -std=c90 -Wall -O2

sequentialVerLinux:
	gcc ./mergeSortSequential/d2s.c -o buildMakeFile/mergeSortSequential -fopenmp -std=c90 -Wall -O2

OpenMpVerLinux:
	gcc ./mergeSortOpenMp/d2omp.c -o buildMakeFile/mergeSortOpenMp -fopenmp -std=c90 -Wall -O2

PThreadVerLinux:
	gcc ./mergeSortPThread/d2p.c -o buildMakeFile/mergeSortPThread -lpthread -fopenmp -std=c90 -Wall -O2

MrProperLinux : clean
	rm -f buildMakeFile/fileGenerator
	rm -f buildMakeFile/mergeSortOpenMp
	rm -f buildMakeFile/mergeSortPThread
	rm -f buildMakeFile/mergeSortSequential

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

clean :
	rm -rf *.o

MrProperWin : clean
	rm -f buildMakeFile/fileGenerator.exe
	rm -f buildMakeFile/mergeSortOpenMp.exe
	rm -f buildMakeFile/mergeSortPThread.exe
	rm -f buildMakeFile/mergeSortSequential.exe
