all:
	$(MAKE) clean
	$(MAKE) OpenMpVer
	$(MAKE) PThreadVer
	$(MAKE) sequentialVer
	$(MAKE) clean

sequentialVer:
	gcc ./sequentialVersion/d2s.c -o BuildMakeFile/SquentialVersion -std=c11 -pedantic -O2

OpenMpVer:
	gcc ./OpenMpVersion/d2omp.c -o BuildMakeFile/OpenMpVersion -fopenmp -std=c11 -pedantic -O2

PThreadVer:
	gcc ./PThreadVersion/d2p.c -o BuildMakeFile/PThreadVersion -lpthread -std=c11 -pedantic -O2

clean :
	rm -rf *.o

#mrproper : clean
#	rm -rf OpenMpVersion
#	rm -rf PThreadVersion
#	rm -rf sequentialVersion
