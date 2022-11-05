all:
	$(MAKE) clean
	$(MAKE) OpenMpVer
	$(MAKE) PThreadVer
	$(MAKE) sequentialVer
	$(MAKE) clean

sequentialVer:
	gcc ./sequentialVersion/d2s.c -o BuildMakeFile/SquentialVersion -O2

OpenMpVer:
	gcc ./OpenMpVersion/d2omp.c -o BuildMakeFile/OpenMpVersion -fopenmp -O2

PThreadVer:
	gcc ./PThreadVersion/d2p.c -o BuildMakeFile/PThreadVersion -lpthread -O2

clean :
	rm -rf *.o

#mrproper : clean
#	rm -rf OpenMpVersion
#	rm -rf PThreadVersion
#	rm -rf sequentialVersion
