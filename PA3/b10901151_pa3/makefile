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

all	: bin/cb
	@echo -n ""

# optimized version
bin/cb	: main_opt.o
			$(CC) $(OPTFLAGS) main_opt.o -o bin/cb
main_opt.o	: src/main.cpp
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG Version
dbg : bin/cb_dbg
	@echo -n ""

bin/cb_dbg	: main_dbg.o
			$(CC) $(DBGFLAGS) main_dbg.o -o bin/cb_dbg
main_dbg.o	: src/main.cpp
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*
