# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps	: MPS_opt.o
			$(CC) $(OPTFLAGS) MPS_opt.o -o bin/mps
MPS_opt.o	: src/MPS.cpp
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG Version
dbg : bin/mps_dbg
	@echo -n ""

bin/mps_dbg	: MPS_dbg.o
			$(CC) $(DBGFLAGS) MPS_dbg.o -o bin/mps_dbg
MPS_dbg.o	: src/MPS.cpp
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*
