all:
	$(MAKE) clean
	$(MAKE) fileGen
	$(MAKE) OpenMpVer
	$(MAKE) PThreadVer
	$(MAKE) sequentialVer
	$(MAKE) clean

fileGen:
	gcc ./fileGenerator/fileGeneratorExe.c -o BuildMakeFile/fileGenerator -std=c99 -pedantic -O2

sequentialVer:
	gcc ./mergeSortSequential/d2s.c -o BuildMakeFile/mergeSortSequential -fopenmp -std=c99 -pedantic -O2

OpenMpVer:
	gcc ./mergeSortOpenMp/d2omp.c -o BuildMakeFile/mergeSortOpenMp -fopenmp -std=c99 -pedantic -O2

PThreadVer:
	gcc ./mergeSortPThread/d2p.c -o BuildMakeFile/mergeSortPThread -lpthread -fopenmp -std=c99 -pedantic -O2

clean :
	rm -rf *.o

#mrproper : clean
#	rm -rf mergeSortOpenMp
#	rm -rf mergeSortPThread
#	rm -rf mergeSortSequential
