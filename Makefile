all:
	$(MAKE) mrproper
	$(MAKE) fileGen
	$(MAKE) OpenMpVer
	$(MAKE) PThreadVer
	$(MAKE) sequentialVer
	$(MAKE) clean

fileGen:
	gcc ./fileGenerator/fileGenerator.c -o BuildMakeFile/fileGenerator -std=c90 -pedantic -O2

sequentialVer:
	gcc ./mergeSortSequential/d2s.c -o BuildMakeFile/mergeSortSequential -fopenmp -std=c90 -pedantic -O2

OpenMpVer:
	gcc ./mergeSortOpenMp/d2omp.c -o BuildMakeFile/mergeSortOpenMp -fopenmp -std=c90 -pedantic -O2

PThreadVer:
	gcc ./mergeSortPThread/d2p.c -o BuildMakeFile/mergeSortPThread -lpthread -fopenmp -std=c90 -pedantic -O2

clean :
	rm -rf *.o

mrproper : clean
	rm -f BuildMakeFile/fileGenerator
	rm -f BuildMakeFile/mergeSortOpenMp
	rm -f BuildMakeFile/mergeSortPThread
	rm -f BuildMakeFile/mergeSortSequential
