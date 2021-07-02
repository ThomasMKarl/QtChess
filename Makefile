CXX=g++
MPICXX=mpic++
CXXFLAGS=-Wall -Wextra -O3 -std=c++17 -fPIC -fopenmp -g

INCLUDE_DIR=include

MPI_LIB=/usr/lib/openmpi -lmpi_cxx -lmpi -Wl,-rpath -Wl,/usr/lib/openmpi -Wl,--enable-new-dtags

USE_MPI=-DUSE_MPI

## all       : makes cmd, qt and doc
all:
	make cmd
	make qt
	make mpi
	make doc

## cmd       : compiles command line application
cmd: board.o pawn.o knight.o bishop.o rook.o queen.o king.o
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -L $(MPI_LIB) cmd.cpp \
	src/board/board.o \
	src/board/fen.o \
	src/board/help.o \
	src/piece/pawn.o \
	src/piece/knight.o \
	src/piece/bishop.o \
	src/piece/rook.o \
	src/piece/queen.o \
	src/piece/king.o -o bin/qtchesscmd $(USE_MPI)

## cmd       : compiles cluster application
mpi: board.o pawn.o knight.o bishop.o rook.o queen.o king.o cluster.o
	export USE_MPI
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -L $(MPI_LIB) mpi.cpp \
	src/board/board.o \
	src/board/fen.o \
	src/board/help.o \
	src/cluster/cluster.o \
	src/piece/pawn.o \
	src/piece/knight.o \
	src/piece/bishop.o \
	src/piece/rook.o \
	src/piece/queen.o \
	src/piece/king.o -o bin/qtchesscmd_mpi $(USE_MPI)

cluster.o:
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/cluster/cluster.cpp -c -o src/cluster/cluster.o $(USE_MPI)
board.o:
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/board/board.cpp -c -o src/board/board.o $(USE_MPI)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/board/fen.cpp   -c -o src/board/fen.o $(USE_MPI)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/board/help.cpp  -c -o src/board/help.o $(USE_MPI)
pawn.o:
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/piece/pawn.cpp   -c -o src/piece/pawn.o $(USE_MPI)
knight.o:
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/piece/knight.cpp -c -o src/piece/knight.o $(USE_MPI)
bishop.o:
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/piece/bishop.cpp -c -o src/piece/bishop.o $(USE_MPI)
rook.o:
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/piece/rook.cpp   -c -o src/piece/rook.o $(USE_MPI)
queen.o:
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/piece/queen.cpp  -c -o src/piece/queen.o $(USE_MPI)
king.o:
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) src/piece/king.cpp   -c -o src/piece/king.o $(USE_MPI)

.PHONY : doc
## doc       : generates documentation
doc:
	mkdir -p doc
	doxygen doc/Doxyfile

## qt        : compiles Qt graphical interface
qt:
	qmake -o Makefile_qt
	make  -f Makefile_qt
	mkdir -p bin
	mv qtchess bin/

## clean     : removes object files and moc files
clean:
	rm -f      *.o     moc_*
	rm -rf   */*.o   */moc_*
	rm -rf */*/*.o */*/moc_*

## realclean : removes object files, moc files and compiled executables
realclean:
	make clean
	rm -f bin


.PHONY : help
## help      : prints help
help : Makefile
	@sed -n 's/^##//p' $<
