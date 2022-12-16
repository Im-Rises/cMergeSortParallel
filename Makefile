CC=gcc
CFLAGS= -std=c90 -W -Wall -ansi -pedantic  -O2
#LDFLAGS=
OPENMP_FLAGS= -fopenmp
PTHREAD_FLAGS= -pthread
OUTPUT_DIR=./buildMakeFile

all:
	$(MAKE) fileGen
	$(MAKE) mergeSortSeq
	$(MAKE) mergeSortParOpenMp
	$(MAKE) mergeSortParPthread
	$(MAKE) clean

fileGen:
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/fileGen fileGenerator/main.c

mergeSortSeq:
	$(MAKE) commonFuncs
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/mergeSortSequential.o -c mergeSortSequential/mergeSortSequential.c
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/main.o -c mergeSortSequential/main.c
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/mergeSortSequential $(OUTPUT_DIR)/mergeSortSequential.o $(OUTPUT_DIR)/main.o $(OUTPUT_DIR)/commonFunctions.o

mergeSortParOpenMp:
	$(MAKE) commonFuncs
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/mergeSortSequential.o -c mergeSortSequential/mergeSortSequential.c
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) -o $(OUTPUT_DIR)/mergeSortOpenMp.o -c mergeSortOpenMp/mergeSortParallelOpenMp.c
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) -o $(OUTPUT_DIR)/main.o -c mergeSortOpenMp/main.c
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) -o $(OUTPUT_DIR)/mergeSortOpenMp $(OUTPUT_DIR)/mergeSortOpenMp.o $(OUTPUT_DIR)/main.o $(OUTPUT_DIR)/commonFunctions.o $(OUTPUT_DIR)/mergeSortSequential.o

mergeSortParPthread:
	$(MAKE) commonFuncs
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/mergeSortSequential.o -c mergeSortSequential/mergeSortSequential.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) -o $(OUTPUT_DIR)/mergeSortPthread.o -c mergeSortPthread/mergeSortParallelPthread.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) -o $(OUTPUT_DIR)/main.o -c mergeSortPthread/main.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) -o $(OUTPUT_DIR)/mergeSortPthread $(OUTPUT_DIR)/mergeSortPthread.o $(OUTPUT_DIR)/main.o $(OUTPUT_DIR)/commonFunctions.o $(OUTPUT_DIR)/mergeSortSequential.o

commonFuncs:
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/commonFunctions.o -c commonFunctions/commonFunctions.c

.PHONY: clean mrproper all

clean:
	rm -rf $(OUTPUT_DIR)/*.o

mrproper: clean
	rm -rf $(OUTPUT_DIR)/fileGen
	rm -rf $(OUTPUT_DIR)/mergeSortSeq
	rm -rf $(OUTPUT_DIR)/mergeSortOpenMp
	rm -rf $(OUTPUT_DIR)/mergeSortPthread


## OTHER
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
