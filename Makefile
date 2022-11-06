all:
	$(MAKE) clean
	$(MAKE) OpenMpVer
	$(MAKE) PThreadVer
	$(MAKE) sequentialVer
	$(MAKE) clean

fileGenerator:
	gcc ./fileGenerator/fileGenerator.c -o BuildMakeFile/fileGenerator -std=c11 -pedantic -O2

sequentialVer:
	gcc ./mergeSortSequential/d2s.c -o BuildMakeFile/SquentialVersion -std=c11 -pedantic -O2

OpenMpVer:
	gcc ./mergeSortOpenMp/d2omp.c -o BuildMakeFile/mergeSortOpenMp -fopenmp -std=c11 -pedantic -O2

PThreadVer:
	gcc ./mergeSortPThread/d2p.c -o BuildMakeFile/mergeSortPThread -lpthread -std=c11 -pedantic -O2

clean :
	rm -rf *.o

#mrproper : clean
#	rm -rf mergeSortOpenMp
#	rm -rf mergeSortPThread
#	rm -rf mergeSortSequential
